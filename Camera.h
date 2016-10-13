#pragma once


#include "glm.hpp"
#include "Direction.h"
#include "Triangle.h"
#include "Light.h"

#include <iostream>
#include <vector>
#include <random>

#define I

using std::vector;

//small size for fast rendering
const int imageSizeY = 480;
const int imageSizeZ = 300;

#define samplePerRay 30
#define bounceDepth 8

class Camera
{		
	friend class Camera;
	public:
		Camera();

		//different position is used depending on user input
		static glm::vec3 getCameraPosition1() { return glm::vec3(-1.0f, 0.f, 0.0f); }
		static glm::vec3 getCameraPosition2() { return glm::vec3(-2.0f, 0.0f, 0.0f); }
		//main rendering loop
		int checkTriangleandSphereHits(int camera);
		//calculate pixelvalues 
		glm::vec3 returnPixel(Ray r, Triangle T,  int nrBounces, Light L);
		//creates an image and saves it into ppm format.
		void createImage();
		bool castShadowRay(bool & shadow, bool &areaLightShadow, float & nrPointArea, glm::vec3 intersection, Triangle T, Light L);
		~Camera();
		private:
		float deltaDistY = 2.0f / imageSizeY;
		float deltaDistZ = 2.0f / imageSizeZ;
		vector<vector<glm::vec3> > image =
			vector<vector<glm::vec3 > >(imageSizeZ, vector<glm::vec3 >(imageSizeY, glm::vec3(0.0f, 0.0f, 0.0f)));
};

inline float getRandomFloat(float deltaDist);
inline void pointLight(bool &returnState, Light L, Triangle T, glm::vec3 intersection);
inline void areaLightpoints(Triangle t, float & contribution, glm::vec3 intersection, bool &returnState, Light L);
