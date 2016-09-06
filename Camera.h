#pragma once

#include "Pixel.h"
#include "glm.hpp"
#include "Direction.h"
#include "Triangle.h"
#include <iostream>
#include <vector>
using std::vector;

//small size for fast rendering
const int imageSize = 30;

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

		float deltaDist = 2 / imageSize;
		glm::vec3 cameraPosition = glm::vec3(-1, 0, 0);
		vector<vector<vector<float> > > image =
			vector<vector<vector<float> > >(imageSize, vector<vector<float> >(imageSize, vector<float>(3, 0.f)));


		
		

};

