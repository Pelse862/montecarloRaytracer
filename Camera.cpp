
#pragma once
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
	Direction D;// = new Direction();

	Triangle T;// = new Triangle();
	float persenc = 0;
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
	float largestR = 0;
	float largestG = 0;
	float largestB = 0;

	for (float i = 0; i < imageSizeZ; ++i) {	
		for (float n = 0; n < imageSizeY; ++n) {

			//calculate perspective y and z.            
			py = tanZ * (2 * n - imageSizeY) / float(imageSizeY);
			pz = tanY * (imageSizeZ - 2 * i) / float(imageSizeZ);

				

			//new origin for each pixelvalue from -1 to +1
			for (int k = 0; k < 4; k++) {
				originPoint = glm::vec3(0.0f,
					-1.0f + (deltaDistY / 2) + getRandomFloat( deltaDistY ) - deltaDistY/2.f + deltaDistY*n,
					-1.0f + (deltaDistZ / 2) + getRandomFloat( deltaDistZ ) - deltaDistZ/2.f + deltaDistZ*i
				);

				//raydirection combined with the perspective vec
				rayDirection = D.calculateRayDirection(originPoint, camera) + glm::vec3(0.0f, py, pz);

				r.setRayDirection(rayDirection);
				r.setRayOrigin(originPoint);
				pixelColor += returnPixel(r, T, 5);

			}
			
			
			image[i][n] = pixelColor/4.f;
			//get largest value for each channel separatly
			/*
			largestR = (largestR < image[i][n][0]) ?  image[i][n][0] : largestR;
			largestG = (largestG < image[i][n][1]) ?  image[i][n][1] : largestG;
			largestB = (largestB < image[i][n][2]) ?  image[i][n][2] : largestB;
			*/
			for (int k = 0; k < 2; ++k) {
				if (largestR < image[i][n][k])largestR = image[i][n][k];
			}
			pixelColor = glm::vec3(0.f, 0.f, 0.f);
		}
		persenc += 100.f / imageSizeZ;
		std::cout << "\rpercent done of image rendering : "<< persenc << " %";
	}
	//std::cout << largestR << ": largest Red"<<std::endl;
	//std::cout << largestG << ": largest Green" << std::endl;
	//std::cout << largestB << ": largest Blue" << std::endl;

	for (float i = 0; i < imageSizeZ; ++i) {
		for (float n = 0; n < imageSizeY; ++n) {
			image[i][n] = 255.f*sqrt(image[i][n] / largestR);
		}
	}

	//create image 
	createImage();
	
	//end rendering this image
	return 0;
}



glm::vec3 Camera::returnPixel(Ray r, Triangle T, int nrbounces) {
	//std::cout << "bounce : " << nrbounces << '\n';
	if (nrbounces == 0)return glm::vec3(0.f, 0.f, 0.f);
	Direction D;
	Light L;
	Triangle::material material;
	int idT = -1, idS = -1;
	float lightFromAreaLight = 0.f;
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
	
	bool sphereHit = false;
	//check hits versus all triangle
	T.molllerTrombore(T.getTriangles(), r, intersectionpointT, pixelColorT, idT);
	//check hits vs all spheres
	T.sphereIntersect(T.getSpheres(), r, intersectionpointS, pixelColorS, normalS, idS);

	float point2sphere = glm::length(intersectionpointS - r.getRayorigin());
	float point2triangle = glm::length(intersectionpointT - r.getRayorigin());
	if (point2sphere > point2triangle)
	{
		result = pixelColorT;
		normalT = glm::normalize( T.getTriangles().at(idT).normal ) ;
		directionnormalizedOut = -glm::normalize(r.getDirection());
		if (glm::dot(normalT, directionnormalizedOut) <= 0)normalT = -normalT;
		intersectionpointT = intersectionpointT + 0.01f*normalT;
		intersection = intersectionpointT;
		shadow = castShadowRay(r, lightFromAreaLight, intersectionpointT, T, L);
		material = T.getTriangleMaterial(idT);	
		normal = normalT;
	
	}
	else if (idS != -1)
	{	
		sphereHit = true;
		result = pixelColorS;
		intersection = intersectionpointS;
		shadow = castShadowRay(r, lightFromAreaLight, intersectionpointS, T, L );
		material = T.getSphereMaterial(idS);
		normal = normalS;
	
	}
	else
	{
		//std::cout << "no HIT" << std::endl;
		return glm::vec3(0.f, 0.f, 0.f);
	}
		
	result = L.getLocalLight(r, intersection, T, idS, idT, normal, sphereHit);
	
	//calculate new ray from intersectionpoint
	r.setRayDirection( D.calculateBounce(r, normal, material) );
	r.setRayOrigin(intersection);

	//check if ray hits a lightSource
	if (material.isLightSource) {
		//end ray
		return L.getAreaLightIntensity()*1000.f;
	}
	//check if material is a mirror
	else if (material.isSpecular) {
		//get reflective pixelvalue
		return returnPixel(r, T, 1);
	}
	//check if in shadow
	else if (shadow) {
		//send a lower pixel value
		return 0.5f*result + 0.075f*returnPixel(r, T, nrbounces - 1);
	}
	//for diffuse surfaces
	else {
		//continue
		return result + 0.15f*returnPixel(r, T, nrbounces - 1);
	}
}


bool Camera::castShadowRay(Ray & r,float & lightFromAreaLight, glm::vec3 intersection, Triangle T, Light L)
{
	bool returnStatepointLight = false;
	pointLight(returnStatepointLight, L,  T, intersection);
	areaLightpoints(T, lightFromAreaLight, intersection ,returnStatepointLight);


	return returnStatepointLight;
}
//check if point is in shadow for the pointlight
inline void pointLight(bool &returnState, Light L, Triangle T,glm::vec3 intersection)
{
	int idS = -1.f, idT = -1.f;
	Ray shadowRay;
	glm::vec3 interS = glm::vec3(0.f, 0.f, 0.f), interT = glm::vec3(0.f, 0.f, 0.f);
	shadowRay.setHitS(false);
	shadowRay.setHitT(false);
	shadowRay.setRayOrigin(intersection);
	shadowRay.setRayDirection(glm::normalize(L.getLightPosition() - intersection));
	T.molllerTrombore(T.getTriangles(), shadowRay, interT, glm::vec3(0.f, 0.f, 0.f), idT);
	T.sphereIntersect(T.getSpheres(), shadowRay, interS, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), idS);
	float inter2light = glm::length(L.getLightPosition() - intersection);
	float inter2tri = glm::length(interT - intersection);
	float inter2sph = glm::length(interS - intersection);

	if (inter2tri <= inter2light) {
		returnState = true;
	}
	else if (inter2sph <= inter2light) {
		returnState = true;
	}
}
inline void areaLightpoints(Triangle T, float & contribution,glm::vec3 intersection, bool & returnState)
{
	std::vector<glm::vec3> points;
	glm::vec3 p;
	Triangle::tri t1 = T.getTriangles().at(T.getTriangles().size() - 1);
	Triangle::tri t2 = T.getTriangles().at(T.getTriangles().size() - 2);
	glm::vec3 normal = glm::normalize(t1.normal);
	for (int i = 0; i < 3; i++) {
		Barycentric(t1, p);
		p += 0.0001f*normal;
		points.push_back(p);
	}
	normal = glm::normalize(t2.normal);
	for (int i = 0; i < 3; i++) {
		Barycentric(t2, p);
		p += 0.0001f*-normal;
		//std::cout << p.x << " " << p.y << " " << p.z << std::endl;
		points.push_back(p);
	}
	//calculate interectiona and contribution
	Ray shadowRay;
	int idS = -1.f, idT = -1.f;
	glm::vec3 interS = glm::vec3(0.f, 0.f, 0.f), interT = glm::vec3(0.f, 0.f, 0.f);
	shadowRay.setRayOrigin(intersection);
	float inter2light;
	float inter2tri;
	float inter2sph;
	for (auto & point : points)
	{
		shadowRay.setRayDirection(glm::normalize(point - intersection));
		T.molllerTrombore(T.getTriangles(), shadowRay, interT, glm::vec3(0.f, 0.f, 0.f), idT);
		T.sphereIntersect(T.getSpheres(), shadowRay, interS, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), idS);
		inter2light = glm::length(point - intersection);
		inter2tri = glm::length(interT - intersection);
		inter2sph = glm::length(interS - intersection);
		if (inter2tri > inter2light && inter2sph > inter2light) {
			contribution += 1.f/ points.size();
		}
		else if (inter2tri <= inter2light) {
			returnState = true;
		}
		else if (inter2sph <= inter2light) {
			returnState = true;
		}
	}
	//std::cout << contribution << std::endl;
	
}
//according to cramers rule (I think)
inline void Barycentric(Triangle::tri t, glm::vec3 & point)
{
	float r1 = getRandomFloat(1.f);
	float r2 = getRandomFloat(1.f);
	float ax = t.vert[0].x, bx = t.vert[1].x, cx = t.vert[2].x;
	float ay = t.vert[0].y, by = t.vert[1].y, cy = t.vert[2].y;
	float az = t.vert[0].z, bz = t.vert[1].z, cz = t.vert[2].z;

	point.x = (1 - sqrt(r1)) * ax + (sqrt(r1) * (1 - r2)) * bx + (sqrt(r1) * r2) * cx;
	point.y = (1 - sqrt(r1)) * ay + (sqrt(r1) * (1 - r2)) * by + (sqrt(r1) * r2) * cy;
	point.z = (1 - sqrt(r1)) * az + (sqrt(r1) * (1 - r2)) * bz + (sqrt(r1) * r2) * cz;
}


Camera::~Camera()
{
	std::cout << "camera ended : ";
}
inline float getRandomFloat(float deltadist)
{
	std::random_device generator;
	std::uniform_real_distribution<float> distance(0, deltadist);
	return distance(generator);
}