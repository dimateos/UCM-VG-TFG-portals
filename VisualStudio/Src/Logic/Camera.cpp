#include "Camera.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Camera::Camera(Projection* proj) : Node(&Node::ROOT), proj_(proj) {}
Camera::~Camera() {}

glm::mat4 const& Camera::getViewMatrix() {
	//return getModelMatrix_Inversed(); //need to avoid Rolling rotation
	//Orientation = Z * Y * X from identity
	return getModelMatrix_Inversed(); //for now roll avoided in the input node
};

const glm::f32* Camera::getViewMatrixPtr() {
	return glm::value_ptr(getViewMatrix());
};
