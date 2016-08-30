#pragma once
#include "ColorDbl.h"
#include "Ray.h"
class Pixel
{
	public:
		Pixel();
		~Pixel();
	private:
		ColorDbl pixelColor;
		Ray rays;

};

