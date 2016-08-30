#pragma once
#include <vector>
class Direction
{
	public:
		Direction();
		~Direction();
	private: 
	//Create a vector that describes the ray direction
	struct Vector3 {
		float x, y, z;
	};
	std::vector<Vector3> direction;
};

