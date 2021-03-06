#pragma once
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

		void setRayOrigin(glm::vec3 newOrigin) { origin = newOrigin; }

		void setRayDirection(glm::vec3 newDirection) { direction = newDirection; }
		//float, importance for vector
		float getImportance() { return importance; }

		void setImportance(float i) { importance = i; }

		float getHitT() { return hitT; }
		float getHitS() { return hitS; }
		void setHitT(bool t) { hitT = t; }
		void setHitS(bool t) { hitS = t; }

		~Ray();
	private:
		glm::vec3 direction;
		glm::vec3 origin;
		bool hitT,hitS;
		float importance;

};

