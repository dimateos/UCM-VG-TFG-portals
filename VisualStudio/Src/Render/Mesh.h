#pragma once
#include <glad\glad.h>
#include <glm.hpp>

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);

	virtual void draw();
	inline glm::dvec3* getVertices() const { return vertices; };
	inline glm::dvec4* getColors() const { return colors; };

	//different static meshes
	static Mesh* generateAxesRGB(GLdouble l);

	static Mesh* generateTriangle(GLdouble r);
	static Mesh* generateTriangleRGB(GLdouble r);
	static Mesh* generateTriPyramid(GLdouble r, GLdouble h);
	static Mesh* generateContCube(GLdouble l);

protected:
	GLuint numVertices = 0;
	GLuint type = GL_POINTS;
	glm::dvec3* vertices = nullptr;
	glm::dvec4* colors = nullptr;
};