#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "vertex.h"
#include "triangle.h"

class SceneObject {

	public:
		virtual ~SceneObject() = default;


		Vertex get_position() { return position_; }

	protected:
		SceneObject(Vertex position) { position_ = position; }
		SceneObject() = default;
		Vertex position_;
		//std::vector<Triangle> triangles_;
};

#endif // SCENE_OBJECT_H
