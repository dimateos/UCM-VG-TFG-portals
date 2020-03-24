#include "RenderTarget.h"
#include <glad\glad.h>

RenderTarget::RenderTarget() {}
RenderTarget::~RenderTarget() {
	free();
}
void RenderTarget::free() {
	if (ID_ != -1) {
		glDeleteFramebuffers(1, &ID_);
		ID_ = -1;
	}
}

bool RenderTarget::create(Viewport * vp) {
	//check already created etc

	glGenFramebuffers(1, &ID_);
	vp_ = vp;
	return true; //could check errors
}

bool RenderTarget::setDefault(Viewport * vp) {
	ID_ = 0;
	vp_ = vp;
	return false;
}

void RenderTarget::bind(bool enableDepthTest) {
	glBindFramebuffer(GL_FRAMEBUFFER, ID_);
	vp_->set();
	enableDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}
void RenderTarget::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::clear(float r, float g, float b, int flags) {
	glClearColor(r, g, b, 1.0);
	glClear(flags);
}
