#pragma once
#include "Transform.h"

#include "../Render/Viewport.h"
#include "../Render/Projection.h"

class Camera {
public:
	Camera(Viewport* vp, Projection* proj);
	~Camera();

	Transform trans; //special inversed trandorm?
	inline glm::dmat4 const& getViewMatrix() const { return trans.getInvModelMatrix(); };
	inline const glm::f32* getViewMatrixPtr() const { return trans.getInvModelMatrixPtr(); };

	inline Viewport* getVP() const { return _vp; }
	inline Projection* getProj() const { return _proj; }

protected:
	Viewport* _vp;
	Projection* _proj;
};