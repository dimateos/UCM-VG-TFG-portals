#include "Viewport.h"
#include <glad\glad.h>

Viewport::Viewport(int w, int h) : _w(w), _h(h), _x(0), _y(0), _aspect(w / h) {}
Viewport::~Viewport() {}

void Viewport::setSize(int w, int h) {
	_w = w;
	_h = h;
	_aspect = (float)_w / (float)_h;
}
void Viewport::setPos(int x, int y) {
	_x = x;
	_y = y;
}

void Viewport::set()
{
	glViewport(_x, _y, _w, _h);
}
