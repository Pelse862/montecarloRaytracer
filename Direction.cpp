#include "Direction.h"



Direction::Direction()
{
}

glm::vec3 Direction::calculateRayDirection(glm::vec3 endPos) {
	return endPos - Camera::getCameraPosition();
}

Direction::~Direction()
{
}
