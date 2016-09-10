

#include "Camera.h"
#pragma warning( disable  : 4996 )


Camera::Camera()
{
}

void Camera::createImage() {

	FILE *fp = fopen("image.ppm", "wb"); /* b - binary mode */
	(void)fprintf(fp, "P6\n%d %d\n255\n", imageSize, imageSize);
	for (int i = 0; i < imageSize; ++i)
	{
		for (int n = 0; n < imageSize; ++n)
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
int Camera::checkTriangleHits(std::vector<Triangle::tri>  traingles) {
	
	Direction D;
	Triangle T;
	glm::vec3 rayOrigin;
	glm::vec3 rayDirection;
	int hit=1;
	for (float i = 0; i < imageSize; i++) {
		for (float n = 0; n < imageSize; n++) {
			//new origin for each pixelvalue from -1 to +1
			rayOrigin = glm::vec3(0.0f , -1.0f + (deltaDist/2) + deltaDist*i,-1.0f + (deltaDist / 2) + deltaDist*n);
			//raydirection
			rayDirection = D.calculateRayDirection(rayOrigin);
			//std::cout << rayDirection .x <<" : " << rayDirection.y << " : " << rayDirection .z<< std::endl;

			//check if triangle intersection

			hit = T.molllerTrombore(traingles, rayOrigin, rayDirection);
			std::cout <<"hit : " <<  hit << '\n';
			if (hit) {
				
				image[i][n][0] = 255.0f;
				image[i][n][1] = 255.0f;
				image[i][n][2] = 255.0f;
			}
			

		}
		std::cout << i << "st iteration" << std::endl;
	}
	//create image
	createImage();
	
	//end
	return 0;
}

Camera::~Camera()
{
}
