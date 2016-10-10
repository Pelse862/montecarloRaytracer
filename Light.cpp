#include "light.h"
#include "triangle.h"

Light::Light()
{

	position = glm::vec3(2.f, 0.f, 4.f);

	lightIntenisity = glm::vec3(255.f,255.f,255.f);
}



Light::~Light() {

}