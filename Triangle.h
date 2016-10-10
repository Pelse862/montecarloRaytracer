#pragma once


#include "Vertex.h"
#include "ColorDbl.h"
#include "Ray.h"
#include "glm.hpp"
#include "SceneObject.h"
#include "triangle_custom_shape.h"
#include <vector>
#include <memory>
class Triangle
{
	public:
		
		//triangle structure
		struct tri {
			glm::vec3 vert[3];
			glm::vec3 normal;
			glm::vec3 color;
		};
		//sphere structure
		struct sphere {
			glm::vec3 center;
			glm::vec3 color;
			float radius;
		};

		Triangle() ;
		Triangle(Vertex v0, Vertex v1, Vertex v2, glm::vec3 c);
		//send all triangles to the function.
		void molllerTrombore(std::vector<Triangle>  triangles, Ray & r, glm::vec3 & intersectionPoint, glm::vec3 & pixelColor, int & id);

		void setRoom(std::vector<Triangle>  room2);
		void setBox(std::vector<Triangle>   room);
		
		//check intersect for implicit sphere
		void sphereIntersect(std::vector<sphere> & spheres, Ray & r, glm::vec3 & intersectionPoint, glm::vec3 & pixelColor, int & id);

		void setTriangles(std::vector<glm::vec3>  & room, std::vector<Triangle::tri> & tri);

		void setSpheres(std::vector<sphere> & S);

		glm::vec3 getNormal() { return normal; };
		
		std::vector<Triangle> getTriangles();
		std::vector<sphere> getSpheres();


		~Triangle();


	private:
		Vertex v0_, v1_, v2_;
		glm::vec3 normal;
		glm::vec3 color;

		std::vector<Triangle> roomVertices;
		std::vector<tri> triangles;
		std::vector<sphere> spheres;
		ColorDbl color2;

		//std::vector<std::unique_ptr<SceneObject>> scene_objects_;

};


