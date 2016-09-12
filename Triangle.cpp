#include "Triangle.h"
#include <vector>
#include <iostream>


#define EPSILON 0.000001


Triangle::Triangle()
{
}


//mollertrombore intersection algorithm
// calcualte ray intersection for rays 
int Triangle::molllerTrombore(std::vector<tri>  triangles, glm::vec3 O, glm::vec3 D) {
	

	//real declarations
	glm::vec3 e1, e2;
	glm::vec3 P, Q, T;
	float det, inv_det, U, V;
	float t;
	float t2;
	int index = 0;

	//caluclate trianglehit for all triangles in the vector 
	for (auto & triangle : triangles) {
		//find vectors for 2 edges sharing V1
		e1 = triangle.vert[1] - triangle.vert[0];
		e2 = triangle.vert[2] - triangle.vert[0];
		P = glm::cross(D, e2);
		
		T = O - triangle.vert[0];

		Q = glm::cross(T, e1);

		t = glm::dot(Q,e2)/ glm::dot(P, e1);
		

		if ((t) > 1) { //ray intersection
			//std::cout << "1st hit";
			return 1;
		}
		//std::cout << "t : " << t << '\n';		
	}
	return 0;
}

//vertex data for the room
void Triangle::setRoom(std::vector<glm::vec3>  & room) {



	float vertex_array_data[] = {

		0.0f,  6.0f, -5.0f,    // Floor
	   	0.0f,  -6.0f, -5.0f,    //
		10.0f, -6.0f, -5.0f,  // 

		0.0f,  6.0f, -5.0f,   // Floor
		10.0f, -6.0f, -5.0f,    // 
		10.0f,  6.0f, -5.0f,    // 

		-3.0f,  0.0f, -5.0f,   // Floor left
		0.0f,  -6.0f, -5.0f,     // 
		0.0f,  6.0f, -5.0f,    //

		10.0f,  -6.0f, -5.0f,    // Floor right
		13.0f,  0.0f, -5.0f,    // 
		10.f,  6.0f, -5.0f, // 

		0.0f,  6.0f, -5.0f,     // Wall back
		10.0f,  6.0f, -5.0f,   // 
		0.0f,  6.0f, 5.0f,   // 

		10.0f,  6.0f, -5.0f,   // Wall back
		10.0f,  6.0f, 5.0f,    // 
		0.0f,  6.0f, 5.0f,   // 

		10.0f,  6.0f, -5.0f,    // right back
		13.0f,  0.0f, -5.0f,    //
		13.0f,  0.0f, 5.0f,  // 

		13.0f,  0.0f, 5.0f,   // right back
		10.f,  6.0f, 5.0f,     // 
		10.0f,  6.0f, -5.0f,     // 

		13.0f,  0.0f, -5.0f,  // right front
		10.0f,  -6.0f, 5.0f,    // 
		13.0f,  0.0f, 5.0f,     // 

		13.0f,  0.0f, -5.0f,   // right front
		10.0f, -6.0f, -5.0f,    // 
		10.0f,  -6.0f, 5.0f,    // 

		0.0f,  6.0f, -5.0f,   // left back
		0.0f,  6.0f, 5.0f,  // 
		-3.0f,  0.0f, 5.0f,     // 

		-0.0f,  6.0f, -5.0f,    // left back
		-3.0f,  0.0f, 5.0f,    // 
		-3.0f,  0.0f, -5.0f,    // 

		-3.0f,  0.0f, -5.0f,    // left front
		-3.0f,  0.0f, 5.0f,   // 
		0.0f,  -6.0f, 5.0f,    //

		-3.0f,  0.0f, -5.0f,  // left front
		-0.0f,  -6.0f, 5.0f,   // 
		0.0f,  -6.0f, -5.0f,     // 

		0.0f,  -6.0f, -5.0f,  // Wall front
		10.0f,  -6.0f, -5.0f,    // 
		0.0f,  -6.0f, 5.0f,    // 

		10.0f,  -6.0f, -5.0f,   // Wall front
		10.0f,  -6.0f, 5.0f,    // 
		0.0f,  -6.0f, 5.0f,     // 

		0.0f,  6.0f, 5.0f,   // Roof
		0.0f,  -6.0f, 5.0f,   //
		10.0f, -6.0f, 5.0f,   // 

		0.0f,  6.0f, 5.0f,  // Roof
		10.0f, -6.0f, 5.0f,    // 
		10.0f,  6.0f, 5.0f,    // 

		-3.0f,  0.0f, 5.0f,     // Roof left
		0.0f,  -6.0f, 5.0f,    // 
		0.0f,  6.0f, 5.0f,     //

		10.0f,  -6.0f, 5.0f,    // Roof right
		13.0f,  0.0f, 5.0f,   // 
		10.f,  6.0f, 5.0f,    // 	
	};
	glm::vec3 V;
	//std::cout << (sizeof(vertex_array_data) / sizeof *vertex_array_data) - 2 << "nr verts" << '\n';
	for (int i = 0; i < (sizeof(vertex_array_data) / sizeof *vertex_array_data)-2; i=i+3) {
	
		V.x = vertex_array_data[i];
		V.y = vertex_array_data[i + 1];
		V.z = vertex_array_data[i + 2];
		room.push_back(V);
		
	}

}

void Triangle::setTriangles(std::vector<glm::vec3>  & room, std::vector<Triangle::tri> & triangles) {
	tri t;
	for (int i = 0; i < room.size()-1; i=i+3) {
		t.vert[0] = room[i];
		t.vert[1] = room[i+1];
		t.vert[2] = room[i+2];

		t.normal[0] = (t.vert[0].x*t.vert[1].z) - (t.vert[0].z*t.vert[1].y);
		t.normal[1] = (t.vert[0].z*t.vert[0].x) - (t.vert[0].x*t.vert[1].z);
		t.normal[2] = (t.vert[0].x*t.vert[1].y) - (t.vert[0].y*t.vert[1].x);
		triangles.push_back(t);
	}


}

Triangle::~Triangle()
{
}
