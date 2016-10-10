#include "light.h"
#include "triangle.h"

Light::Light()
{
	position = glm::vec3(2.f, 2.f, 2.f);
	lightIntenisity = glm::vec3(128.f,128.f,128.f);
}



Light::~Light() {

}