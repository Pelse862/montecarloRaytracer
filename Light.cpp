#include "light.h"
#include "triangle.h"

Light::Light()
{

	position = glm::vec3(7.f, 2.f, -2.f);
	lightIntenisity = glm::vec3(255.f,255.f,255.f);
	areaLightIntensity = glm::vec3(255.f, 255.f, 255.f);
}

glm::vec3 Light::getLocalLightPoint(Ray r,glm::vec3 intersection,Triangle T, int idS,int idT,glm::vec3 normal,bool sphereHit)
{
	glm::vec3 pl = glm::normalize(position - intersection);
	glm::vec3 result = glm::vec3(0.f,0.f,0.f);
	glm::vec3 N = glm::normalize(normal);
	
	float dotProduct = glm::dot(pl, N);
	if (glm::dot(pl, N) < 0) {
		dotProduct = 0.f;
	}
	if (!sphereHit && idT != -1) {
		result += dotProduct*lightIntenisity*T.getTriangles().at(idT).color;
	}
	else if (sphereHit && idS != -1) {
		
		result += dotProduct*lightIntenisity*T.getSpheres().at(idS).color;
	}
	return result;
}


glm::vec3 Light::getLocalLightArea(float contributuin, Ray r, glm::vec3 intersection, Triangle T, int idS, int idT, glm::vec3 normal, bool sphereHit)
{
	glm::vec3 meanPos = glm::vec3(0.f,0.f,0.f);
	for (auto &p : AreaLightPoints) {
		meanPos += p;
	}
	meanPos = meanPos / float(AreaLightPoints.size());
	glm::vec3 pl = glm::normalize(meanPos - intersection);
	glm::vec3 result = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 N = glm::normalize(normal);
	glm::vec3 meanPos2inter = glm::normalize(intersection - meanPos);
	float intersectionAngle = glm::dot(N,-meanPos2inter);
	intersectionAngle = intersectionAngle < 0 ? 0 : intersectionAngle;
	float areaLightAngle = glm::dot( glm::vec3(0.0f,0.0f,1.0f), meanPos2inter);
	areaLightAngle = areaLightAngle < 0 ? 0 : areaLightAngle;
	float d_2 = glm::dot(intersection - meanPos, intersection - meanPos);
	float anglecont = ((intersectionAngle * areaLightAngle) / d_2)*1.f/ float(AreaLightPoints.size());
	float dotProduct = glm::dot(pl, N);
	if (!sphereHit && idT != -1) {
		result += glm::dot(pl, N)*lightIntenisity*T.getTriangles().at(idT).color*contributuin+ areaLightIntensity*anglecont;
	}
	else if (sphereHit && idS != -1) {
		result += glm::dot(pl, N)*lightIntenisity*T.getSpheres().at(idS).color*contributuin*areaLightIntensity*anglecont;
	}
	return result;
}

//save random points on the area lightsource
void Light::setAreaLightPoints(Triangle T) {
	glm::vec3 p;
	Triangle::tri t1 = T.getTriangles().at(T.getTriangles().size() - 1);
	Triangle::tri t2 = T.getTriangles().at(T.getTriangles().size() - 2);
	glm::vec3 normal = glm::normalize(t1.normal);
	for (int i = 0; i < 6; i++) {
		Barycentric(t1, p);
		p += 0.001f*normal;
		AreaLightPoints.push_back(p);
	}
	normal = glm::normalize(t2.normal);
	for (int i = 0; i < 6; i++) {
		Barycentric(t2, p);
		p += 0.001f*-normal;
		AreaLightPoints.push_back(p);
	}
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

inline float getRandomFloat(float deltadist)
{
	std::random_device generator;
	std::uniform_real_distribution<float> distance(0, deltadist);
	return distance(generator);
}



Light::~Light() {

}