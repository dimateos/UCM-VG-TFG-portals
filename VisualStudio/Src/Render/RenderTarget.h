#pragma once

#include "../Render/Viewport.h"

class RenderTarget
{
public:
	RenderTarget(Viewport* vp);
	~RenderTarget();
	void free();

	void bind();
	void unbind();

	inline unsigned int getID() const { return ID_; };
	inline Viewport* getVP() const { return vp_; }

protected:
	unsigned int ID_ = -1;
	Viewport* vp_;
};