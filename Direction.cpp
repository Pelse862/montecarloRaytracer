#include "Direction.h"

Direction::Direction()
{
}

glm::vec3 Direction::calculateRayDirection(glm::vec3 endPos, int camera) {
	if(camera == 1)return endPos - Camera::getCameraPosition1();
	return endPos - Camera::getCameraPosition2();
}

Direction::~Direction()
{
}
