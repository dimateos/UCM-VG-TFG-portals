#pragma once
#include "Node.h"

#include "../Render/Projection.h"

class Camera : public Node {
public:
	Camera(Projection* proj);
	virtual ~Camera();

	glm::mat4 const& getViewMatrix();
	const glm::f32* getViewMatrixPtr();

	inline Projection* getProj() const { return proj_; }

protected:
	Projection* proj_;
};