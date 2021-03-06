#pragma once
#pragma warning( disable  : 4996 )
#include "Camera.h"

#include <math.h>

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
int Camera::Render(int camera) {

	//classobjects needed
	Direction D;
	Light L;
	Ray r;
	Triangle T;
	L.setAreaLightPoints(T);

	//ray variables
	glm::vec3 originPoint;
	glm::vec3 rayDirection;
	glm::vec3 pixelColor = glm::vec3(0.f, 0.f, 0.f);

	float py;
	float pz;
	float fovZ = M_PI / 4;
	float fovY = fovZ* float(imageSizeZ) / float(imageSizeY);
	float tanZ = tan(fovZ / 2);
	float tanY = tan(fovY / 2);
	float largest = 0;

	for (float i = 0; i < imageSizeZ; ++i) {
		for (float n = 0; n < imageSizeY; ++n) {
			//calculate perspective y and z.            
			py = tanZ * (2 * n - imageSizeY) / float(imageSizeY);
			pz = tanY * (imageSizeZ - 2 * i) / float(imageSizeZ);
			//new origin for each pixelvalue from -1 to +1
			for (int k = 0; k < samplePerRay; k++) {
				originPoint = glm::vec3(0.0f,
					-1.0f + (deltaDistY / 2) + getRandomFloat(deltaDistY) - deltaDistY / 2.f + deltaDistY*n,
					-1.0f + (deltaDistZ / 2) + getRandomFloat(deltaDistZ) - deltaDistZ / 2.f + deltaDistZ*i
				);
				//raydirection combined with the perspective vec
				rayDirection = D.calculateRayDirection(originPoint, camera) + glm::vec3(0.0f, py, pz);
				r.setRayDirection(rayDirection);
				r.setRayOrigin(originPoint);
				r.setImportance(1.0f);
				pixelColor += returnPixel(r, T, bounceDepth, L);
			}
			image[i][n] = pixelColor;
			for (int k = 0; k < 2; ++k) {
				if (largest < image[i][n][k])largest = image[i][n][k];
			}
			pixelColor = glm::vec3(0.f, 0.f, 0.f);
		}
	}


	for (float i = 0; i < imageSizeZ; ++i) {
		for (float n = 0; n < imageSizeY; ++n) {
			image[i][n] = 255.f*sqrt(image[i][n] / largest);
			py = tanZ * (2 * n - imageSizeY) / float(imageSizeY);
			pz = tanY * (imageSizeZ - 2 * i) / float(imageSizeZ);
			pixelColor = glm::vec3(0.f, 0.f, 0.f);
			originPoint = glm::vec3(0.0f,
				-1.0f + (deltaDistY / 2) + deltaDistY*n,
				-1.0f + (deltaDistZ / 2) + deltaDistZ*i
			);
			//raydirection combined with the perspective vec
			rayDirection = D.calculateRayDirection(originPoint, camera) + glm::vec3(0.0f, py, pz);
			r.setRayDirection(rayDirection);
			r.setRayOrigin(originPoint);
			int id = -1;
			T.molllerTrombore(T.getTriangles(), r, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), id);
			if (T.getTriangles().at(id).mat.isLightSource)image[i][n] = L.getAreaLightIntensity();
		}
	}

	//create image 
	createImage();

	//end rendering this image
	return 0;
}

glm::vec3 Camera::returnPixel(Ray r, Triangle T, int nrbounces, Light L) {
	//std::cout << "bounce : " << nrbounces << '\n';
	float randomNr = getRandomFloat(1.f);

	if (nrbounces == 0 || randomNr>r.getImportance())return glm::vec3(0.f, 0.f, 0.f);
	
	Direction D;
	Triangle::material material;
	int idT = -1, idS = -1;
	float lightFromAreaLight = 0.f;
	r.setHitS(false);
	r.setHitT(false);
	bool shadow = false;;
	bool areaLightShadow = false;
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
		normalT = glm::normalize( T.getTriangles().at(idT).normal ) ;
		directionnormalizedOut = -glm::normalize(r.getDirection());
		if (glm::dot(normalT, directionnormalizedOut) <= 0)normalT = -normalT;
		intersectionpointT = intersectionpointT + 0.01f*normalT;
		intersection = intersectionpointT;
		castShadowRay(shadow, areaLightShadow, lightFromAreaLight, intersectionpointT, T, L);
		material = T.getTriangleMaterial(idT);	
		normal = normalT;
	
	}
	else if (idS != -1)
	{	
		sphereHit = true;
		intersection = intersectionpointS;
		castShadowRay(shadow, areaLightShadow,  lightFromAreaLight, intersectionpointS, T, L );
		material = T.getSphereMaterial(idS);
		normal = normalS;
	}
	else
	{
		//end ray, (failsafe)
		return glm::vec3(0.f, 0.f, 0.f);
	}
	//pointlight
	//if(!shadow)result = L.getLocalLightPoint(r, intersection, T, idS, idT, normal, sphereHit);
	//AreaLight
	result += L.getLocalLightArea(lightFromAreaLight, r, intersection, T, idS, idT, normal, sphereHit);
	//calculate new ray from intersectionpoint
	r.setRayDirection( D.calculateBounce(r, normal, material) );
	r.setRayOrigin(intersection);
	//check if ray hits a lightSource
	if (material.isLightSource) {
		return L.getAreaLightIntensity();
	}
	//check if material is a mirror
	else if (material.isSpecular) {
		//get reflective pixelvalue
		r.setImportance(1.0f);
		glm::vec3 pixelColor = r.getImportance()*returnPixel(r, T, 1, L );
		return pixelColor;
	}
	//if surface is diffuse
	else {
		r.setImportance(0.8f*r.getImportance());
		glm::vec3 pixelColor = result + r.getImportance()*returnPixel(r, T, nrbounces - 1, L);
		return pixelColor;
	}
}

bool Camera::castShadowRay(bool & shadow, bool &areaLightShadow,float & lightFromAreaLight, glm::vec3 intersection, Triangle T, Light L)
{
	//returnsate for pointlight
	bool returnStatepointLight = false;
	//pointLight(shadow, L,  T, intersection);
	areaLightpoints(T, lightFromAreaLight, intersection ,areaLightShadow, L);
	return returnStatepointLight;
}

//calculate if shadow and percentage of light applied
inline void areaLightpoints(Triangle T, float & contribution, glm::vec3 intersection, bool & areaLightShadow, Light L)
{
	//calculate intersection and contribution
	Ray shadowRay;
	int idS = -1.f, idT = -1.f;
	glm::vec3 interS = glm::vec3(0.f, 0.f, 0.f), interT = glm::vec3(0.f, 0.f, 0.f);
	shadowRay.setRayOrigin(intersection);
	float inter2light;
	float inter2tri;
	float inter2sph;
	std::vector<glm::vec3> vec = L.getAreaLightPoints();
	for (auto & point : vec)
	{
		shadowRay.setRayDirection(glm::normalize(point - intersection));
		T.molllerTrombore(T.getTriangles(), shadowRay, interT, glm::vec3(0.f, 0.f, 0.f), idT);
		T.sphereIntersect(T.getSpheres(), shadowRay, interS, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), idS);
		inter2light = glm::length(point - intersection);
		inter2tri = glm::length(interT - intersection);
		inter2sph = glm::length(interS - intersection);
		if (inter2tri > inter2light && inter2sph > inter2light) {
			contribution += 1.f / vec.size();
		}
		else if (inter2tri <= inter2light) {
			areaLightShadow = true;
		}
		else if (inter2sph <= inter2light) {
			areaLightShadow = true;
		}
	}
}

//check if point is in shadow for the pointlight
inline void pointLight(bool &returnState, Light L, Triangle T,glm::vec3 intersection)
{
	int idS = -1.f, idT = -1.f;
	Ray shadowRay;
	glm::vec3 interS = glm::vec3(0.f, 0.f, 0.f), interT = glm::vec3(0.f, 0.f, 0.f);
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

