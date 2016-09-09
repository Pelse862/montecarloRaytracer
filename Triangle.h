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
		};
		

		Triangle();
		//send all triangles to the function.
		int molllerTrombore(std::vector<tri> traingles, glm::vec3 O, glm::vec3 D);

		void setRoom(std::vector<glm::vec3>  & room);
		
		
		void setTriangles(std::vector<glm::vec3>  & room, std::vector<Triangle::tri> & tri); 

		~Triangle();


	private:
	
		std::vector<glm::vec3> roomVertices;
		std::vector<tri> triangles;

		ColorDbl color;

};


