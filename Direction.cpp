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

glm::vec3 Direction::calculateBounce( Ray r, glm::vec3 normal, Triangle::material mat) {
	glm::vec3 directionIn;
	glm::vec3 v1,v2,axis;
	float teta, phi;
	float sqrtVal;
	if (mat.isDiffuse) 
	{
		float randomValInc = getRandominclinationFloat();
		float randomValAzi = getRandominclinationFloat();
		teta = randomValInc*M_PI * 2.f;
		phi = acos(randomValAzi);
		v1 = glm::vec3(cos(teta)*sin(phi), sin(phi)*sin(teta), cos(phi));
		return v1;
	}
	else 
	{
		directionIn = glm::normalize(r.getDirection());
		return (directionIn - 2 * glm::dot(directionIn, normal)*normal);
	}



}
//should not be uniform
inline float getRandominclinationFloat()
{
	std::random_device generator;
	std::mt19937 distribution(generator());
	std::uniform_real_distribution<float> distance(0.0f, 1.f);
	return distance(distribution);

}



Direction::~Direction()
{
}

