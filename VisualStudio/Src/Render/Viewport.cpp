#include "Viewport.h"
#include <glad\glad.h>

Viewport::Viewport(int w, int h) : w_(w), h_(h), x_(0), y_(0), aspect_(w / h) {}
Viewport::~Viewport() {}

void Viewport::setSize(int w, int h) {
	w_ = w;
	h_ = h;
	aspect_ = (float)w_ / (float)h_;
}
void Viewport::setPos(int x, int y) {
	x_ = x;
	y_ = y;
}

void Viewport::set()
{
	glViewport(x_, y_, w_, h_);
}
