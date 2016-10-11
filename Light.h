#include "glm.hpp"
#include <stdlib.h>
#include <iostream>
#include "Triangle.h"
#pragma once
class Light {

	public:

		//constructor
		Light();

		glm::vec3 getLightPosition() { return position; }

		glm::vec3 getlightIntensity() { return lightIntenisity; }
		glm::vec3 getLocalLight(Ray r,glm::vec3 intersection, Triangle T, int idS, int idT, glm::vec3 normal,bool sphereHit);

		//this is not correct just to se if things work
		glm::vec3 getlight() { return lightIntenisity; }
		glm::vec3 getAreaLightIntensity() { return areaLightIntensity; };

		~Light();

	private:
		glm::vec3 position;
		glm::vec3 lightIntenisity;
		glm::vec3 areaLightIntensity;

};