#include "light.h"
#include "triangle.h"

Light::Light()
{
}
void Light::setLight(std::vector<Triangle::tri> & triangles)

{
	
	triangles.at(19).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(19).vert[0].x;

	//lightObject = new Triangle();

}

glm::dvec3 Light::randomPosition(std::vector<Triangle::tri> & triangles) {

	glm::dvec3 randPos(0.0, 0.0, 0.0);
	//srand((time(NULL)));
	
	randPos.x = triangles.at(31).vert[0].x + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / ((triangles.at(31).vert[1].x) - triangles.at(31).vert[0].x)));
	randPos.y = position.y;
	randPos.z = triangles.at(31).vert[2].z + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / ((triangles.at(31).vert[1].z) - triangles.at(31).vert[2].z)));

	// use this for point light
	//return glm::dvec3(0.5, position.y, -0.5);

	// use this for smooth shadow
	return randPos;
}

glm::dvec3 Light::calculateIntersections() {
	glm::dvec3 intersectionPoint = glm::dvec3(0.0, 0.0, 0.0);

	return intersectionPoint;
}

void Light::computeChildrenRays() {

}

int Light::getType() {
	return LIGHT_SHAPE;
}

glm::dvec3 Light::getColor(int c) {
	return glm::dvec3(1.0, 1.0, 1.0);
}

int Light::getWallIntersectionIndex() {
	return 1;
}

double Light::getRefractiveIndex() {
	return 1.0;
}

glm::dvec3 Light::getIntersectionNormal() {
	return glm::dvec3(0.0, 0.0, 0.0);
}

bool Light::getTransparency() {
	return false;
}
