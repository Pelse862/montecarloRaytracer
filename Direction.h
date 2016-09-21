#pragma once
#include "vec3.hpp"
#include "Triangle.h"
#include "Camera.h"
#include <vector>
class Direction
{
	public:
		Direction();

		glm::vec3 calculateRayDirection(glm::vec3 startPos,int camera);

		glm::vec3 calculateBounce(Triangle *T, Ray *r, glm::vec3 surfacePoint, int id, int ident);

		~Direction();
	private: 
		//Create a vector that describes the ray direction
		glm::vec3 direction = glm::vec3(0.f,0.f,0.f);
};

