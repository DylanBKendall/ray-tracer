/****************************************************
 * 2016-2024 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <vector>
#include "defs.h"
#include "utilities.h"
#include "framebuffer.h"
#include "colorandmaterials.h"
#include "rasterization.h"
#include "io.h"

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

void render() {
	frameBuffer.clearColorBuffer();
	drawLine(frameBuffer, 0, 0, 100, 100, red);
	drawLine(frameBuffer, 100, 100, 200, 100, blue);
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}


int main(int argc, char* argv[]) {

	//graphicsInit(argc, argv, __FILE__);

	//glutDisplayFunc(render);
	//glutReshapeFunc(resize);
	//glutKeyboardFunc(keyboardUtility);
	//glutMouseFunc(mouseUtility);

	//frameBuffer.setClearColor(paleGreen);

	//glutMainLoop();
	double a = 5;
	double b = 6;
	swap(a, b);
	int line = 53;
	double unitX, unitY;
	pointOnUnitCircle(PI, unitX, unitY);
	vector<double> quadratic1 = quadratic(1, 4, 3);
	vector<double> quadratic2 = quadratic(1, 0, 0);
	vector<double> quadratic3 = quadratic(-4, -2, -1);

	std::cout << "True? " << (a == 6 && b == 5) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(3.000000, 3.0000000001) << "  Line: "
		<< (line += 2) << std::endl;

	std::cout << "True? " << !approximatelyEqual(3.000000, 3.1) << "  Line: "
		<< (line += 3) << std::endl;

	std::cout << "True? " << approximatelyZero(0.0000001) << "  Line: "
		<< (line += 3) << std::endl;

	std::cout << "True? " << approximatelyZero(-0.0000001) << "  Line: "
		<< (line += 3) << std::endl;

	std::cout << "True? " << !approximatelyZero(0.1) << "  Line: "
		<< (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(normalizeDegrees(0), 0) << "  Result: "
		<< normalizeDegrees(0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(normalizeDegrees(1.75), 1.75) << "  Result: "
		<< normalizeDegrees(1.75) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(normalizeDegrees(-1), 359) << "  Result: "
		<< normalizeDegrees(-1) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(normalizeDegrees(-721), 359) << "  Result: "
		<< normalizeDegrees(-721) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(normalizeRadians(0), 0) << "  Result: "
		<< normalizeRadians(0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(normalizeRadians(1), 1) << "  Result: "
		<< normalizeRadians(1) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(normalizeRadians(3 * PI), 3.141) << "  Result: "
		<< normalizeRadians(3 * PI) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(normalizeRadians(-31 * PI), 3.141) << "  Result: "
		<< normalizeRadians(-31 * PI) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(rad2deg(2 * PI), 360) << "  Result: "
		<< rad2deg(2 * PI) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(rad2deg(0), 0) << "  Result: "
		<< rad2deg(0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(deg2rad(360), 2 * PI) << "  Result: "
		<< deg2rad(360) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(deg2rad(0), 0) << "  Result: "
		<< deg2rad(0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(min(0, -1, 1), -1) << "  Result: "
		<< min(0, -1, 1) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(max(0, -1, 1), 1) << "  Result: "
		<< max(0, -1, 1) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceFromOrigin(0, 1), 1) << "  Result: "
		<< distanceFromOrigin(0, 1) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceFromOrigin(1, 0), 1) << "  Result: "
		<< distanceFromOrigin(1, 0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceFromOrigin(1.0, 1.0), 1.4142135) << "  Result: "
		<< distanceFromOrigin(1, 1) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceFromOrigin(-10, 30), 31.6227766) << "  Result: "
		<< distanceFromOrigin(-10, 30) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceFromOrigin(0, 0), 0) << "  Result: "
		<< distanceFromOrigin(0, 0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceBetween(0, 0, 1, 1), 1.4142135) << "  Result: "
		<< distanceBetween(0, 0, 1, 1) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceBetween(1, 1, 0, 0), 1.4142135) << "  Result: "
		<< distanceBetween(1, 1, 0, 0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceBetween(10, 10, 11, 11), 1.4142135) << "  Result: "
		<< distanceBetween(10, 10, 11, 11) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceBetween(100, 100, 99, 99), 1.4142135) << "  Result: "
		<< distanceBetween(100, 100, 99, 99) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceBetween(54, 1, -34, -99), 133.2066064) << "  Result: "
		<< distanceBetween(54, 1, -34, -99) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(distanceBetween(0, 0, 0, 0), 0) << "  Result: "
		<< distanceBetween(0, 0, 0, 0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfTriangle(0, 0, 0), -1) << "  Result: "
		<< areaOfTriangle(0, 0, 0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfTriangle(3, 4, 5), 6) << "  Result: "
		<< areaOfTriangle(3, 4, 5) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfTriangle(-3, 4, 5), -1) << "  Result: "
		<< areaOfTriangle(-3, 4, 5) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfTriangle(3, 4, 50), -1) << "  Result: "
		<< areaOfTriangle(3, 4, 50) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfTriangle(0, 0, 3, 0, 0, 4), 6) << "  Result: "
		<< areaOfTriangle(0, 0, 3, 0, 0, 4) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfTriangle(0, 0, 0, 0, 0, 0), -1) << "  Result: "
		<< areaOfTriangle(0, 0, 0, 0, 0, 0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(unitX, -1) << approximatelyEqual(unitY, 0) << "  Result: "
		<< unitX << ", " << unitY << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(pointOnCircle(glm::dvec2(0.0, 0.0), 1.0, PI).x, -1) << approximatelyEqual(pointOnCircle(glm::dvec2(0.0, 0.0), 1.0, PI).y, 0) << "  Result: "
		<< pointOnCircle(glm::dvec2(0.0, 0.0), 1.0, PI).x << ", " << pointOnCircle(glm::dvec2(0.0, 0.0), 1.0, PI).y << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(directionInRadians(dvec2(0, 0), dvec2(-1, 0)), PI) << "  Result: "
		<< directionInRadians(dvec2(0, 0), dvec2(-1, 0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(directionInRadians(dvec2(0, 0), dvec2(2, 2)), 0.78539816) << "  Result: "
		<< directionInRadians(dvec2(0, 0), dvec2(2, 2)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(directionInRadians(dvec2(2, 10), dvec2(3, 11)), 0.78539816) << "  Result: "
		<< directionInRadians(dvec2(2, 10), dvec2(3, 11)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(directionInRadians(dvec2(2, 2), dvec2(2, 0)), 4.7123889804) << "  Result: "
		<< directionInRadians(dvec2(2, 2), dvec2(2, 0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(directionInRadians(dvec2(1, -1), dvec2(1.3420, -1.93969)), 5.06144) << "  Result: "
		<< directionInRadians(dvec2(1, -1), dvec2(1.3420, -1.93969)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(directionInRadians(0, 0, 2, 2), 0.7853981634) << "  Result: "
		<< directionInRadians(0, 0, 2, 2) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(directionInRadians(2, 10, 3, 11), 0.7853981634) << "  Result: "
		<< directionInRadians(2, 10, 3, 11) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(directionInRadians(2, 2, 2, 0), 4.7123889804) << "  Result: "
		<< directionInRadians(2, 2, 2, 0) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(map(2, 0, 5, 10, 11), 10.4) << "  Result: "
		<< map(2, 0, 5, 10, 11) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(quadratic1[0], -3) << approximatelyEqual(quadratic1[1], -1)
		<< "  Result: " << quadratic1 << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(quadratic2[0], 0) << "  Result: "
		<< quadratic2 << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << "  Result: " << quadratic3 << "  Line: " << (line += 2) << std::endl;

	std::cout << "True? " << (doubleIt(dvec2(3, 4)) == dvec2(6, 8)) << "  Result: "
		<< doubleIt(dvec2(3, 4)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << (myNormalize(dvec3(5, 0, 0)) == dvec3(1, 0, 0)) << "  Result: "
		<< myNormalize(dvec3(5, 0, 0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << isOrthogonal(dvec3(5, 0, 0), dvec3(0, 5, 0)) << "  Result: "
		<< isOrthogonal(dvec3(5, 0, 0), dvec3(0, 5, 0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << !isOrthogonal(dvec3(5, 0, 0), dvec3(2, 5, 0)) << "  Result: "
		<< !isOrthogonal(dvec3(5, 0, 0), dvec3(2, 5, 0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << formAcuteAngle(dvec3(5, 0, 0), dvec3(2, 5, 0)) << "  Result: "
		<< formAcuteAngle(dvec3(5, 0, 0), dvec3(2, 5, 0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << !formAcuteAngle(dvec3(5, 0, 0), dvec3(0, 5, 0)) << "  Result: "
		<< !formAcuteAngle(dvec3(5, 0, 0), dvec3(0, 5, 0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << !formAcuteAngle(dvec3(5, -1, 0), dvec3(0, 5, 0)) << "  Result: "
		<< !formAcuteAngle(dvec3(5, -1, 0), dvec3(0, 5, 0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 0.0)), 1.0) << "  Result: "
		<< cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 0.0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 1.0)), 0.707107) << "  Result: "
		<< cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 1.0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(cosBetween(dvec2(-1.0, glm::sqrt(3.0)), dvec2(1.0, glm::sqrt(3.0))), 0.5) << "  Result: "
		<< cosBetween(dvec2(-1.0, glm::sqrt(3.0)), dvec2(1.0, glm::sqrt(3.0))) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(cosBetween(dvec2(-1.0, glm::sqrt(3.0)), dvec2(-1.0, 0.0)), 0.5) << "  Result: "
		<< cosBetween(dvec2(-1.0, glm::sqrt(3.0)), dvec2(-1.0, 0.0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(cosBetween(dvec3(0, -1.0, glm::sqrt(3.0)), dvec3(0, -1.0, 0.0)), 0.5) << "  Result: "
		<< cosBetween(dvec3(0, -1.0, glm::sqrt(3.0)), dvec3(0, -1.0, 0.0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfParallelogram(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)), 1.0) << "  Result: "
		<< areaOfParallelogram(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfParallelogram(dvec3(1.0, 1.0, 1.0), dvec3(1.0, 0.0, 1.0)), 1.41421) << "  Result: "
		<< areaOfParallelogram(dvec3(1.0, 1.0, 1.0), dvec3(1.0, 0.0, 1.0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)), 0.5) << "  Result: "
		<< areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)) << "  Line: " << (line += 3) << std::endl;

	std::cout << "True? " << approximatelyEqual(areaOfTriangle(dvec3(-10.0, -10.0, -10.0), dvec3(-11.0, -10.0, -10.0), dvec3(-10.0, -11.0, -10.0)), 0.5) << "  Result: "
		<< areaOfTriangle(dvec3(-10.0, -10.0, -10.0), dvec3(-11.0, -10.0, -10.0), dvec3(-10.0, -11.0, -10.0)) << "  Line: " << (line += 3) << std::endl;


	return 0;
}