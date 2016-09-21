

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
			color[0] = image[i][n].x;  /* red */
			color[1] = image[i][n].y;  /* green */
			color[2] = image[i][n].z;  /* blue */
			(void)fwrite(color, 1, 3, fp);
		}
	}

	(void)fclose(fp);

}

//check if the ray from the image plane hits a triangle.
int Camera::checkTriangleandSphereHits(int camera) {
	
	//classobjects needed
	Direction D;
	Triangle *T = new Triangle();

	Ray *r = new Ray();
	//ray variables
	glm::vec3 originPoint;
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
	int id = -1;
	for (float i = 0; i < imageSizeZ; i++) {	
		for (float n = 0; n < imageSizeY; n++) {

			//calculate perspective y and z.            
			py = tanZ * (2 * n - imageSizeY) / float(imageSizeY);
			pz = tanY * (imageSizeZ - 2 * i) / float(imageSizeZ);

			//new origin for each pixelvalue from -1 to +1
			originPoint = glm::vec3(0.0f , -1.0f + (deltaDistY/2) + deltaDistY*n,-1.0f + (deltaDistZ / 2) + deltaDistZ*i);
			
			//raydirection combined with the perspective vec
			rayDirection = D.calculateRayDirection(originPoint,camera) + glm::vec3(0.0f,  py ,pz);

			r = new Ray(rayDirection, originPoint);

			//check if triangle intersection
			T->molllerTrombore(T->getTriangles(), r, instersectionPointTriangle, pixelColorTriangle, id);
		
			//check if sphere intersection
			T->sphereIntersect(T->getSpheres(), r, instersectionPointSphere, pixelColorSphere );
			
			//since sphere and triangle has deifferent intersection this is needed 
			if (glm::distance(originPoint, instersectionPointTriangle) > glm::distance(originPoint, instersectionPointSphere)) {
				image[i][n] = pixelColorSphere;
				//id = 1
			}
			else {
				image[i][n] = pixelColorTriangle;
			}
			
			
			
		}
	}
	delete r;
	//create image 
	createImage();
	
	//end rendering
	return 0;
}

Camera::~Camera()
{
	std::cout << "camera ended : ";
}
