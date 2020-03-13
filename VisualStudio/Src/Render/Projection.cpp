#include "Projection.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Projection::Projection(float aspect, float fovY, float near, float far)
	: aspect(aspect), fov(fovY), near(near), far(far) {
	updateProjMatrix();
}

Projection::~Projection() {}

void Projection::updateProjMatrix() {
	//atm just perspective
	_computedProjMatrix = glm::perspective(
		glm::radians(fov), aspect, near, far
	);
}

glm::mat4 Projection::getProjMatrix() const {
	return _computedProjMatrix;
}
const glm::f32 * Projection::getProjMatrixPtr() const {
	return glm::value_ptr(_computedProjMatrix);
}
