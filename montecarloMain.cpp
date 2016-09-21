#include <iostream>
#include <vector>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>

#include "glm.hpp"
#include "Scene.h"
#include "Camera.h"
#include "Triangle.h"
#include "Light.h"

using namespace std;

int main() {
	bool running = true;
	int camera = 1;
	Scene S;
	vector<glm::vec3> rommTriangles;
	vector<Triangle::tri> rommTrianglesWithProperties;
	std::vector<Triangle::sphere> spheres;
	Triangle T;
	Light L;
	Camera C;
	int in;

	//set room propertis
	T.setRoom(rommTriangles);
	T.setTriangles(rommTriangles, rommTrianglesWithProperties);
	T.setSpheres(spheres);
	L.setLight(rommTriangles, rommTrianglesWithProperties);
	



	while (running) {

		std::cout << "choose camera (1/2)" << '\n';
		std::cin >> camera;
		while (camera != 1 && camera != 2) {
			std::cout << "try again : ";
			std::cin >> camera;
		}

		//right now this also creates an image
		C.checkTriangleandSphereHits(rommTrianglesWithProperties, spheres , camera);

		std::cout << "So fucking DONE, Run another image? (1/0) : ";
		std::cin >> in;
		
		while (in != 0 && in != 1) {
			std::cout << "try again : ";
			std::cin >> in;
		}
		if (in == 0)break;
		
	}
	return 0;
}