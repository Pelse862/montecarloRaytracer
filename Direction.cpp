#include <random>
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
glm::vec3 Direction::calculateBounce( Ray r, glm::vec3 normal, bool mat) {
	glm::vec3 directionIn;
	glm::vec3 v1,v2,axis;
	float randomValInc = getRandominclinationValue();
	float randomValAzi = getRandomAzimuthValue();

	directionIn = glm::normalize(r.getDirection());
	if (mat) {
		v1 = -directionIn - (-directionIn*normal)*normal;
		axis = v2 = v1 = -v1;
		v1 = v1 * cos(randomValInc) + glm::cross(axis, v1)*sin(randomValInc) + axis*(axis*v1)*(1 - cos(randomValInc));
		v1 += v1 * cos(randomValAzi) + glm::cross(normal, v1)*sin(randomValAzi) + normal*(normal*v1) - (1 - cos(randomValAzi));
		return v1;
	}
	else {
		return (directionIn - 2 * glm::dot(directionIn, normal)*normal);

	}


}
//should not be uniform
inline int getRandominclinationValue()
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 90);
	float value = distribution(generator);  
	return value;
}
inline int getRandomAzimuthValue()
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(-90, 90);
	int value = distribution(generator);
	return value;
}

Direction::~Direction()
{
}
