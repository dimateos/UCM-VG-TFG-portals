#pragma once
#include "Node.h"

#include "../Render/Viewport.h"
#include "../Render/Projection.h"

class Camera : public Node {
public:
	Camera(Viewport* vp, Projection* proj);
	virtual ~Camera();

	inline glm::dmat4 const& getViewMatrix() { return getModelMatrix_Inversed(); };
	inline const glm::f32* getViewMatrixPtr() { return getModelMatrix_Inversed_ptr(); };

	inline Viewport* getVP() const { return vp_; }
	inline Projection* getProj() const { return proj_; }

protected:
	Viewport* vp_;
	Projection* proj_;
};