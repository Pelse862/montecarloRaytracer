#pragma once
#include <vector>
#include "glm.hpp"


class Vertex
{
public:
	
	Vertex();
	Vertex(int x, int y, int z);
	~Vertex();
	glm::vec3 vertex;
	
private:
	
	//Create a vector containing positions 
	struct coord {
		float x, y, z;
	};
	std::vector<coord> mVertices;
	
};

