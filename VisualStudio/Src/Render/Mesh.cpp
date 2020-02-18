#include "Mesh.h"

using namespace glm;

Mesh::Mesh(void) {}
Mesh ::~Mesh(void) {
	delete[] vertices;
	delete[] colors;
}

void Mesh::draw() {
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate

		if (colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate
		}

		glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}

////////////////////////////////////////////////////////////////////////////////

Mesh * Mesh::generateAxesRGB(GLdouble l) {
	Mesh* m = new Mesh();
	m->type = GL_LINES;
	m->numVertices = 6;
	m->vertices = new dvec3[m->numVertices];
	m->colors = new dvec4[m->numVertices];

	//generate the vertices
	m->vertices[0] = dvec3(0.0, 0.0, 0.0);
	m->vertices[1] = dvec3(l, 0.0, 0);
	m->vertices[2] = dvec3(0, 0.0, 0.0);
	m->vertices[3] = dvec3(0.0, l, 0.0);
	m->vertices[4] = dvec3(0.0, 0.0, 0.0);
	m->vertices[5] = dvec3(0.0, 0.0, l);

	//rgb colors
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

Mesh * Mesh::generateTriangle(GLdouble r) {
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;
	m->vertices = new dvec3[m->numVertices];
	m->colors = new dvec4[m->numVertices];

	//generate the vertices
	double x, y, ang;
	float degrees = 90; //first the upper vertex
	for (size_t i = 0; i < m->numVertices; i++) {
		ang = radians(degrees);
		x = r * cos(ang);
		y = r * sin(ang);

		m->vertices[i] = dvec3(x, y, 0.0);
		degrees += 120;
	}

	//blank
	for (size_t i = 0; i < m->numVertices; i++)
		m->colors[i] = dvec4(0.0, 0.0, 0.0, 1.0);

	return m;
}

Mesh * Mesh::generateTriangleRGB(GLdouble r) {
	Mesh* m = generateTriangle(r); //base triangle

	//change the colors
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

Mesh * Mesh::generateTriPyramid(GLdouble r, GLdouble h) {
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_FAN;
	m->numVertices = 5;
	m->vertices = new dvec3[m->numVertices];
	m->colors = new dvec4[m->numVertices];

	//generate the vertices
	m->vertices[0] = dvec3(0.0, 0.0, h); //common vertex
	double x, y, ang;
	float degrees = 90;
	for (size_t i = 1; i < m->numVertices; i++) {
		ang = radians(degrees);
		x = r * cos(ang);
		y = r * sin(ang);

		m->vertices[i] = dvec3(x, y, 0);
		degrees += 120;
	}

	//non blank
	m->colors[0] = dvec4(0.25, 0.25, 0.25, 1.0);
	for (size_t i = 1; i < m->numVertices; i++)
		m->colors[i] = dvec4(1.0, 0.0, 0.0, 1.0);

	return m;
}

Mesh * Mesh::generateContCube(GLdouble l) {
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	//m->numVertices = 6 * 2 * 3;
	m->numVertices = 14;
	m->vertices = new dvec3[m->numVertices];
	m->colors = new dvec4[m->numVertices];

	//generate the vertices
	m->vertices[0] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[1] = dvec3(l / 2, l / 2, -l / 2);
	m->vertices[2] = dvec3(-l / 2, -l / 2, -l / 2);
	m->vertices[3] = dvec3(l / 2, -l / 2, -l / 2);
	m->vertices[4] = dvec3(l / 2, -l / 2, l / 2);
	m->vertices[5] = dvec3(l / 2, l / 2, -l / 2);
	m->vertices[6] = dvec3(l / 2, l / 2, l / 2);
	m->vertices[7] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[8] = dvec3(-l / 2, l / 2, l / 2);
	m->vertices[9] = dvec3(-l / 2, -l / 2, -l / 2);
	m->vertices[10] = dvec3(-l / 2, -l / 2, l / 2);
	m->vertices[11] = dvec3(l / 2, -l / 2, l / 2);
	m->vertices[12] = dvec3(-l / 2, l / 2, l / 2);
	m->vertices[13] = dvec3(l / 2, l / 2, l / 2);

	//blank
	for (size_t i = 0; i < m->numVertices; i++)
		m->colors[i] = dvec4(0.0, 0.0, 0.0, 1.0);

	return m;
}