#include "Camera.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Camera::Camera(Viewport * vp, Projection* proj) : _vp(vp), _proj(proj) {}
Camera::~Camera() {}

