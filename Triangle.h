#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include <vector>
class Triangle
{
	public:
		struct Vector3 {
			float x, y, z;
		};
		struct tri {
			Vector3 vert[3];
			float normal[3];
		};
		

		Triangle();

		void setRoom(std::vector<Vector3>  & room);
		void setTriangles(std::vector<Vector3>  & room, std::vector<Triangle::tri> & tri);

		~Triangle();


	private:
	
		std::vector<Vector3> roomVertices;
		std::vector<tri> triangles;

		ColorDbl color;

};


