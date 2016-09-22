#pragma once

#include "Pixel.h"
#include "glm.hpp"
#include "Direction.h"
#include "Triangle.h"
#include <iostream>
#include <vector>
using std::vector;

//small size for fast rendering
const int imageSizeY = 1400;
const int imageSizeZ = 1000;

class Camera
{		
	friend class Camera;
	public:
		
		Camera();

		//different position is used depending on user input
		static glm::vec3 getCameraPosition1() { return glm::vec3(-1.0f, 0.1f, 0.0f); }
		static glm::vec3 getCameraPosition2() { return glm::vec3(-2.0f, 0.0f, 0.0f); }
		
		int checkTriangleandSphereHits(int camera);
		glm::vec3 returnPixel(Ray *r, Triangle *T,  int nrBounces);
		//creates an image and saves it into ppm format.
		void createImage();
		
		~Camera();
		
		
	private:

		float deltaDistY = 2.0f / imageSizeY;
		float deltaDistZ = 2.0f / imageSizeZ;
		vector<vector<glm::vec3> > image =
			vector<vector<glm::vec3 > >(imageSizeZ, vector<glm::vec3 >(imageSizeY, glm::vec3(0.0f, 0.0f, 0.0f)));

};

