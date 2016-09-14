

#include "Camera.h"
#include <math.h>
#pragma warning( disable  : 4996 )
#define _USE_MATH_DEFINES
# define M_PI 3.14159265358979323846  /* pi */


Camera::Camera()
{
}

void Camera::createImage() {

	FILE *fp = fopen("image.ppm", "wb"); /* b - binary mode */
	(void)fprintf(fp, "P6\n%d %d\n255\n", imageSizeY, imageSizeZ);
	for (int i = 0; i < imageSizeZ; i++)
	{
		for (int n = imageSizeY-1; n >= 0; n--)
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
int Camera::checkTriangleHits(std::vector<Triangle::tri>  traingles, int camera) {
	
	//Y>Z
	float fovZ = M_PI/4;
	float fovY = fovZ* imageSizeZ/imageSizeY;
	Direction D;
	Triangle T;
	glm::vec3 imagePoint;
	glm::vec3 rayDirection;
	glm::vec3 pixelColor;
	float xx = -1.f;
	int hit=1;

	for (float i = 0; i < imageSizeZ; i++) {
		for (float n = 0; n < imageSizeY; n++) {


			//map xx and yy to image plane            
			float yy = tan(fovZ / 2) * (2 * n - imageSizeY) / float(imageSizeY);
			float zz = tan(fovY / 2) * (imageSizeZ - 2 * i) / float(imageSizeZ);
			//std::cout << yy << '\n';
			//construct ray

			//new origin for each pixelvalue from -1 to +1
			imagePoint = glm::vec3(0.0f , -1.0f + (deltaDistY/2) + deltaDistY*n,-1.0f + (deltaDistZ / 2) + deltaDistZ*i);
			//raydirection
			rayDirection = D.calculateRayDirection(imagePoint,camera) - glm::vec3(0.0f,  yy ,zz);
			//std::cout << rayDirection .x <<" : " << rayDirection.y << " : " << rayDirection .z<< std::endl;

			//check if triangle intersection
	
			hit = T.molllerTrombore(traingles, imagePoint, rayDirection, pixelColor);
			//std::cout <<"hit : " <<  hit << '\n';
			if (hit) {
				
				image[i][n][0] = pixelColor.x;
				image[i][n][1] = pixelColor.y;
				image[i][n][2] = pixelColor.z;
			}
		}
		//std::cout << i << "st iteration" << std::endl;
	}
	//create image
	createImage();
	
	//end
	return 0;
}

Camera::~Camera()
{

}
