#include "Triangle.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>   

#define EPSILON 0.00000000000000001


Triangle::Triangle()
{
}
//calculates if the ray is on the surface of the sphere
//using the formula ||x-c|^2| = r^2 
void Triangle::sphereIntersect(std::vector<sphere> spheres, glm::vec3 dir, glm::vec3 O, glm::vec3 & intersectionPoint ,glm::vec3 & pixelcolor){

	glm::vec3 l = glm::normalize(dir);
	glm::vec3 pos1, pos2, b;
	float d,d1,d2,sqrtA;
	std::vector<glm::vec3> possiblePoint;

	possiblePoint.push_back(glm::vec3(10000.0f, 1000000.0f, 100000.0f));
	//intersection for multiple spheres?
	for (auto & sphere : spheres)
	{
		//;
		b = O - sphere.center;
		if (pow(dot(l, b), 2) - pow(sqrt(pow(b.x, 2) + pow(b.y, 2) + pow(b.z, 2)), 2)
			+ pow(sphere.radius, 2) < 0) continue;

	    sqrtA = sqrt( pow( dot(l,b) ,2 ) - pow ( sqrt( pow(b.x,2)+ pow(b.y, 2) + pow(b.z, 2) ), 2)
				+ pow(sphere.radius,2) );
	
		if (sqrtA == 0) {
			pixelcolor = sphere.color;
			d = -1* dot(l, b);
			possiblePoint.push_back(O + d*l);
		}
		else {
			pixelcolor = sphere.color;
			
			d1 = -1 * dot(l, b) + sqrtA;
			d2 = -1 * dot(l, b) - sqrtA;
			pos1 = O + d1*l;
			pos1 = O + d2*l;
			float dist1 = pow(sqrt(pow(pos1.x, 2) + pow(pos1.y, 2) + pow(pos1.z, 2)),2);
			float dist2 = pow(sqrt(pow(pos1.x, 2) + pow(pos1.y, 2) + pow(pos1.z, 2)),2);
			possiblePoint.push_back( O + (dist1 < dist2 ? d1 : d2)*l);
		}
	}
	if (possiblePoint.size() > 1) {
		for (int i = 0; i < possiblePoint.size() - 1; i++) {
			intersectionPoint = glm::distance(O,possiblePoint[i]) < glm::distance(O,possiblePoint[i + 1]) ?
								possiblePoint[i] : possiblePoint[i + 1];
		}
	}
	else
	{
		intersectionPoint = possiblePoint[0];
	}
}
//mollertrombore intersection algorithm
// calcualte ray intersection for rays 
void Triangle::molllerTrombore(std::vector<tri> triangles, glm::vec3 O, glm::vec3 D, glm::vec3 & intersectionPoint, glm::vec3 & pixelcolor) {
	

	//real declarations
	glm::vec3 e1 = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 e2 = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 P = glm::vec3(0.f, 0.f, 0.f); 
	glm::vec3 Q = glm::vec3(0.f, 0.f, 0.f); 
	glm::vec3 T = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 pos;
	std::vector<glm::vec3> possiblePoint;
	//real declarations
	float t = 0;
	float t1 = 10000000.0f;
	float det = 0;
	float inv_det = 0;
	float u = 0;
	float v = 0;
	D = glm::normalize(D);
	//caluclate trianglehit for all triangles in the vector 
	for (auto & triangle : triangles) {
		//find vectors for 2 edges sharing V1
		e1 = triangle.vert[1] - triangle.vert[0];
		e2 = triangle.vert[2] - triangle.vert[0];

		P = glm::cross(D, e2);
		det = glm::dot(e1, P);


		if (det > -EPSILON && det < EPSILON) continue;

		inv_det = 1.f / det;

		T = O - triangle.vert[0];

		u = glm::dot(T, P) * inv_det;

		if (u < 0.f || u > 1.f) continue;

		Q = glm::cross(T, e1);

		//Calculate V parameter and test bound
		v = glm::dot(D, Q) * inv_det;
		//The intersection lies outside of the triangle
		if (v < 0.f || u + v  > 1.f) continue;

		t = glm::dot(e2, Q) * inv_det;

		if ((t) > EPSILON && t < t1) { //ray intersection
			t1 = t;
			pos.x = (1 - u - v)*triangle.vert[0].x + u*triangle.vert[1].x + v*triangle.vert[2].x;
			pos.y = (1 - u - v)*triangle.vert[0].y + u*triangle.vert[1].y + v*triangle.vert[2].y;
			pos.x = (1 - u - v)*triangle.vert[0].z + u*triangle.vert[1].z + v*triangle.vert[2].z;
			intersectionPoint = pos;
			pixelcolor = triangle.color;
		}
	}

}



//vertex data for the room
void Triangle::setRoom(std::vector<glm::vec3>  & room) {


	float vertex_array_data[] = {

		//box

		5.f, 0.f, 3.f,
		7.f, 0.f, 3.f,
		5.f, 2.f, 3.f,

		7.f, 0.f, 3.f,
		7.f, 2.f, 3.f,
		5.f, 2.f, 3.f,

		5.f, 0.f, 1.f,	//floor
		7.f, 0.f, 1.f,
		5.f, 2.f, 1.f,

		7.f, 0.f, 1.f,
		7.f, 2.f, 1.f,
		5.f, 2.f, 1.f,

		5.f, 2.f, 3.f,	//front
		5.f, 2.f, 1.f,
		5.f, 0.f, 1.f,

		5.f, 2.f, 3.f,
		5.f, 0.f, 1.f,
		5.f, 0.f, 3.f,

		7.f, 2.f, 3.f,	//back
		7.f, 2.f, 1.f,
		7.f, 0.f, 1.f,

		7.f, 2.f, 3.f,
		7.f, 0.f, 1.f,
		7.f, 0.f, 3.f,

		5.f, 2.f ,1.f, //left side
		7.f ,2.f ,1.f,
		5.f ,2.f ,3.f,

		5.f, 2.f , 3.f,
		7.f, 2.f , 3.f,
		7.f ,2.f ,1.f,

		5.f, 0.f ,1.f, //right side
		7.f ,0.f ,1.f,
		5.f ,0.f ,3.f,

		5.f, 0.f , 3.f,
		7.f, 0.f , 3.f,
		7.f ,0.f ,1.f,


		//room
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
	std::cout << "Room: " << room.size() << std::endl;
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
		//std::cout << i;
	
		triangles.push_back(t);
	}

	std::cout << "triangles: " << triangles.size() << std::endl;

	//golv cube
	triangles.at(0).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(1).color = glm::vec3(255.f, 255.f, 0.f);

	//höger
	triangles.at(2).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(3).color = glm::vec3(255.f, 255.f, 0.f);

	//tak
	triangles.at(4).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(5).color = glm::vec3(255.f, 255.f, 0.f);

	//front magenta
	triangles.at(6).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(7).color = glm::vec3(255.f, 255.f, 0.f);

	//vänster
	triangles.at(8).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(9).color = glm::vec3(255.f, 255.f, 0.f);

	//ej synlig
	triangles.at(10).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(11).color = glm::vec3(255.f, 255.f, 0.f);
	
	//floor room #########################
	triangles.at(12).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(13).color = glm::vec3(255.f, 255.f, 255.f);

	//Floor left
	triangles.at(14).color = glm::vec3(255.f, 255.f, 255.f);

	//Floor right
	triangles.at(15).color = glm::vec3(255.f, 255.f, 255.f);

	//Wall back Cyan
	triangles.at(16).color = glm::vec3(0.f, 255.f, 255.f);
	triangles.at(17).color = glm::vec3(0.f, 255.f, 255.f);

	//Right back Red
	triangles.at(18).color = glm::vec3(255.f,0.f,0.f);
	triangles.at(19).color = glm::vec3(255.f,0.f,0.f);

	//Right front Blue
	triangles.at(20).color = glm::vec3(0.f, 0.f, 255.f);
	triangles.at(21).color = glm::vec3(0.f, 0.f, 255.f);

	//Left back Green
	triangles.at(22).color = glm::vec3(0.f, 255.f, 0.f);
	triangles.at(23).color = glm::vec3(0.f, 255.f, 0.f);

	//Left front Yellow
	triangles.at(24).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(25).color = glm::vec3(255.f, 255.f, 0.f);

	//Wall front  Magenta
	triangles.at(26).color = glm::vec3(255.f, 0.f, 255.f);
	triangles.at(27).color = glm::vec3(255.f, 0.f, 255.f);

	//Roof
	triangles.at(28).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(29).color = glm::vec3(255.f, 255.f, 255.f);

	//Roof left
	triangles.at(30).color = glm::vec3(255.f, 255.f, 255.f);

	//Roof right
	triangles.at(31).color = glm::vec3(255.f, 255.f, 255.f);


}	


//adds spheres to the scene
void Triangle::setSpheres(std::vector<Triangle::sphere> & S) {
	//add 1 sphere to the scene
	sphere s;
	s.center = glm::vec3(5.0f, -3.0f, 3.0f);
	s.radius = 1.0f;
	s.color = glm::vec3(100.0f, 100.0f, 100.0f);
	S.push_back(s);
	s.center = glm::vec3(4.0f, 2.0f, -3.0f);
	s.radius = 0.5f;
	s.color = glm::vec3(200.0f, 100.0f, 100.0f);
	S.push_back(s);

}

//the void is calling
Triangle::~Triangle()
{
}
