#include "Transform.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Transform::Transform() {
	localPostion = glm::vec3(0.0f);
	localScale = glm::vec3(1.0f);
	localRotation = glm::angleAxis(glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
	updateModelMatrix();
}

Transform::~Transform() {}

void Transform::updateModelMatrix() {
	glm::mat4 translate = glm::translate(glm::mat4(1.0), localPostion);
	glm::mat4 rotate = glm::mat4_cast(localRotation);
	glm::mat4 scale = glm::scale(glm::mat4(1.0), localScale);

	_computedLocalModelMatrix = translate * rotate * scale;
}

glm::mat4 Transform::getModelMatrix() const {
	return _computedLocalModelMatrix;
}
const glm::f32 * Transform::getModelMatrixPtr() const {
	return glm::value_ptr(_computedLocalModelMatrix);
}


