#include "light.h"
#include "triangle.h"

Light::Light()
{

	position = glm::vec3(1.f, 0.f, 0.f);
	lightIntenisity = glm::vec3(150.f,128.f,128.f);
	areaLightIntensity = glm::vec3(150.f, 128.f, 128.f);

}

glm::vec3 Light::getLocalLight(Ray r,glm::vec3 intersection,Triangle T, int idS,int idT,glm::vec3 normal,bool sphereHit)
{
	glm::vec3 pl = glm::normalize(position - intersection);
	glm::vec3 result = glm::vec3(0.f,0.f,0.f);
	glm::vec3 N = glm::normalize(normal);
	glm::vec3 V = glm::normalize(r.getDirection());
	glm::vec3 R = 2.f * glm::dot(pl,N)*N-pl;
	//ColorDbl light_color = pl.get_color();
	
	float dotProduct = glm::dot(pl, N);
	if (glm::dot(pl, N) < 0) {
		dotProduct = 0.f;
	}

	if (!sphereHit && idT != -1) {
		result += glm::dot(pl, N)*lightIntenisity*T.getTriangles().at(idT).color;
	}
	else if (sphereHit && idS != -1) {
		
		result += glm::dot(pl, N)*lightIntenisity*T.getSpheres().at(idS).color;
		//+  glm::pow( glm::dot(R,V) ,14.f)*lightIntenisity*T.getSpheres().at(idS).color;
	}



	return result;

}


Light::~Light() {

}