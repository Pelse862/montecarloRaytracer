#pragma once

#include "Pixel.h"
#include "glm.hpp"
#include "Direction.h"
#include "Triangle.h"
#include <iostream>
#include <vector>
using std::vector;

const int iamgeSize = 500;

class Camera
{	
	//....
	friend class Direction;
	public:

		Camera();
		void caluclateEye2Image();
		glm::vec3 returnCameraPos() { return cameraPosition; }
		int checkTriangleHits(std::vector<Triangle::tri>  & traingles);
		~Camera();
		//dummy declaration
		void createImage();
		
	private:

		float deltaDist = 2 / iamgeSize;
		glm::vec3 cameraPosition = glm::vec3(-1, 0, 0);
		vector<vector<vector<float> > > image;

		
		

};

