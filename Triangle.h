#pragma once


#include "Vertex.h"
#include "ColorDbl.h"

#include "glm.hpp"


#include <vector>
class Triangle
{
	public:
		
		//bindes the normal to 1 triangle
		struct tri {
			glm::vec3 vert[3];
			glm::vec3 normal;
			glm::vec3 color;
		};
		struct sphere {
			glm::vec3 center;
			float radius;
		};



		Triangle();
		//send all triangles to the function.
		int molllerTrombore(std::vector<tri>  triangles, glm::vec3 O, glm::vec3 D, glm::vec3 & pixelcolor);

		void setRoom(std::vector<glm::vec3>  & room);
		
		//check intersect for implicit sphere
		int sphereIntersect(std::vector<sphere> spheres,  glm::vec3 dir);

		void setTriangles(std::vector<glm::vec3>  & room, std::vector<Triangle::tri> & tri); 

		~Triangle();


	private:
	
		std::vector<glm::vec3> roomVertices;
		std::vector<tri> triangles;
		std::vector<sphere> spheres;
		ColorDbl color;

};


