#pragma once
#include "Node.h"

#include "../Render/Viewport.h"
#include "../Render/Projection.h"

class Camera : public Node {
public:
	Camera(Viewport* vp, Projection* proj);
	virtual ~Camera();

	glm::mat4 const& getViewMatrix();
	const glm::f32* getViewMatrixPtr();

	inline Viewport* getVP() const { return vp_; }
	inline Projection* getProj() const { return proj_; }

protected:
	Viewport* vp_;
	Projection* proj_;
};