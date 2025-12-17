/****************************************************
 * 2016-2024 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include "light.h"
#include "io.h"
#include "ishape.h"

 /**
  * @fn	color ambientColor(const color &matAmbient, const color &lightColor)
  * @brief	Computes the ambient color produced by a single light at a single point.
  * @param	mat  	Ambient material property.
  * @param	lightColor	Light's color.
  * @return	Ambient color.
   */

color ambientColor(const color& ambientMatColor, const color& lightColor) {
	return ambientMatColor * lightColor;
}

/**
 * @fn	color diffuseColor(const color &mat, const color &light, const dvec3 &l, const dvec3 &n)
 * @brief	Computes diffuse color produce by a single light at a single point.
 * @param	mat		 	Material.
 * @param	lightColor	 	The light's color.
 * @param	l		 	Light vector.
 * @param	n		 	Normal vector.
 * @return	Diffuse color.
 */

color diffuseColor(const color& diffuseMatColor, const color& lightColor,
	const dvec3& lightVector, const dvec3& surfaceNormal) {
	return glm::max(0.0, glm::dot(lightVector, surfaceNormal)) * diffuseMatColor * lightColor;
}

/**
 * @fn	color specularColor(const color &mat, const color &lightColor, double shininess,
 *							const dvec3 &r, const dvec3 &v)
 * @brief	Computes specular color produce by a single light at a single point.
 * @param	mat		 	Material.
 * @param	lightColor	 	The light's color.
 * @param	shininess	Material shininess.
 * @param	r		 	Reflection vector.
 * @param	v		 	Viewing vector.
 * @return	Specular color.
 */

color specularColor(const color& mat, const color& lightColor,
	double shininess,
	const dvec3& r, const dvec3& v) {

	return glm::pow(glm::max(glm::dot(r,v), 0.0), shininess) * mat * lightColor;
}

/**
 * @fn	color totalColor(const Material &mat, const color &lightColor,
 *						const dvec3 &viewingDir, const dvec3 &normal,
 *						const dvec3 &lightPos, const dvec3 &intersectionPt,
 *						bool attenuationOn, const LightAttenuationParameters &ATparams)
 * @brief	Color produced by a single light at a single point. This includes the summation
 * of the ambient, diffuse, and specular components. Attenuation is also applied, if applicable.
 * @param	mat			  	Material.
 * @param	lightColor	  	The light's color.
 * @param	v	  			The v vector.
 * @param	n   		  	Normal vector.
 * @param	lightPos	  	Light position.
 * @param	intersectionPt	(x,y,z) of intersection point.
 * @param	attenuationOn 	true if attenuation is on.
 * @param	ATparams	  	Attenuation parameters.
 * @return	Color produced by a single light at a single point. This includes the summation
 * of the ambient, diffuse, and specular components. Attenuation is also applied, if applicable.
 */

color totalColor(const Material& mat, const color& lightColor,
	const dvec3& viewVector, const dvec3& surfaceNormal,
	const dvec3& lightPos, const dvec3& intersectionPt,
	bool attenuationOn,
	const LightATParams& ATparams) {

	dvec3 lightVector = glm::normalize(lightPos - intersectionPt);
	dvec3 reflectionVector = glm::reflect(-lightVector, surfaceNormal);

	double attenuationFactor = attenuationOn ? ATparams.factor(glm::distance(intersectionPt, lightPos)) : 1.0;
	
	color ambientReflection = ambientColor(mat.ambient, lightColor);
	color diffuseReflection = diffuseColor(mat.diffuse, lightColor, lightVector, surfaceNormal);
	color specularReflection = specularColor(mat.specular, lightColor, mat.shininess, reflectionVector, viewVector);
	
	return glm::clamp(ambientReflection + attenuationFactor * (diffuseReflection + specularReflection), 0.0, 1.0);
}

/**
 * @fn	color PositionalLight::illuminate(const dvec3 &interceptWorldCoords,
 *										const dvec3 &normal, const Material &material,
 *										const Frame &eyeFrame, bool inShadow) const
 * @brief	Computes the color this light produces in RAYTRACING applications.
 * @param	interceptWorldCoords	(x, y, z) at the intercept point.
 * @param	normal				The normal vector.
 * @param	material			The object's material properties.
 * @param	eyeFrame			The coordinate frame of the camera.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 */

color PositionalLight::illuminate(const dvec3& interceptWorldCoords,
	const dvec3& normal,
	const Material& material,
	const Frame& eyeFrame,
	bool inShadow) const {
	/* CSE 386 - todo  */

	if (!this->isOn) return black;

	if (inShadow) return ambientColor(material.ambient, this->lightColor);

	dvec3 viewVector = glm::normalize(eyeFrame.origin - interceptWorldCoords);
	dvec3 lightPosition = this->isTiedToWorld ? this->pos : eyeFrame.frameCoordsToGlobalCoords(this->pos);

	color colorForThisLight = totalColor(material, this->lightColor, viewVector, normal, lightPosition, interceptWorldCoords, this->attenuationIsTurnedOn, this->atParams);
	return colorForThisLight;
}

/*
* @fn PositionalLight::actualPosition(const Frame& eyeFrame) const
* @brief	Returns the global world coordinates of this light.
* @param	eyeFrame	The camera's frame
* @return	The global world coordinates of this light. This will be the light's
*			raw position. Or, it will be the position relative to the camera's
*			frame (transformed from camera's frame into the world coordinate frame).
*/

dvec3 PositionalLight::actualPosition(const Frame& eyeFrame) const {
	return isTiedToWorld ? pos : eyeFrame.frameCoordsToGlobalCoords(pos);
}

/**
* @fn	bool PositionalLight::pointIsInAShadow(const dvec3& intercept, const dvec3& normal, const vector<VisibleIShapePtr>& objects, const Frame& eyeFrame) const
* @brief	Determines if an intercept point falls in a shadow.
* @param	intercept	the position of the intercept.
* @param	normal		the normal vector at the intercept point
* @param	objects		the collection of opaque objects in the scene
*/

bool PositionalLight::pointIsInAShadow(const dvec3& intercept,
    const dvec3& normal,
    const vector<VisibleIShapePtr>& objects,
    const Frame& eyeFrame) const {

    double distanceToLight = glm::distance(intercept, this->pos);
    dvec3 directionToLight = glm::normalize(this->pos - intercept);
    Ray shadowFeeler(intercept + EPSILON * normal, directionToLight);
    OpaqueHitRecord hit;

    for (const auto& obj : objects) {
        hit.t = FLT_MAX;
        obj->findClosestIntersection(shadowFeeler, hit);

        if (hit.t < distanceToLight) {
            if (hit.material.isDielectric) continue;
            return true;
        }
    }
    return false;
}


/**
* @fn	Ray PositionalLight::getShadowFeeler(const dvec3& interceptWorldCoords, const dvec3& normal, const Frame &eyeFrame) const
* @brief	Returns the shadow feeler for this light.
* @param	interceptWorldCoords	the position of the intercept.
* @param	normal		The normal vector at the intercept point
* @param	eyeFrame	The coordinate frame of the camera.
*/

Ray PositionalLight::getShadowFeeler(const dvec3& interceptWorldCoords,
	const dvec3& normal,
	const Frame& eyeFrame) const {
	/* 386 - todo */
	dvec3 origin(0, 0, 0);
	dvec3 dir(1, 1, 1);
	Ray shadowFeeler(origin, dir);
	return shadowFeeler;
}

/**
 * @fn	color SpotLight::illuminate(const dvec3 &interceptWorldCoords,
 *									const dvec3 &normal, const Material &material,
 *									const Frame &eyeFrame, bool inShadow) const
 * @brief	Computes the color this light produces in raytracing applications.
 * @param	interceptWorldCoords				The surface properties of the intercept point.
 * @param	normal					The normal vector.
 * @param	material			The object's material properties.
 * @param	eyeFrame			The coordinate frame of the camera.
 * @param	inShadow			true if the point is in a shadow.
 * @return	The color produced at the intercept point, given this light.
 */

color SpotLight::illuminate(const dvec3& interceptWorldCoords,
	const dvec3& normal,
	const Material& material,
	const Frame& eyeFrame,
	bool inShadow) const {

	if (isInSpotlightCone(pos, spotDir, fov, interceptWorldCoords)) {
		// comment out fallOffFactor for project
        double spotCutOffCosine = glm::cos(fov / 2.0);
        double spotCosine = glm::dot(spotDir, glm::normalize(interceptWorldCoords - pos));
        double fallOffFactor = 1.0 - (1.0 - spotCosine) / (1.0 - spotCutOffCosine);

		return fallOffFactor * PositionalLight::illuminate(interceptWorldCoords, normal, material, eyeFrame, inShadow);
	}
	return black;
}

/**
* @fn	void setDir (double dx, double dy, double dz)
* @brief	Sets the direction of the spotlight.
* @param	dx		x component of the direction
* @param	dy		y component of the direction
* @param	dz		z component of the direction
*/

void SpotLight::setDir(double dx, double dy, double dz) {
	spotDir = glm::normalize(dvec3(dx, dy, dz));
}

/**
* @fn	SpotLight::isInSpotlightCone(const dvec3& spotPos, const dvec3& spotDir, double spotFOV, const dvec3& intercept)
* @brief	Determines if an intercept point falls within a spotlight's cone.
* @param	spotPos		where the spotlight is positioned
* @param	spotDir		normalized direction of spotlight's pointing direction
* @param	spotFOV		spotlight's field of view, which is 2X of the angle from the viewing axis
* @param	intercept	the position of the intercept.
*/

bool SpotLight::isInSpotlightCone(const dvec3& spotPos,
	const dvec3& spotDir,
	double spotFOV,
	const dvec3& intercept) {

	double spotCutOffCosine = glm::cos(spotFOV / 2.0);
	double spotCosine = glm::dot(spotDir, glm::normalize(intercept - spotPos));

	return spotCutOffCosine < spotCosine;
}

color DirectionalLight::illuminate(const dvec3& interceptWorldCoords,
    const dvec3& normal,
    const Material& material,
    const Frame& eyeFrame,
    bool inShadow) const {
    if (!this->isOn) return black;

    dvec3 lightVector = -dir; // Light "comes from" opposite the direction
    dvec3 viewVector = glm::normalize(eyeFrame.origin - interceptWorldCoords);
    dvec3 reflectionVector = glm::reflect(-lightVector, normal);

    color ambient = ambientColor(material.ambient, lightColor);
    if (inShadow) return ambient;

    color diffuse = diffuseColor(material.diffuse, lightColor, lightVector, normal);
    color specular = specularColor(material.specular, lightColor, material.shininess, reflectionVector, viewVector);

    return glm::clamp(ambient + diffuse + specular, 0.0, 1.0);
}

bool DirectionalLight::pointIsInAShadow(const dvec3& intercept,
    const dvec3& normal,
    const vector<VisibleIShapePtr>& objects,
    const Frame& eyeFrame) const {

    dvec3 directionToLight = -dir;
    Ray shadowRay(intercept + EPSILON * normal, directionToLight);
    OpaqueHitRecord hit;

    for (auto& obj : objects) {
        hit.t = FLT_MAX;
        obj->findClosestIntersection(shadowRay, hit);

        if (hit.t < FLT_MAX) {
            if (hit.material.isDielectric) continue;
            return true;
        }
    }
    return false;
}


Ray DirectionalLight::getShadowFeeler(const dvec3& interceptWorldCoords,
    const dvec3& normal,
    const Frame& eyeFrame) const {
    return Ray(interceptWorldCoords + EPSILON * normal, -dir);
}
