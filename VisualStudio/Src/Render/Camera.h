#pragma once
#include <glad\glad.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Viewport {
public:
	Viewport(GLsizei aw, GLsizei ah) : w(aw), h(ah) { };
	~Viewport() { };

	void setSize(GLsizei aw, GLsizei ah);

	//NEW
	void setPos(GLint ax, GLint ay) { x = ax; y = ay, set(); };

	GLint getX() { return x; };
	GLint getY() { return y; };
	GLsizei getW() { return w; };
	GLsizei getH() { return h; };

protected:
	GLint x = 0, y = 0;
	GLsizei w, h;
	void set();
};

//-------------------------------------------------------------------------

class Camera {
public:
	Camera(Viewport* avp) : vp(avp), viewMat(1.0), projMat(1.0),
		xRight(avp->getW() / 2.0), xLeft(-xRight), yTop(avp->getH() / 2.0), yBot(-yTop) {};
	~Camera() {};

	Viewport* getVP() { return vp; }

	// view matrix
	glm::dmat4 const& getViewMat() { return viewMat; };

	void setAZ();  // lookAt(eye(0,0,500), look(0,0,0) up(0, 1, 0))
	void set3D();  // lookAt(eye(500,500,500), look(0,10,0) up(0, 1, 0))
	void setReverse3D();  // lookAt(eye(500,500,500), look(0,10,0) up(0, 1, 0))

	void pitch(GLdouble a); // rotates a degrees on the X axis
	void yaw(GLdouble a);   // rotates a degrees on the Y axis
	void roll(GLdouble a);  // rotates a degrees on the Z axis

	// projection matrix
	glm::dmat4 const& getProjMat() { return projMat; };

	void setSize(GLdouble aw, GLdouble ah);
	void scale(GLdouble s);
	void setScale(GLdouble s);

protected:
	glm::dvec3 position = glm::dvec3(0.0f, 0.0f, 5.0f);
	glm::dvec3 target = glm::dvec3(0.0f, 0.0f, 0.0f);
	glm::dvec3 up = glm::dvec3(0.0f, 1.0f, 0.0f);

	glm::dmat4 viewMat;  // inverse
	glm::dmat4 projMat;

	GLdouble xRight, xLeft, yTop, yBot;
	GLdouble nearVal = 1;
	GLdouble farVal = 10000;
	GLdouble factScale = 1;

	Viewport* vp;

	void setVM();
	void setPM();
};