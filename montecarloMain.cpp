#include <iostream>
#include <vector>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>

#include "glm.hpp"
#include "Scene.h"
#include "Camera.h"
#include "Triangle.h"

using namespace std;

int main() {
	bool running = true;
	int camera = 1;
	Camera *C = new Camera();
	int in;

	while (running) {

		std::cout << "choose camera (1/2)" << '\n';
		std::cin >> camera;
		while (camera != 1 && camera != 2) {
			std::cout << "try again : ";
			std::cin >> camera;
		}

		//right now this also creates an image
		C->checkTriangleandSphereHits(camera);

		std::cout << "So fucking DONE, Run another image? (1/0) : ";
		std::cin >> in;
		
		while (in != 0 && in != 1) {
			std::cout << "try again : ";
			std::cin >> in;
		}
		if (in == 0)break;
		
	}

	//probably a memory leak: TODO, fix
	delete C;


	return 0;
}