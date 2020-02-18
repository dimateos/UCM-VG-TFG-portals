#include "Camera.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Viewport::setSize(GLsizei aw, GLsizei ah)
{
	w = aw;
	h = ah;
	set();
}
//-------------------------------------------------------------------------

void Viewport::set()
{
	glViewport(x, y, w, h);
}
//-------------------------------------------------------------------------

void Camera::setAZ()
{
	position = dvec3(0, 0, 500);
	target = dvec3(0, 0, 0);
	up = dvec3(0, 1, 0);
	viewMat = lookAt(position, target, up);
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D()
{
	position = dvec3(500, 500, 500);
	target = dvec3(0, 10, 0);
	up = dvec3(0, 1, 0);
	viewMat = lookAt(position, target, up);
	setVM();
}
void Camera::setReverse3D()
{
	position = dvec3(-500, -500, -500);
	target = dvec3(0, 10, 0);
	up = dvec3(0, 1, 0);
	viewMat = lookAt(position, target, up);
	setVM();
}
//-------------------------------------------------------------------------

void Camera::setVM()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{
	factScale -= s;
	if (s < 0) s = 0.01; //?? useless
	setPM();
}
void Camera::setScale(GLdouble s)
{
	factScale = s;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah)
{
	xRight = aw / 2.0;
	xLeft = -xRight;
	yTop = ah / 2.0;
	yBot = -yTop;

	setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM()
{
	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------


