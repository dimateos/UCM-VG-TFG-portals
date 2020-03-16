#pragma once

#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

//more constructors later
//https://gamedev.stackexchange.com/questions/94061/rotating-an-object-with-quaternion

enum Direction { RIGHT, LEFT, DOWN, UP, BACK, FORE }; //ordered as SDL enums
//enum Property { POSITION, ROTATION, SCALE };

class Transform
{
public:
	Transform();
	~Transform();

	glm::vec3 localPostion, localScale;
	glm::quat localRotation;

	void updateLocalModelMatrix();
	void updateModelMatrix(glm::mat4 const& fatherMatrix);
	glm::mat4 const& getModelMatrix() const;
	const glm::f32* getModelMatrixPtr() const;

	void updateInvLocalModelMatrix();
	void updateInvModelMatrix(glm::mat4 const& fatherMatrix);
	glm::mat4 const& getInvModelMatrix() const;
	const glm::f32* getInvModelMatrixPtr() const;

private:
	glm::mat4 computedLocalModelMatrix_, computedInvLocalModelMatrix_;
	glm::mat4 computedModelMatrix_, computedInvModelMatrix_;

	//bool state_[3]; //flags for outdated propery fields
};