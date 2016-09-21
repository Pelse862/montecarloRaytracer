#include "glm.hpp"
#include <stdlib.h>
#include <iostream>
#include "Triangle.h"


#define LIGHT_SHAPE 3

class Light {

	public:

		double radiance;
		glm::dvec3 position;
		double size;
		Triangle *lightObject;

		//constructor
		Light();
		//~Light();

		void setLight( std::vector<Triangle::tri> & triangles);

		//methods
		glm::dvec3 randomPosition(std::vector<Triangle::tri> & triangles);

		glm::dvec3 calculateIntersections();
		void computeChildrenRays();
		int getType();
		glm::dvec3 getColor(int);
		int getWallIntersectionIndex();
		double getRefractiveIndex();
		glm::dvec3 getIntersectionNormal();
		bool getTransparency();

		


};