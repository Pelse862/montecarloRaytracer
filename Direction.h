#pragma once
#include "vec3.hpp"
#include "Camera.h"
#include <vector>
class Direction
{
	public:
		Direction();

		glm::vec3 calculateRayDirection(glm::vec3 startPos);

		~Direction();
	private: 
		//Create a vector that describes the ray direction
		glm::vec3 direction;
};

