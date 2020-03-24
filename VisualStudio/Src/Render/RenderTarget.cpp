#include "RenderTarget.h"
#include <glad\glad.h>

RenderTarget::RenderTarget(Viewport * vp) : vp_(vp) {
	glGenFramebuffers(1, &ID_);
}
RenderTarget::~RenderTarget() {
	free();
}

void RenderTarget::free() {
	if (ID_ != -1) {
		glDeleteFramebuffers(1, &ID_);
		ID_ = -1;
	}
}

void RenderTarget::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, ID_);
	vp_->set();
}
void RenderTarget::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
