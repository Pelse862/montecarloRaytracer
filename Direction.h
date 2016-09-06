#pragma once
#include "vec3.hpp"
#include <vector>
class Direction
{
	public:
		Direction();

		glm::vec3 calculateDirection(glm::vec3 startPos, glm::vec3 endPos);

		~Direction();
	private: 
	//Create a vector that describes the ray direction

	std::vector<glm::vec3> direction;
};

