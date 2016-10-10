#include "light.h"
#include "triangle.h"

Light::Light()
{
	position = glm::vec3(2.f, 2.f, 2.f);
	lightIntenisity = glm::vec3(128.f,128.f,128.f);
}

glm::vec3 Light::getLocalLight(glm::vec3 intersection,Triangle T, int idS,int idT,glm::vec3 normal,bool sphereHit)
{
	glm::vec3 pl = position - intersection;
	glm::vec3 result;

	//ColorDbl light_color = pl.get_color();
	pl = glm::normalize(pl);
	glm::vec3 N = glm::normalize(normal);
	if (!sphereHit && idT != -1) {
		result += glm::dot(pl, N)*lightIntenisity*T.getTriangles().at(idT).color;
	}
	else if (sphereHit && idS != -1) {
		result += glm::dot(pl, N)*lightIntenisity*T.getSpheres().at(idS).color;
	}
	else
	{	//if nothing is hit failsafe
		result = glm::vec3(0.f, 0.f, 0.f);
	}
	return result;

}

Light::~Light() {

}