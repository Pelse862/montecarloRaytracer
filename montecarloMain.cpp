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
	Scene S;
	vector<glm::vec3> room;
	vector<Triangle::tri> rommTriangles;
	Triangle T;
	Camera C;
	T.setRoom(room);
	T.setTriangles(room, rommTriangles);

	//right now this also creates an image
	C.checkTriangleHits(rommTriangles);

	
	/*
	for (auto i : rommTriangles) {
		std::cout << " normal:" << i.normal[0] << " " <<
					i.normal[1] << " " << i.normal[2] << '\n';
	}*/
	
	

	int s;
	cin >>s ; 
	return 0;
}