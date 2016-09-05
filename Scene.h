#pragma once
#include "Triangle.h"
#include <vector>
class Scene
{
  public:
	  Scene();
	  ~Scene();
	  void Scene::setRoom( std::vector<float> & room );
  private:
	  Triangle roomTriangles;
  

};

