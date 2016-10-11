#include "Ray.h"


Ray::Ray(){
}

Ray::Ray(glm::vec3 dir, glm::vec3 O){
	importance = 1.f;
	hitT = false;
	hitS = false;
	direction = dir;
	origin = O;


}


Ray::~Ray()
{
}
