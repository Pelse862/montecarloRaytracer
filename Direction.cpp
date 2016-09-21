#include "Direction.h"
# define M_PI 3.14159265358979323846  /* pi */

Direction::Direction()
{
}

glm::vec3 Direction::calculateRayDirection(glm::vec3 endPos, int camera) {
	if(camera == 1)return endPos - Camera::getCameraPosition1();
	return endPos - Camera::getCameraPosition2();
}

//this should be perfect reflection model, it is wrong but easy to implement
glm::vec3 Direction::calculateBounce(Triangle *t, Ray *r, glm::vec3 surfacePoint, int id, int ident) {
	glm::vec3 normal;
	glm::vec3 directionIn;
	if (id == 1) {
		normal = glm::vec3(2 * surfacePoint.x, 2 * surfacePoint.y, 2 * surfacePoint.z);
	}
	else {
		normal = t->getTriangles().at(id).normal;

	}
	normal = glm::normalize(normal);

	directionIn = glm::normalize(r->getDirection());
	// if the plane normal is poointing i nthe wrong direction... 
	// TODO: this will have to be corrected later wont work with transparancy I think
	if (glm::dot(normal, directionIn) > M_PI / 2 ||
		glm::dot(normal, directionIn) > -M_PI / 2) normal = -normal;


	return (directionIn-2*glm::dot(directionIn,normal)*normal);

}


Direction::~Direction()
{
}
