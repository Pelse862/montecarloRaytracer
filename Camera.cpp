

#include "Camera.h"
#include "Light.h"
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
	Direction D;// = new Direction();

	Triangle T;// = new Triangle();

	Ray r;
	//ray variables
	glm::vec3 originPoint;
	glm::vec3 rayDirection;

	//perspective values
	
	float py;
	float pz;
	//Y>Z
	float fovZ = M_PI / 4;
	float fovY = fovZ* float(imageSizeZ) / float(imageSizeY);
	float tanZ = tan(fovZ / 2);
	float tanY = tan(fovY / 2);
	int id = -1;
	float largest = 0;

	for (float i = 0; i < imageSizeZ; ++i) {	
		for (float n = 0; n < imageSizeY; ++n) {

			//calculate perspective y and z.            
			py = tanZ * (2 * n - imageSizeY) / float(imageSizeY);
			pz = tanY * (imageSizeZ - 2 * i) / float(imageSizeZ);

			//new origin for each pixelvalue from -1 to +1
			originPoint = glm::vec3(0.0f , -1.0f + (deltaDistY/2) + deltaDistY*n,-1.0f + (deltaDistZ / 2) + deltaDistZ*i);
			
			//raydirection combined with the perspective vec
			rayDirection = D.calculateRayDirection(originPoint,camera) + glm::vec3(0.0f,  py ,pz);

			r.setRayDirection(rayDirection);
			r.setRayOrigin(originPoint); 
			glm::vec3 pixelColor = returnPixel(r, T , 3 );

			
			image[i][n] = pixelColor;
			for (int k = 0; k < 3; ++k) {
				if (largest < image[i][n][k])largest = image[i][n][k];
			}
		}
	}
	std::cout << largest << ": largest"<<std::endl;
	for (float i = 0; i < imageSizeZ; ++i) {
		for (float n = 0; n < imageSizeY; ++n) {
			image[i][n] = 255.f*sqrt(image[i][n] / largest);
		}
	}

	//create image 
	createImage();
	
	//end rendering
	return 0;
}



glm::vec3 Camera::returnPixel(Ray r, Triangle T, int nrbounces) {
	//std::cout << "bounce : " << nrbounces << '\n';
	if (nrbounces == 0)return glm::vec3(0.f, 0.f, 0.f);

	int idT = 0;
	int idS = -1;
	glm::vec3 pixelColor, pixelColor2;
	glm::vec3 instersectionPointTriangle = glm::vec3(100000.f, 100000.f, 100000.f);
	glm::vec3 instersectionPointSphere;
	glm::vec3 normal;
	Ray r2;
	r2.setRayDirection(r.getDirection());
	r2.setRayOrigin(r.getRayorigin());
	glm::vec3 pixelColorTriangle, pixelColorSphere, newOrigin;
	Direction D;
	Light L;
	//check if triangle intersection
	T.molllerTrombore(T.getTriangles(), r, instersectionPointTriangle, pixelColorTriangle, idT);

	//check if sphere intersection
	T.sphereIntersect(T.getSpheres(), r, instersectionPointSphere, pixelColorSphere, idS);

	//since sphere and triangle has deifferent intersection this is needed 
	if (glm::distance(r.getRayorigin(), instersectionPointTriangle)
		> glm::distance(r.getRayorigin(), instersectionPointSphere))
	{
		pixelColor = pixelColorSphere;
		normal = instersectionPointSphere - T.getSpheres().at(idS).center;
		normal = glm::normalize(normal);
		newOrigin = instersectionPointSphere + 0.105f*(normal);
		r.setRayOrigin(newOrigin);
		r.setRayDirection(glm::normalize(L.getLightPosition() - newOrigin));
		T.molllerTrombore(T.getTriangles(), r, instersectionPointTriangle, pixelColor2, idS);
		T.sphereIntersect(T.getSpheres(), r, instersectionPointSphere, pixelColor2, idT);
		if (glm::distance(r.getRayorigin(), L.getLightPosition()) < glm::distance(r.getRayorigin(), instersectionPointSphere
		)) {
			//std::cout << "SR hit sphere" << std::endl;
			return glm::vec3(0.f, 0.f, 0.f);
		}

	}
	else {
		pixelColor = pixelColorTriangle;
		normal = T.getTriangles().at(idT).normal;
		float angle =acos(glm::dot(normal, -glm::normalize(r.getDirection())) );
		if (angle > M_PI / 2.f) normal = -normal;
		newOrigin = instersectionPointTriangle + 0.1f*(normal);
		r.setRayOrigin(newOrigin);
		r.setRayDirection(glm::normalize(L.getLightPosition() - newOrigin));
		T.molllerTrombore(T.getTriangles(), r, instersectionPointTriangle, pixelColor2, idS);
		T.sphereIntersect(T.getSpheres(), r, instersectionPointSphere, pixelColor2, idT);
		if (glm::distance(r.getRayorigin(), L.getLightPosition()) > glm::distance(r.getRayorigin(), instersectionPointTriangle)
		|| glm::distance(r.getRayorigin(), L.getLightPosition()) > glm::distance(r.getRayorigin(), instersectionPointSphere)
		) {
			//std::cout << "SR hit triangle" << std::endl;

			return glm::vec3(0.f, 0.f, 0.f);
		}
		
	}
	

	

	//calculate new ray from intersectionpoint
	r.setRayDirection( D.calculateBounce(T, r2, normal) );

	return pixelColor + 0.1f*returnPixel(r, T,  nrbounces-1);
}




Camera::~Camera()
{
	std::cout << "camera ended : ";
}
