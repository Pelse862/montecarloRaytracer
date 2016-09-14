#pragma once

#include "Pixel.h"
#include "glm.hpp"
#include "Direction.h"
#include "Triangle.h"
#include <iostream>
#include <vector>
using std::vector;

//small size for fast rendering
const int imageSizeY = 1200;
const int imageSizeZ = 1000;

class Camera
{	
	//...
	friend class Direction;
	public:

		Camera();
		static glm::vec3 getCameraPosition1() { return glm::vec3(-1.0f, 0.0f, 0.0f); }

		static glm::vec3 getCameraPosition2() { return glm::vec3(-2.0f, 0.0f, 0.0f); }

		void caluclateEye2Image();
		int checkTriangleHits(std::vector<Triangle::tri>  traingles, int camera);
		~Camera();
		//dummy declaration
		void createImage();
		
	private:

		float deltaDistY = 2.0f / imageSizeY;
		float deltaDistZ = 2.0f / imageSizeZ;
		vector<vector<vector<float> > > image =
			vector<vector<vector<float> > >(imageSizeZ, vector<vector<float> >(imageSizeY, vector<float>(3, 0.5f)));


		
		

};

