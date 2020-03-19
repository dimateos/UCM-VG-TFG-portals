#include "Transformable.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Transformable::Transformable(Transformable * father_transform) : local_trans_(Transformation::BASE), father_transform_(father_transform) {
	forceUpdateTransform();
}
Transformable::~Transformable() {}

void Transformable::forceUpdateTransform() {
	setOutDated();
	if (father_transform_ != nullptr) return;
	getModelMatrix();
	getModelMatrix_Inversed();
}

glm::mat4 const& Transformable::getModelMatrix() {
	if (outdated_flags_[MATRIX]) {
		local_computedMatrix_ = local_trans_.matrix();
		computedMatrix_ = father_transform_ == nullptr ? IDENTITY_MAT : father_transform_->getModelMatrix();
		computedMatrix_ *= local_computedMatrix_;
		outdated_flags_[MATRIX] = false;
	}
	return computedMatrix_;
}
const glm::f32 * Transformable::getModelMatrix_ptr() {
	return glm::value_ptr(getModelMatrix());
}

glm::mat4 const& Transformable::getModelMatrix_Inversed() {
	if (outdated_flags_[MATRIX_INVERSED]) {
		local_computedMatrix_Inversed_ = local_trans_.matrix_Inversed();
		computedMatrix_Inversed_ = father_transform_ == nullptr ? IDENTITY_MAT : father_transform_->getModelMatrix_Inversed();
		computedMatrix_Inversed_ *= local_computedMatrix_Inversed_;
		outdated_flags_[MATRIX_INVERSED] = false;
	}
	return computedMatrix_;
}
const glm::f32 * Transformable::getModelMatrix_Inversed_ptr() {
	return glm::value_ptr(getModelMatrix_Inversed());
}


