#pragma once

#include "Pixel.h"
#include "glm.hpp"
#include "Direction.h"
#include "Triangle.h"
#include <iostream>
#include <vector>
using std::vector;

//small size for fast rendering
const int imageSize = 1000;

class Camera
{	
	//...
	friend class Direction;
	public:

		Camera();
		static glm::vec3 getCameraPosition() { return glm::vec3(-1.0f, 0.0f, 0.0f); }

		void caluclateEye2Image();
		int checkTriangleHits(std::vector<Triangle::tri>  traingles);
		~Camera();
		//dummy declaration
		void createImage();
		
	private:

		float deltaDist = 2.0f / imageSize;
		vector<vector<vector<float> > > image =
			vector<vector<vector<float> > >(imageSize, vector<vector<float> >(imageSize, vector<float>(3, 0.5f)));


		
		

};

