

#include "Camera.h"
#pragma warning( disable  : 4996 )


Camera::Camera()
{
}

void Camera::createImage() {

	FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
	(void)fprintf(fp, "P6\n%d %d\n255\n", iamgeSize, iamgeSize);
	for (int i = 0; i < iamgeSize; ++i)
	{
		for (int n = 0; n < iamgeSize; ++n)
		{
			static unsigned char color[3];
			color[0] = image[i][n][0];  /* red */
			color[1] = image[i][n][1];  /* green */
			color[2] = image[i][n][2];  /* blue */
			(void)fwrite(color, 1, 3, fp);
		}
	}
	(void)fclose(fp);

}

//check if the ray from the image plane hits a triangle.
int Camera::checkTriangleHits(std::vector<Triangle::tri>  & traingles) {
	// Set up image !!!!!!!!!!!! BETA AS FUCK
	image.resize(iamgeSize);
	for (int i = 0; i < iamgeSize; ++i) {
		image[i].resize(iamgeSize);

		for (int j = 0; j < iamgeSize; ++j)
			image[i][j].resize(3);
	}


	Direction D;
	Triangle T;
	glm::vec3 rayOrigin;
	glm::vec3 rayDirection;
	int hit;
	for (int i = 0; i < iamgeSize; i++) {
		for (int n = 0; n < iamgeSize; n++) {
			//new origin for each pixelvalue from -1 to +1
			rayOrigin = glm::vec3(0 , -1 + (deltaDist/2) + deltaDist*i,-1 + (deltaDist / 2) + deltaDist*n);
			//raydirection
			rayDirection = D.calculateRayDirection(rayOrigin);

			//check if triangle intersection

			hit = T.molllerTrombore(traingles, rayOrigin, rayDirection);
			std::cout << hit << '\n';
			if (hit) {
				image[i][n][0] = 255;
				image[i][n][1] = 255;
				image[i][n][3] = 255;
				std::cout << "hit" << i << " " << n << '\n';			
			}

		}
	}
	//create image
	createImage();
	
	//end
	return 0;
}

Camera::~Camera()
{
}
