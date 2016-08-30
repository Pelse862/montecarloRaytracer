#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
class Triangle
{
	public:
		Triangle();
		~Triangle();
	private:
		Vertex v1, v2, v3;
		ColorDbl color;

};

