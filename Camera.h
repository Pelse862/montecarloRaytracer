#pragma once

#include "Pixel.h"


class Camera
{

	public:

		Camera();
		void caluclateEye2Image();
		~Camera();
		//dummy declaration
		void createImage();
		
	private:
		float deltaDist = 2 / 500;
		int cameraPosition[3] = { 0,0,-1 };
		float image[500][500][3];
		
		

};

