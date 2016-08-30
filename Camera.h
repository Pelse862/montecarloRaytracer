#pragma once

#include "Pixel.h"


class Camera
{

	public:

		Camera();
		~Camera();
		//dummy declaration
		void createImage();
		
	private:
		Pixel image[HEIGHT][WIDTH];
		

};

