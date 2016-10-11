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
		v1 = -directionIn - glm::dot(-directionIn, normal)*normal;
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
inline float getRandominclinationValue()
{
	std::random_device generator;
	std::mt19937 re(generator());
	std::uniform_real_distribution<float> distance(0.0f, 1.0f);
	return distance(re);

}

inline float getRandomAzimuthValue()
{
	std::random_device generator;
	std::mt19937  distribution(generator());
	std::uniform_real_distribution<float> distance(-1.0f, 1.0f);
	return distance(distribution);
}

Direction::~Direction()
{
}
