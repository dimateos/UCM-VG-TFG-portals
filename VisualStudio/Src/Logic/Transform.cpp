#include "Transform.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Transform::Transform() {
	localPostion = glm::vec3(0.0f);
	localScale = glm::vec3(1.0f);
	localRotation = glm::angleAxis(glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
	//localRotation = glm::quat(0.f, 0.f, 0.f, 1.0f);
	updateModelMatrix();
	updateInvModelMatrix();
}
Transform::~Transform() {}

void Transform::updateModelMatrix() {
	glm::mat4 translate = glm::translate(glm::mat4(1.0), localPostion);
	glm::mat4 rotate = glm::mat4_cast(localRotation);
	glm::mat4 scale = glm::scale(glm::mat4(1.0), localScale);

	computedLocalModelMatrix_ = translate * rotate * scale;
}
glm::mat4 const& Transform::getModelMatrix() const {
	return computedLocalModelMatrix_;
}
const glm::f32 * Transform::getModelMatrixPtr() const {
	return glm::value_ptr(computedLocalModelMatrix_);
}

void Transform::updateInvModelMatrix() {
	glm::mat4 translate = glm::translate(glm::mat4(1.0), -localPostion);
	glm::mat4 rotate = glm::mat4_cast(glm::inverse(localRotation));
	glm::mat4 scale = glm::scale(glm::mat4(1.0), 1.0f / localScale);

	computedInvLocalModelMatrix_ = translate * rotate * scale;
}
glm::mat4 const& Transform::getInvModelMatrix() const {
	return computedInvLocalModelMatrix_;
}
const glm::f32 * Transform::getInvModelMatrixPtr() const {
	return glm::value_ptr(computedInvLocalModelMatrix_);
}


