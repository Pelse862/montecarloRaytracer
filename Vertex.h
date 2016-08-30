#pragma once
#include <vector>


class Vertex
{
public:
	
	Vertex();
	~Vertex();
	
private:
	//Create a vector containing positions 
	struct coord {
		float x, y, z, w;
	};
	std::vector<coord> mVertices;
	
};

