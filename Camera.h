#pragma once

#include "Pixel.h"
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
const int imageSizeY = 800;
const int imageSizeZ = 600;

class Camera
{		
	friend class Camera;
	public:
		
		Camera();

		//different position is used depending on user input
		static glm::vec3 getCameraPosition1() { return glm::vec3(-1.0f, 0.f, 0.0f); }
		static glm::vec3 getCameraPosition2() { return glm::vec3(-2.0f, 0.0f, 0.0f); }
		int checkTriangleandSphereHits(int camera);
		
		//calculate pixelvalues 
		glm::vec3 returnPixel(Ray r, Triangle T,  int nrBounces);
		
		//return random point on triangle

		//creates an image and saves it into ppm format.
		void createImage();
		bool castShadowRay(Ray & r, float & nrPointArea, glm::vec3 intersection, Triangle T, Light L);
		~Camera();
			
	private:
		float deltaDistY = 2.0f / imageSizeY;
		float deltaDistZ = 2.0f / imageSizeZ;
		vector<vector<glm::vec3> > image =
			vector<vector<glm::vec3 > >(imageSizeZ, vector<glm::vec3 >(imageSizeY, glm::vec3(0.0f, 0.0f, 0.0f)));

};

inline float getRandomFloat(float deltaDist);
inline void pointLight(bool &returnState, Light L, Triangle T, glm::vec3 intersection);
inline void areaLightpoints(Triangle t, float & contribution, glm::vec3 intersection, bool &returnState);
inline void Barycentric(Triangle::tri t, glm::vec3 & point);
