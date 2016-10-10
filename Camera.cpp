

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
	glm::vec3 pixelColor = glm::vec3(0.f,0.f,0.f);
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
			for (int k = 0; k < 4; k++) {
				originPoint = glm::vec3(0.0f,
					-1.0f + (deltaDistY / 2) + getRandomFloat(deltaDistY / 2) + deltaDistY*n,
					-1.0f + (deltaDistZ / 2) + getRandomFloat(deltaDistZ / 2) + deltaDistZ*i
				);

				//raydirection combined with the perspective vec
				rayDirection = D.calculateRayDirection(originPoint, camera) + glm::vec3(0.0f, py, pz);

				r.setRayDirection(rayDirection);
				r.setRayOrigin(originPoint);
				pixelColor += returnPixel(r, T, 2);

			}
			
			
			image[i][n] = pixelColor;
			for (int k = 0; k < 2; ++k) {
				if (largest < image[i][n][k])largest = image[i][n][k];
			}
			pixelColor = glm::vec3(0.f, 0.f, 0.f);
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
	Direction D;
	Light L;

	int idT = -1, idS = -1;

	r.setHitS(false);
	r.setHitT(false);
	bool shadow = false;;
	glm::vec3 normal = glm::vec3(0.f, 0.f, 0.f); 
	glm::vec3 normalT = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 normalS = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 result = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 pixelColorT = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 pixelColorS = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 intersectionpointT = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 intersectionpointS = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 directionnormalizedOut = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 intersection = glm::vec3(0.f, 0.f, 0.f);
	bool material;
	bool sphereHit = false;
	//check hits versus all triangle
	T.molllerTrombore(T.getTriangles(), r, intersectionpointT, pixelColorT, idT);
	//check hits vs all spheres
	T.sphereIntersect(T.getSpheres(), r, intersectionpointS, pixelColorS, normalS, idS);

	float point2sphere = glm::length(intersectionpointS - r.getRayorigin());
	float point2triangle = glm::length(intersectionpointT - r.getRayorigin());
	if (idT != -1 && point2sphere > point2triangle)
	{
		result = pixelColorT;
		normalT = glm::normalize( T.getTriangles().at(idT).normal ) ;
		directionnormalizedOut = -glm::normalize(r.getDirection());

		if (glm::dot(normalT, directionnormalizedOut) < 0)normalT = -normalT;
		
		intersectionpointT = intersectionpointT + 0.01f*normalT;

		intersection = intersectionpointT;
		shadow = castShadowRay(r, intersectionpointT, T);
		material = T.getTriangleMaterial(idT);
		normal = normalT;
	
	}
	else if (idS != -1)
	{	
		sphereHit = true;
		result = pixelColorS;
		intersection = intersectionpointS;
		shadow = castShadowRay(r, intersectionpointS, T);
		material = T.getSphereMaterial(idS);
		normal = normalS;
	
	}
	else
	{
		std::cout << "no HIT" << std::endl;
	}
		

	result = L.getLocalLight(r,intersection, T, idS, idT, normal, sphereHit);

	//calculate new ray from intersectionpoint
	r.setRayDirection( D.calculateBounce(r, normal, material) );
	r.setRayOrigin(intersection);

	if (shadow)return result*0.1f + 0.05f*returnPixel(r, T, nrbounces - 1);
	if (!material)return returnPixel(r, T, 1);
	return 0.5f*(result + 0.1f*returnPixel(r, T,  nrbounces-1));
}


bool Camera::castShadowRay(Ray & r, glm::vec3 intersection, Triangle T)
{
	int idS = -1.f,idT = -1.f;
	Ray shadowRay;
	Light L;
	bool returnState = false;
	glm::vec3 interS = glm::vec3(0.f,0.f,0.f), interT = glm::vec3(0.f, 0.f, 0.f);
	shadowRay.setHitS(false);
	shadowRay.setHitT(false);
	shadowRay.setRayOrigin(intersection);
	shadowRay.setRayDirection(glm::normalize ( L.getLightPosition() - intersection) ) ;

	T.molllerTrombore(T.getTriangles(), shadowRay, interT, glm::vec3(0.f, 0.f, 0.f), idT);

	T.sphereIntersect(T.getSpheres(), shadowRay, interS, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f,0.f,0.f), idS);
	
	double intersection2light_2 = glm::length(L.getLightPosition() - intersection);
	double intersection2triangle_2 = glm::length(interT - intersection);
	double intersection2sphere_2 = glm::length(interS - intersection);
	

	if (intersection2triangle_2 <= intersection2light_2 ) {
		returnState = true;
	}
	else if (intersection2sphere_2 <= intersection2light_2) {
		returnState = true;
	}

	return returnState;
}


Camera::~Camera()
{
	std::cout << "camera ended : ";
}
inline float getRandomFloat(float deltadist)
{
	std::random_device generator;
	std::uniform_real_distribution<float> distance(-deltadist, deltadist);
	return distance(generator);
}