/****************************************************
 * 2016-2024 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/
#include "raytracer.h"
#include "ishape.h"
#include "io.h"

 /**
  * @fn	RayTracer::RayTracer(const color &defa)
  * @brief	Constructs a raytracers.
  * @param	defa	The clear color.
  */

RayTracer::RayTracer(const color& defa)
    : defaultColor(defa) {
}

/**
 * @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
 * @brief	Raytrace scene
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	depth	   	The current depth of recursion.
 * @param 		  	theScene   	The scene.
 */

void RayTracer::raytraceScene(FrameBuffer& frameBuffer, int depth,
    const IScene& theScene, int n) {
    const RaytracingCamera& camera = *theScene.camera;
    //const vector<VisibleIShapePtr>& objs = theScene.opaqueObjs;
    const vector<LightSourcePtr>& lights = theScene.lights;
    //color defaultColor = frameBuffer.getClearColor();
    this->initialRecursionDepth = depth;

    for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
        for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {
            //DEBUG_PIXEL = (x == xDebug && y == yDebug);
            //if (DEBUG_PIXEL) {
            //    cout << "";
            //}
            if (n > 1) {
                vector<Ray> rays = theScene.camera->getAARays(x, y, n);

                color colorForPixel = black;
                for (auto& ray : rays) {
                    colorForPixel += traceIndividualRay(ray, theScene, depth);;
                }

                colorForPixel /= rays.size();
                colorForPixel = glm::clamp(colorForPixel, 0.0, 1.0);
                frameBuffer.setColor(x, y, colorForPixel);
            }
            else {
                Ray ray = theScene.camera->getRay(x, y);
                color colorForPixel = traceIndividualRay(ray, theScene, depth);
                frameBuffer.setColor(x, y, colorForPixel);
                frameBuffer.showAxes(x, y, ray, 0.25);
            }
        }
    }

    frameBuffer.showColorBuffer();
}

/**
 * @fn	color RayTracer::traceIndividualRay(const Ray &ray,
 *											const IScene &theScene,
 *											int recursionLevel) const
 * @brief	Trace an individual ray.
 * @param	ray			  	The ray.
 * @param	theScene	  	The scene.
 * @param	recursionLevel	The recursion level.
 * @return	The color to be displayed as a result of this ray.
 */

 /**
  * @fn	static double fresnel(const dvec3& i, const dvec3& n, const double& etai, const double& etat)
  *
  * @brief	Compute Fresnel equation
  *
  * @param	i   	is the incident view direction.
  * @param	n   	is the normal at the intersection point.
  * @param	etai	is the refractive index of the material the light is leaving.
  * @param	etat	is the refractive index of the material the light is entering.
  *
  * @returns	kr is the percentage of light reflected As a consequence of the conservation of
  * 			energy, transmittance is given by: kt = 1 - kr
  * 			https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
  * 			http://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted
  * 			https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf.
  * 			https://www.cs.cornell.edu/courses/cs4620/2012fa/lectures/36raytracing.pdf
  */
static double fresnel(const dvec3& i, const dvec3& n, const double& etai, const double& etat)
{
    // Percentage of light that is reflected
    // Percentage of light that is refracted is equal to 1-kr
    double kr;

    // Calculate the dot product of the incidence vector and the normal 
    // vector of the surface the the light is entering
    double cosi = glm::clamp(-1.0, 1.0, glm::dot(i, n));

    // Compute the sine of the angle of refraction using Snell's law
    double sint = etai / etat * sqrt(glm::max(0.0, 1.0 - cosi * cosi));

    // Check if angle of incidence exceeds critical angle 
    if (sint >= 1.0) {
        kr = 1.0; // Total internal reflection
    }
    else {
        // Calculate the percentage of light that will be reflected
        double cost = sqrt(glm::max(0.0, 1.0 - sint * sint));
        cosi = fabs(cosi);
        double Rs = ((etat * cosi) - (etai * cost)) / ((etai * cost) + (etat * cosi)); // S polarized light (parallel)
        double Rp = ((etai * cosi) - (etat * cost)) / ((etat * cost) + (etai * cosi)); // P polarized light (perpendicular)
        kr = (Rs * Rs + Rp * Rp) / 2.0;
    }

    return kr;

}

color RayTracer::traceIndividualRay(const Ray& ray, const IScene& theScene, int recursionLevel) const {
    OpaqueHitRecord theHit;
    theHit.t = FLT_MAX;
    VisibleIShape::findIntersection(ray, theScene.opaqueObjs, theHit);

    if (theHit.t < FLT_MAX) {
        color totalColor = black;

        if (theHit.texture != nullptr) {
            color texelColor = theHit.texture->getPixelUV(theHit.u, theHit.v);
            theHit.material.ambient = 0.15 * texelColor;
            theHit.material.diffuse = texelColor;
        }

        if (!theHit.material.isDielectric) {
            for (auto& light : theScene.lights) {
                bool inShadow = light->pointIsInAShadow(theHit.interceptPt, theHit.normal, theScene.opaqueObjs, theScene.camera->getFrame());
                totalColor += light->illuminate(theHit.interceptPt, theHit.normal, theHit.material, theScene.camera->getFrame(), inShadow);
            }
        }

        if (recursionLevel > 0) {
            if (theHit.material.isDielectric) {
                double etai, etat;
                if (theHit.rayStatus == ENTERING) {
                    etai = 1.0;
                    etat = theHit.material.dielectricRefractionIndex;
                }
                else {
                    etai = theHit.material.dielectricRefractionIndex;
                    etat = 1.0;
                }

                double kr = fresnel(ray.dir, theHit.normal, etai, etat);
                double kt = 1.0 - kr;

                dvec3 reflectionDir = glm::reflect(ray.dir, theHit.normal);
                Ray reflectionRay(theHit.interceptPt + EPSILON * theHit.normal, reflectionDir);
                color reflectionColor = traceIndividualRay(reflectionRay, theScene, recursionLevel - 1);

                color refractionColor = black;

                if (kr < 1.0) {
                    Ray refractionRay(theHit.interceptPt - EPSILON * theHit.normal, ray.dir);
                    refractionColor = traceIndividualRay(refractionRay, theScene, recursionLevel - 1);

                    color tint = color(1.3, 0.9, 0.9);
                    refractionColor = refractionColor * tint;
                }
                totalColor = kr * reflectionColor + kt * refractionColor;
            }


            else {
                dvec3 reflectionDir = glm::reflect(ray.dir, theHit.normal);
                Ray reflectionRay(theHit.interceptPt + EPSILON * theHit.normal, reflectionDir);
                totalColor += 0.5 * traceIndividualRay(reflectionRay, theScene, recursionLevel - 1);

                if (theHit.material.alpha < 1.0) {
                    Ray transparentRay(theHit.interceptPt - EPSILON * theHit.normal, ray.dir);
                    color transparentColor = traceIndividualRay(transparentRay, theScene, recursionLevel - 1);
                    totalColor = theHit.material.alpha * totalColor + (1.0 - theHit.material.alpha) * transparentColor;
                }
            }
        }
        else if (theHit.material.isDielectric) {
            Ray transparentRay(theHit.interceptPt - EPSILON * theHit.normal, ray.dir);
            color throughColor = traceIndividualRay(transparentRay, theScene, 0);

            color tint = color(1.3, 0.9, 0.9);
            totalColor = throughColor * tint;
        }

        return totalColor;
    }
    return (recursionLevel == initialRecursionDepth) ? defaultColor : defaultColor * 0.1;
}
