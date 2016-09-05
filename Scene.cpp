#include "Scene.h"
#include <vector>


Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::setRoom( std::vector<float>  & room ) {
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
	 for (int i = 0; i < 180; i++) {
		 room.push_back(vertex_array_data[i]);
	}
	
}