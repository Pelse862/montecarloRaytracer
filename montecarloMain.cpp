#include <iostream>
#include <vector>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>



#include "Scene.h"
#include "Camera.h"
using namespace std;

int main() {
	Scene S;
	vector<float> room;
	S.setRoom(room);
	Camera C;

	C.createImage();


	int s;
	cin >>s ; 
	return 0;
}