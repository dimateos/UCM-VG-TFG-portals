#pragma once
#include "Node.h"

#include "../Render/Viewport.h"
#include "../Render/Projection.h"

class Camera : public Node {
public:
	Camera(Viewport* vp, Projection* proj);
	virtual ~Camera();

	//for now
	virtual void update();

	inline glm::dmat4 const& getViewMatrix() const { return trans.getInvModelMatrix(); };
	inline const glm::f32* getViewMatrixPtr() const { return trans.getInvModelMatrixPtr(); };

	inline Viewport* getVP() const { return vp_; }
	inline Projection* getProj() const { return proj_; }

protected:
	Viewport* vp_;
	Projection* proj_;
};