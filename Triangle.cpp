#include "Triangle.h"
#include "Light.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>   

#define EPSILON 0.00000000000000001
# define M_PI 3.14159265358979323846  /* pi */


Triangle::Triangle()
{
	
	setRoom(roomVertices);
	setBox(roomVertices);
	setAreaLight(roomVertices);

	setTriangles(roomVertices, triangles);
	setSpheres(spheres);
	
}
//calculates if the ray is on the surface of the sphere
void Triangle::sphereIntersect(std::vector<sphere> & spheres, Ray & r, glm::vec3 & intersectionPoint ,glm::vec3 & pixelcolor,
	glm::vec3 & normalS, int & id){

	glm::vec3 d = glm::normalize(r.getDirection());
	glm::vec3 o = r.getRayorigin();
	glm::vec3 c,normal;
	float a, b, ac,sqrt, bsqrt;
	float d1, d2;
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
		ac = glm::dot(o - c, o - c) - glm::pow(radius,2);
		d1 = -b / 2.f;
		d2 = d1;
	
		bsqrt = d1*d1 - ac;
		//if bsqrt is negative it will be complex => no hit
		if (bsqrt < 0.f) continue;
		
		sqrt = glm::sqrt(bsqrt);
		d1 += sqrt;
		d2 -= sqrt;

		//d1 or d2 is negative intersection is in a negative
		//direction seen from the given direction
		if(d1 <= 0 && d2 <= 0)
		{
			continue;
		}
		else if(d2 < d1) 
		{
			intersectionPoint = o + d2*d;
		}
		else if(d1 < d2)
		{
			intersectionPoint = o + d1*d;
		}
		else
		{
			intersectionPoint = o + d2*d;
		}
		r.setHitS(true);
		normalS = glm::normalize( intersectionPoint - c);
		//move point some distance from surface
		intersectionPoint = intersectionPoint + 0.01f*normalS;
		pixelcolor = sphere.color;
		id = count;
	}	
}

//mollertrombore intersection algorithm
// calcualte ray intersection for rays 
void Triangle::molllerTrombore(std::vector<tri> triangles, Ray & r, glm::vec3 & intersectionPoint, glm::vec3 & pixelcolor, int & id) {
	
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
	intersectionPoint = glm::vec3(10000.f, 10000.f, 10000.f);

	//caluclate trianglehit for all triangles in the vector 
	for (auto & triangle : triangles) {
		count++;
		//find vectors for 2 edges sharing V1
		e1 = triangle.vert[1] - triangle.vert[0];
		e2 = triangle.vert[2] - triangle.vert[0];

		P = glm::cross(D, e2);
		det = glm::dot(e1, P);


		if (det > -EPSILON && det < EPSILON) continue;

		inv_det = 1.f / det;

		T = r.getRayorigin() - triangle.vert[0];

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
			pos.x = (1 - u - v)*triangle.vert[0].x + u*triangle.vert[1].x + v*triangle.vert[2].x;
			pos.y = (1 - u - v)*triangle.vert[0].y + u*triangle.vert[1].y + v*triangle.vert[2].y;
			pos.z = (1 - u - v)*triangle.vert[0].z + u*triangle.vert[1].z + v*triangle.vert[2].z;		
			intersectionPoint = pos;
			pixelcolor = triangle.color;	
		}
	}

}
//area light triangles
void Triangle::setAreaLight(std::vector<glm::vec3>  & room) {
	float vertex_array_data[] = {
		6.f, -0.5f,-4.99f,
		5.f, 0.5f,-4.99f,
		6.f, 0.5f,-4.99f,

		5.f, -0.5f,-4.99f,
		6.f, -0.5f,-4.99f,
		5.f, 0.5f,-4.99f

	};
	glm::vec3 V;
	for (int i = 0; i < (sizeof(vertex_array_data) / sizeof *vertex_array_data) - 2; i = i + 3) {
		V.x = vertex_array_data[i];
		V.y = vertex_array_data[i + 1];
		V.z = vertex_array_data[i + 2];
		room.push_back(V);
	}
}

//vertex data for the room
void Triangle::setRoom(std::vector<glm::vec3>  & room) {


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

		room.push_back(V);
		
	}
	std::cout << "Room: " << room.size() << std::endl;
}

void Triangle::setBox(std::vector<glm::vec3>  & room) {

	float vertex_array_data[] = {

		7.f, -4.f, -5.f,	//floor
		5.f, -2.5f, -5.f,
		7.f, -1.f, -5.f,

		5.f, -2.5f, -5.f,	//front left
		6.f, -2.5f, -3.f,
		7.f, -1.f, -5.f,

		5.f, -2.5f, -5.f,	//front right
		7.f, -4.f, -5.f,
		6.f, -2.5f, -3.f,

		7.f, -4.f , -5.f, //back
		7.f ,-1.f , -5.f,
		6.f ,-2.5f , -3.f,
	};

	glm::vec3 V;
	//std::cout << (sizeof(vertex_array_data) / sizeof *vertex_array_data) - 2 << "nr verts" << '\n';

	for (int i = 0; i < (sizeof(vertex_array_data) / sizeof *vertex_array_data) - 2; i = i + 3) {

		V.x = vertex_array_data[i];
		V.y = vertex_array_data[i + 1] ;
		V.z = vertex_array_data[i + 2] ;

		room.push_back(V);

	}
	std::cout << "Room: " << room.size() << std::endl;

}


void Triangle::setTriangles(std::vector<glm::vec3>  & room, std::vector<Triangle::tri> & triangles) {
	tri t;
	glm::vec3 u, v;

	for (int i = 0; i < room.size()-1; i=i+3) {
		t.vert[0] = room[i];
		t.vert[1] = room[i+1];
		t.vert[2] = room[i+2];

		u = t.vert[2] - t.vert[0];
		v = t.vert[1] - t.vert[0];
		t.normal = glm::normalize(glm::cross(v, u));
		//std::cout << i;
	
		triangles.push_back(t);
	}



	std::cout << "triangles: " << triangles.size() << std::endl;
	
	//floor room
	triangles.at(0).color = glm::vec3(230.f, 230.f, 230.f);
	triangles.at(0).mat.isDiffuse = true;
	triangles.at(1).color = glm::vec3(230.f, 230.f, 230.f);
	triangles.at(1).mat.isDiffuse = true;

	//Floor left
	triangles.at(2).color = glm::vec3(230.f, 230.f, 230.f);
	triangles.at(2).mat.isDiffuse = true;

	//Floor right
	triangles.at(3).color = glm::vec3(230.f, 230.f, 230.f);
	triangles.at(3).mat.isDiffuse = true;

	//Wall back Cyan
	triangles.at(4).color = glm::vec3(0.f, 255.f, 255.f);
	triangles.at(4).mat.isDiffuse = true;
	triangles.at(5).color = glm::vec3(0.f, 255.f, 255.f);
	triangles.at(5).mat.isDiffuse = true;

	//Right back Red
	triangles.at(6).color = glm::vec3(255.f,0.f,0.f);
	triangles.at(6).mat.isDiffuse = true;
	triangles.at(7).color = glm::vec3(255.f,0.f,0.f);
	triangles.at(7).mat.isDiffuse = true;

	//Right front Blue
	triangles.at(8).color = glm::vec3(0.f, 0.f, 255.f);
	triangles.at(8).mat.isDiffuse = true;

	triangles.at(9).color = glm::vec3(0.f, 0.f, 255.f);
	triangles.at(9).mat.isDiffuse = true;

	//Left back Green
	triangles.at(10).color = glm::vec3(0.f, 255.f, 0.f);
	triangles.at(10).mat.isDiffuse = true;

	triangles.at(11).color = glm::vec3(0.f, 255.f, 0.f);
	triangles.at(11).mat.isDiffuse = true;

	//Left front Yellow
	triangles.at(12).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(12).mat.isDiffuse = true;

	triangles.at(13).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(13).mat.isDiffuse = true;

	//Wall front  Magenta
	triangles.at(14).color = glm::vec3(255.f, 0.f, 255.f);
	triangles.at(14).mat.isDiffuse = true;
	triangles.at(15).color = glm::vec3(255.f, 0.f, 255.f);
	triangles.at(15).mat.isDiffuse = true;

	//Roof
	triangles.at(16).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(16).mat.isDiffuse = true;

	triangles.at(17).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(17).mat.isDiffuse = true;

	//Roof left
	triangles.at(18).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(18).mat.isDiffuse = true;

	//Roof right
	triangles.at(19).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(19).mat.isDiffuse = true;

	//###############################
	//floor tetra
	triangles.at(20).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(20).mat.isDiffuse = true;


	//right
	triangles.at(21).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(21).mat.isDiffuse = true;

	//left
	triangles.at(22).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(22).mat.isDiffuse = true;

	//back
	triangles.at(23).color = glm::vec3(255.f, 255.f, 0.f);
	triangles.at(23).mat.isDiffuse = true;

	//##############
	//areaLight
	triangles.at(24).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(24).mat.isLightSource = true;

	triangles.at(25).color = glm::vec3(255.f, 255.f, 255.f);
	triangles.at(25).mat.isLightSource = true;


}	


//adds spheres to the scene
void Triangle::setSpheres(std::vector<Triangle::sphere> & S) {
	//add 1 sphere to the scene
	sphere s1,s2;
	s1.center = glm::vec3(6.0f, -2.0f, 2.0f);
	s1.radius = 1.0f;
	s1.color = glm::vec3(100.0f, 100.0f, 100.0f);
	s1.mat.isSpecular = true;
	S.push_back(s1);

	s2.center = glm::vec3(6.0f, 2.0f, -3.0f);
	s2.radius = 0.8f;
	s2.color = glm::vec3(100.0f, 100.0f, 100.0f);
	s2.mat.isDiffuse = true;
	S.push_back(s2);

}


std::vector<Triangle::tri> Triangle::getTriangles() {
	return triangles;
}
std::vector<Triangle::sphere> Triangle::getSpheres() {
	return spheres;
}


//the void is calling
Triangle::~Triangle()
{
}
