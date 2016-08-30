#pragma once

#include "ColorDbl.h"
#include "Ray.h"



const int WIDTH = 1000;
const int HEIGHT = 1000;

class Pixel
{
	public:
		Pixel();
		//dummy declaration
		void render();
		~Pixel();
	
	private:
		ColorDbl pixelColor;
		Ray rays;

};

