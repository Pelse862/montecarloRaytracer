#include "Direction.h"



Direction::Direction()
{
}

glm::vec3 Direction::calculateRayDirection(glm::vec3 endPos) {
	Camera C;
	return endPos - C.returnCameraPos();
}

Direction::~Direction()
{
}
