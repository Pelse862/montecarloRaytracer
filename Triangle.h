#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include <vector>
class Triangle
{
	public:
		struct Vector3 {
			float x, y, z;
			float nx, ny, nz;
		};
		Triangle();

		std::vector<Vector3> Triangle::getVertex();

		~Triangle();


	private:
	
		std::vector<Vector3> vertex;
		ColorDbl color;

};


