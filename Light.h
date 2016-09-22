#include "glm.hpp"
#include <stdlib.h>
#include <iostream>
#include "Triangle.h"


#define LIGHT_SHAPE 3

class Light {

	public:

		

		//constructor
		Light();
		glm::vec3 getLightPosition() { return position; }

		//this is not correct just to se if things work
		glm::vec3 getlight() { return lightIntenisity; }

		~Light();



	private:
		glm::vec3 position;
		glm::vec3 lightIntenisity;


};