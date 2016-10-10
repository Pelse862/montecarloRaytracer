#pragma once
#include "Triangle.h"

#include <vector>
#include <memory>
class Scene
{
  public:
	  Scene();
	  ~Scene();
	  void Scene::setRoom( std::vector<float> & room );
	  
  private:
	  Triangle roomTriangles;
	  
  

};

