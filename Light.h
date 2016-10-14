#pragma once

#include "glm.hpp"
#include <stdlib.h>
#include <iostream>
#include "Triangle.h"
#include <random>
#pragma once
class Light {

	public:

		//constructor
		Light();

		glm::vec3 getLightPosition() { return position; }

		glm::vec3 getlightIntensity() { return lightIntenisity; }
		glm::vec3 getLocalLightPoint(Ray r,glm::vec3 intersection, Triangle T, int idS, int idT, glm::vec3 normal,bool sphereHit);
		glm::vec3 getLocalLightArea(float contributuin, Ray r, glm::vec3 intersection, Triangle T, int idS, int idT, glm::vec3 normal, bool sphereHit);

		void setAreaLightPoints(Triangle T);
		std::vector<glm::vec3> getAreaLightPoints() { return AreaLightPoints; }
		//this is not correct just to se if things work
		glm::vec3 getlight() { return lightIntenisity; }
		glm::vec3 getAreaLightIntensity() { return areaLightIntensity; };

		~Light();

	private:
		glm::vec3 position;
		glm::vec3 lightIntenisity;
		glm::vec3 areaLightIntensity;
		std::vector<glm::vec3> AreaLightPoints;
		float contribution;
};

inline void Barycentric(Triangle::tri t, glm::vec3 & point);
inline float getRandomFloat(float deltadist);