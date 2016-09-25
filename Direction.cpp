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
glm::vec3 Direction::calculateBounce(Triangle *t, Ray *r, glm::vec3 normal) {
	glm::vec3 directionIn;
	directionIn = glm::normalize(r->getDirection());
	// if the plane normal is poointing i nthe wrong direction... 
	// TODO: this will have to be corrected later wont work with transparancy I think
	//float angle = acos(glm::dot(normal, directionIn) / (glm::length(normal)*glm::length(direction)));
	//if (angle> M_PI / 2 || angle > -M_PI / 2) normal = -normal;


	return (directionIn-2*glm::dot(directionIn,normal)*normal);

}


Direction::~Direction()
{
}
