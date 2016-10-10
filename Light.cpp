#include "light.h"
#include "triangle.h"

Light::Light()
{

	position = glm::vec3(1.f, 1.f, 1.f);

	lightIntenisity = glm::vec3(128.f,128.f,128.f);

}



Light::~Light() {

}