#include "Projection.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Projection::Projection(float near, float far)
	: near(near), far(far) {
	//updateProjMatrix();
}
Projection::~Projection() {}

glm::mat4 Projection::getProjMatrix() const {
	return computedProjMatrix_;
}
const glm::f32 * Projection::getProjMatrixPtr() const {
	return glm::value_ptr(computedProjMatrix_);
}

PerspectiveProjection::PerspectiveProjection(float aspect, float fovY, float near, float far)
	: Projection (near, far), aspect(aspect), fov(fovY) {
	updateProjMatrix();
}
PerspectiveProjection::~PerspectiveProjection() {}

void PerspectiveProjection::updateProjMatrix() {
	computedProjMatrix_ = glm::perspective(
		glm::radians(fov), aspect, near, far
	);
}

OrthoProjection::OrthoProjection(float w, float h, float zoom, float near, float far)
	: Projection(near, far), w(w), h(h), zoom(zoom) {
	updateProjMatrix();
}
OrthoProjection::~OrthoProjection() { }

void OrthoProjection::updateProjMatrix() {
	computedProjMatrix_ = glm::ortho (
		zoom * -w/2, zoom * w/2, zoom * -h/2, zoom * h/2, near, far
	);
}
