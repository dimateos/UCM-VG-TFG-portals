#pragma once

#include "../Render/Viewport.h"

class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
	void free();

	bool create(Viewport* vp);
	bool setDefault(Viewport* vp);

	void bind(bool enableDepthTest);
	void unbind();
	void clear(float r, float g, float b, int flags);

	inline unsigned int getID() const { return ID_; };
	inline Viewport* getVP() const { return vp_; }

protected:
	unsigned int ID_ = -1;
	Viewport* vp_;
};