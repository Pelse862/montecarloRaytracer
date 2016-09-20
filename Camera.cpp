

#include "Camera.h"
#include <math.h>
#pragma warning( disable  : 4996 )
# define M_PI 3.14159265358979323846  /* pi */


Camera::Camera()
{
	//no need atm since Camera is a static position
}

void Camera::createImage() {

	FILE *fp = fopen("image.ppm", "wb"); /* b - binary mode */
	(void)fprintf(fp, "P6\n%d %d\n255\n", imageSizeY, imageSizeZ);
	for (int i = imageSizeZ-1; i >= 0; i--)
	{
		for (int n = imageSizeY-1; n >=0; n--)
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
int Camera::checkTriangleandSphereHits(std::vector<Triangle::tri>  traingles, std::vector<Triangle::sphere> spheres, int camera) {
	
	//classobjects needed
	Direction D;
	Triangle T;
	//ray variables
	glm::vec3 imagePoint;
	glm::vec3 rayDirection;
	glm::vec3 instersectionPointTriangle, instersectionPointSphere;
	glm::vec3 pixelColorTriangle, pixelColorSphere, temp;
	//perspective values
	float py;
	float pz;
	//Y>Z
	float fovZ = M_PI / 4;
	float fovY = fovZ* float(imageSizeZ) / float(imageSizeY);
	float tanZ = tan(fovZ / 2);
	float tanY = tan(fovY / 2);
	for (float i = 0; i < imageSizeZ; i++) {	
		for (float n = 0; n < imageSizeY; n++) {

			//calculate perspective y and z.            
			py = tanZ * (2 * n - imageSizeY) / float(imageSizeY);
			pz = tanY * (imageSizeZ - 2 * i) / float(imageSizeZ);

			//new origin for each pixelvalue from -1 to +1
			imagePoint = glm::vec3(0.0f , -1.0f + (deltaDistY/2) + deltaDistY*n,-1.0f + (deltaDistZ / 2) + deltaDistZ*i);
			
			//raydirection combined with the perspective vec
			rayDirection = D.calculateRayDirection(imagePoint,camera) + glm::vec3(0.0f,  py ,pz);

			//check if triangle intersection
			T.molllerTrombore(traingles, imagePoint, rayDirection, instersectionPointTriangle, pixelColorTriangle);
		
			//check if sphere intersection
			T.sphereIntersect(spheres, rayDirection, imagePoint, instersectionPointSphere, pixelColorSphere );
			
			//since sphere and triangle has deifferent intersection this is needed 
			temp = glm::distance(imagePoint, instersectionPointTriangle) > glm::distance(imagePoint, instersectionPointSphere) ?
							pixelColorSphere : pixelColorTriangle;
			
			//set color
			image[i][n][0] = temp.x;
			image[i][n][1] = temp.y;
			image[i][n][2] = temp.z;
			
		}
	}

	//create image 
	createImage();
	
	//end rendering
	return 0;
}

Camera::~Camera()
{

}
