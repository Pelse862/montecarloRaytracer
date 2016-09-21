#pragma once


#include "Vertex.h"
#include "ColorDbl.h"

#include "glm.hpp"


#include <vector>
class Triangle
{
	public:
		
		//triangle structure
		struct tri {
			glm::vec3 vert[3];
			glm::vec3 normal;
			glm::vec3 color;
		};
		//sphere structure
		struct sphere {
			glm::vec3 center;
			glm::vec3 color;
			float radius;
		};

		Triangle();
		//send all triangles to the function.
		void molllerTrombore(std::vector<tri>  triangles, glm::vec3 O, glm::vec3 D, glm::vec3 & intersectionPoint, glm::vec3 & pixelColor);

		void setRoom(std::vector<glm::vec3>  & room);
		
		//check intersect for implicit sphere
		void sphereIntersect(std::vector<sphere> spheres, glm::vec3 dir, glm::vec3 O, glm::vec3 & intersectionPoint, glm::vec3 & pixelColor);

		void setTriangles(std::vector<glm::vec3>  & room, std::vector<Triangle::tri> & tri);

		void setSpheres(std::vector<sphere> & S);

		~Triangle();


	private:
	
		std::vector<glm::vec3> roomVertices;
		std::vector<tri> triangles;
		std::vector<sphere> spheres;
		ColorDbl color;

};


