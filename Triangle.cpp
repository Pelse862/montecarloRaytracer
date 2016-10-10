#include "Triangle.h"
#include "Scene.h"
#include "Light.h"
#include "Vertex.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>   
#include "triangle_custom_shape.h"

#define EPSILON 0.00000000000000001

#define COLOR_WHITE   glm::vec3(255,255,255)
#define COLOR_BLACK   glm::vec3(  0,  0,  0)
#define COLOR_RED     glm::vec3(255,  0,  0)
#define COLOR_GREEN   glm::vec3(  0,255,  0)
#define COLOR_BLUE    glm::vec3(  0,  0,255)
#define COLOR_CYAN    glm::vec3(  0,255,255)
#define COLOR_MAGENTA glm::vec3(255,  0,255)
#define COLOR_YELLOW  glm::vec3(255,255,  0)
#define COLOR_PINK    glm::vec3(235, 16,255)


Triangle::Triangle()
{
	
	setRoom(roomVertices);
	setBox(roomVertices);
	
	//setTriangles(roomVertices, triangles);
	setSpheres(spheres);
	
}
//calculates if the ray is on the surface of the sphere
//using the formula ||x-c|^2| = r^2 
void Triangle::sphereIntersect(std::vector<sphere> & spheres, Ray & r, glm::vec3 & intersectionPoint ,glm::vec3 & pixelcolor,int & id){

	glm::vec3 d = glm::normalize(r.getDirection());
	glm::vec3 o = r.getRayorigin();
	glm::vec3 c,normal;
	float a, b, ac,sqrt;
	pixelcolor = glm::vec3(100, 100, 100);
	int count = -1;
	float radius;
	intersectionPoint = glm::vec3(10000.f, 10000.f, 10000.f);
	//intersection for multiple spheres?
	for (auto & sphere : spheres)
	{
		count++;
		c = sphere.center;
		radius = sphere.radius;

		b = glm::dot( (2.f * d), (o - c));
		ac = glm::dot(o - c, o - c) - radius;
		float d1 = -b / 2.f;
		float d2 = d1;

		float bsqrt = d1*d1 - ac;
		if (bsqrt < 0.f)continue;

		sqrt = glm::sqrt(bsqrt);
		d1 += sqrt;
		d2 -= sqrt;

		if(d1 < d2) 
		{
			intersectionPoint = o+d1*d;
		}
		else if(d2 < d1) 
		{
			intersectionPoint = o + d2*d;
		}
		else 
		{
			intersectionPoint = o + d1*d;
		}

		normal = intersectionPoint - c;
		intersectionPoint += 0.001f*glm::normalize(normal);
	}
	
	

	
}
//mollertrombore intersection algorithm
// calcualte ray intersection for rays 
void Triangle::molllerTrombore(std::vector<Triangle> triangles, Ray & r, glm::vec3 & intersectionPoint, glm::vec3 & pixelcolor, int & id) {
	
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
	int count = -1;
	glm::vec3 D = glm::normalize(r.getDirection() );
	//caluclate trianglehit for all triangles in the vector 
	for (auto & triangle : triangles) {
		count++;
		//find vectors for 2 edges sharing V1
		e1 = triangle.v1_.vertex - triangle.v0_.vertex;
		e2 = triangle.v2_.vertex - triangle.v0_.vertex;

		P = glm::cross(D, e2);
		det = glm::dot(e1, P);


		if (det > -EPSILON && det < EPSILON) continue;

		inv_det = 1.f / det;

		T = r.getRayorigin() - triangle.v0_.vertex;

		u = glm::dot(T, P) * inv_det;

		if (u < 0.f || u > 1.f) continue;

		Q = glm::cross(T, e1);

		//Calculate V parameter and test bound
		v = glm::dot(D, Q) * inv_det;
		//The intersection lies outside of the triangle
		if (v < 0.f || u + v  > 1.f) continue;

		t = glm::dot(e2, Q) * inv_det;

		if ( (t) > EPSILON && t < t1) { //ray intersection
			t1 = t;
			id = count;
			r.setHitT(true);
			pos.x = (1 - u - v)*triangle.v0_.vertex.x + u*triangle.v1_.vertex.x + v*triangle.v2_.vertex.x;
			pos.y = (1 - u - v)*triangle.v0_.vertex.y + u*triangle.v1_.vertex.y + v*triangle.v2_.vertex.y;
			pos.z = (1 - u - v)*triangle.v0_.vertex.z + u*triangle.v1_.vertex.z + v*triangle.v2_.vertex.z;
			intersectionPoint = pos;
			pixelcolor = triangle.color;	
		}
	}

}



//vertex data for the room
void Triangle::setRoom(std::vector<Triangle>  room2) {

	// Floor vertices
	Vertex vfC = Vertex(5, 0, -5); // center vertex on floor
	Vertex vf1 = Vertex(-3, 0, -5);
	Vertex vf2 = Vertex(0, -6, -5);
	Vertex vf3 = Vertex(10, -6, -5);
	Vertex vf4 = Vertex(13, 0, -5);
	Vertex vf5 = Vertex(10, 6, -5);
	Vertex vf6 = Vertex(0, 6, -5);

	// Ceiling vertices
	Vertex vcC = Vertex(5, 0, 5); // center vertex on ceiling
	Vertex vc1 = Vertex(-3, 0, 5);
	Vertex vc2 = Vertex(0, -6, 5);
	Vertex vc3 = Vertex(10, -6, 5);
	Vertex vc4 = Vertex(13, 0, 5);
	Vertex vc5 = Vertex(10, 6, 5);
	Vertex vc6 = Vertex(0, 6, 5);
	


	// Floor
	roomVertices.push_back(Triangle(vfC, vf6, vf1, COLOR_WHITE));
	roomVertices.push_back(Triangle(vfC, vf1, vf2, COLOR_WHITE));
	roomVertices.push_back(Triangle(vfC, vf2, vf3, COLOR_WHITE));
	roomVertices.push_back(Triangle(vfC, vf3, vf4, COLOR_WHITE));
	roomVertices.push_back(Triangle(vfC, vf4, vf5, COLOR_WHITE));
	roomVertices.push_back(Triangle(vfC, vf5, vf6, COLOR_WHITE));

	// Ceiling
	roomVertices.push_back(Triangle(vcC, vc1, vc6, COLOR_WHITE));
	roomVertices.push_back(Triangle(vcC, vc2, vc1, COLOR_WHITE));
	roomVertices.push_back(Triangle(vcC, vc3, vc2, COLOR_WHITE));
	roomVertices.push_back(Triangle(vcC, vc4, vc3, COLOR_WHITE));
	roomVertices.push_back(Triangle(vcC, vc5, vc4, COLOR_WHITE));
	roomVertices.push_back(Triangle(vcC, vc6, vc5, COLOR_WHITE));

	/* Counter-clockwise order, starting with front */

	// Wall1
	roomVertices.push_back(Triangle(vf2, vc2, vf3, COLOR_RED));
	roomVertices.push_back(Triangle(vf3, vc2, vc3, COLOR_RED));

	// Wall 2
	roomVertices.push_back(Triangle(vf3, vc3, vf4, COLOR_BLUE));
	roomVertices.push_back(Triangle(vf4, vc3, vc4, COLOR_BLUE));

	// Wall 3
	roomVertices.push_back(Triangle(vf4, vc4, vf5, COLOR_YELLOW));
	roomVertices.push_back(Triangle(vf5, vc4, vc5, COLOR_YELLOW));

	// Wall 4
	roomVertices.push_back(Triangle(vf5, vc5, vf6, COLOR_GREEN));
	roomVertices.push_back(Triangle(vf6, vc5, vc6, COLOR_GREEN));

	// Wall 5
	roomVertices.push_back(Triangle(vf6, vc6, vf1, COLOR_MAGENTA));
	roomVertices.push_back(Triangle(vf1, vc6, vc1, COLOR_MAGENTA));

	// Wall 6
	roomVertices.push_back(Triangle(vf1, vc1, vf2, COLOR_CYAN));
	roomVertices.push_back(Triangle(vf2, vc1, vc2, COLOR_CYAN));

//	std::cout << room2.at(0).v0_.vertex.x << std::endl;

	float vertex_array_data[] = {


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

	//	room.push_back(V);
		
	}
//	std::cout << "Room: " << room.size() << std::endl;
}

void Triangle::setBox(std::vector<Triangle>  room) {

	// Floor vertices
	Vertex v1 = Vertex(5, 0, 3);
	Vertex v2 = Vertex(5, 0, 1);
	Vertex v3 = Vertex(5, 2, 1);
	Vertex v4 = Vertex(5, 2, 3);
	Vertex v5 = Vertex(7, 0, 3);
	Vertex v6 = Vertex(7, 2, 3);
	Vertex v7 = Vertex(7, 2, 1);
	Vertex v8 = Vertex(7, 0, 1);

	roomVertices.push_back(Triangle(v1, v2, v4, COLOR_YELLOW));//front
	roomVertices.push_back(Triangle(v2, v3, v4, COLOR_YELLOW));

	roomVertices.push_back(Triangle(v4, v7, v6, COLOR_YELLOW));// top
	roomVertices.push_back(Triangle(v4, v3, v7, COLOR_YELLOW));

	roomVertices.push_back(Triangle(v5, v6, v8, COLOR_YELLOW));//back
	roomVertices.push_back(Triangle(v8, v6, v7, COLOR_YELLOW));

	roomVertices.push_back(Triangle(v2, v8, v3, COLOR_YELLOW));//right
	roomVertices.push_back(Triangle(v8, v7, v3, COLOR_YELLOW));

	roomVertices.push_back(Triangle(v6, v5, v4, COLOR_YELLOW));//left
	roomVertices.push_back(Triangle(v5, v1, v4, COLOR_YELLOW));
	
	//scene_objects_.push_back(std::make_unique<TriangleCustomShape>(roomVertices));


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

	};

	glm::vec3 V;
	//std::cout << (sizeof(vertex_array_data) / sizeof *vertex_array_data) - 2 << "nr verts" << '\n';

	for (int i = 0; i < (sizeof(vertex_array_data) / sizeof *vertex_array_data) - 2; i = i + 3) {

		V.x = vertex_array_data[i];
		V.y = vertex_array_data[i + 1]+1;
		V.z = vertex_array_data[i + 2];

	//	room.push_back(V);

	}
	std::cout << "Room: " << room.size() << std::endl;

}


void Triangle::setTriangles(std::vector<glm::vec3>  & room, std::vector<Triangle::tri> & triangles) {
	tri t;
	glm::vec3 u, v;

	for (int i = 0; i < room.size()-2; i=i+3) {
		t.vert[0] = room[i];
		t.vert[1] = room[i+1];
		t.vert[2] = room[i+2];

		u = t.vert[2] - t.vert[0];
		v = t.vert[1] - t.vert[0];
		t.normal = glm::normalize(glm::cross(u, v));
		//std::cout << i;
	
		triangles.push_back(t);
	}



	std::cout << "triangles: " << triangles.size() << std::endl;
	
	//floor room
	triangles.at(0).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(1).color = glm::vec3(255.f, 255.f, 255.f);

	//Floor left
	triangles.at(2).color = glm::vec3(255.f, 255.f, 255.f);

	//Floor right
	triangles.at(3).color = glm::vec3(255.f, 255.f, 255.f);

	//Wall back Cyan
	triangles.at(4).color = glm::vec3(0.f, 255.f, 255.f);
	triangles.at(5).color = glm::vec3(0.f, 255.f, 255.f);

	//Right back Red
	triangles.at(6).color = glm::vec3(255.f,0.f,0.f);
	triangles.at(7).color = glm::vec3(255.f,0.f,0.f);

	//Right front Blue
	triangles.at(8).color = glm::vec3(0.f, 0.f, 255.f);
	triangles.at(9).color = glm::vec3(0.f, 0.f, 255.f);

	//Left back Green
	triangles.at(10).color = glm::vec3(0.f, 255.f, 0.f);
	triangles.at(11).color = glm::vec3(0.f, 255.f, 0.f);

	//Left front Yellow
	triangles.at(12).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(13).color = glm::vec3(255.f, 255.f, 0.f);

	//Wall front  Magenta
	triangles.at(14).color = glm::vec3(255.f, 0.f, 255.f);
	triangles.at(15).color = glm::vec3(255.f, 0.f, 255.f);

	//Roof
	triangles.at(16).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(17).color = glm::vec3(255.f, 255.f, 255.f);

	//Roof left
	triangles.at(18).color = glm::vec3(255.f, 255.f, 255.f);

	//Roof right
	triangles.at(19).color = glm::vec3(255.f, 255.f, 255.f);

	//###############################
	//golv box
	triangles.at(20).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(21).color = glm::vec3(255.f, 255.f, 0.f);

	//höger
	triangles.at(22).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(23).color = glm::vec3(255.f, 255.f, 0.f);

	//tak
	triangles.at(24).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(25).color = glm::vec3(255.f, 255.f, 0.f);

	//front magenta
	triangles.at(26).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(27).color = glm::vec3(255.f, 255.f, 0.f);

	//vänster
	triangles.at(28).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(29).color = glm::vec3(255.f, 255.f, 0.f);

	//ej synlig
	triangles.at(30).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(31).color = glm::vec3(255.f, 255.f, 0.f);


}	


//adds spheres to the scene
void Triangle::setSpheres(std::vector<Triangle::sphere> & S) {
	//add 1 sphere to the scene
	sphere s;
	s.center = glm::vec3(4.0f, -1.0f, 2.0f);
	s.radius = 1.0f;
	s.color = glm::vec3(100.0f, 100.0f, 100.0f);
	S.push_back(s);
	/*s.center = glm::vec3(6.0f, 2.0f, -3.0f);
	s.radius = 0.5f;
	s.color = glm::vec3(200.0f, 100.0f, 100.0f);
	S.push_back(s);*/

}


std::vector<Triangle> Triangle::getTriangles() {
	return roomVertices;
}
std::vector<Triangle::sphere> Triangle::getSpheres() {
	return spheres;
}


//the void is calling
Triangle::~Triangle()
{
}

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2, glm::vec3 c) : v0_(v0), v1_(v1), v2_(v2), color(c) {

	normal = glm::cross(v1_.vertex - v0_.vertex, v2_.vertex - v1_.vertex);
	color = c;
	
}