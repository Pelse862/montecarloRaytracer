#pragma once
#include "Vertex.h"
#include "glm.hpp"
class Ray
{
	public:
		Ray();
		Ray(glm::vec3 dir, glm::vec3 O);

		//vector3 with ray direction
		glm::vec3 getDirection() { return direction; }
		//vector3 with origin point for vector 
		glm::vec3 getRayorigin() { return origin; }
		//float, importance for vector
		float getImportance() { return importance; }

		~Ray();
	private:
		glm::vec3 direction;
		glm::vec3 origin;
		bool end;
		float importance;

};

