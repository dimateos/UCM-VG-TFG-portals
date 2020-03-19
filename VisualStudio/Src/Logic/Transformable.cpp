#include "Transformable.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Transformable::Transformable(Transformable * father_transform) : local_trans_(Transformation::BASE), father_transform_(father_transform) {
	forceUpdateTransformable();
}
Transformable::~Transformable() {}

void Transformable::forceUpdateTransformable() {
	setOutDated();
	if (father_transform_ == nullptr) return;
	getModelMatrix();
	getModelMatrix_Inversed();
}

glm::mat4 const& Transformable::getModelMatrix() {
	if (outdated_flags_[MATRIX]) {
		local_computedMatrix_ = local_trans_.matrix();
		outdated_flags_[MATRIX] = false;
	}
	//no father, then return the local
	if (father_transform_ == nullptr) return local_computedMatrix_;

	//atm no need to store it but well see
	computedMatrix_ = father_transform_->getModelMatrix() * local_computedMatrix_;
	return computedMatrix_;
}
const glm::f32 * Transformable::getModelMatrix_ptr() {
	return glm::value_ptr(getModelMatrix());
}

glm::mat4 const& Transformable::getModelMatrix_Inversed() {
	if (outdated_flags_[MATRIX_INVERSED]) {
		local_computedMatrix_Inversed_ = local_trans_.matrix_Inversed();
		outdated_flags_[MATRIX_INVERSED] = false;
	}
	//no father, then return the local
	if (father_transform_ == nullptr) return local_computedMatrix_Inversed_;

	computedMatrix_Inversed_ = local_computedMatrix_Inversed_ * father_transform_->getModelMatrix_Inversed();
	return computedMatrix_Inversed_;
}
const glm::f32 * Transformable::getModelMatrix_Inversed_ptr() {
	return glm::value_ptr(getModelMatrix_Inversed());
}


