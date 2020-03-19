#include "InputCameraRotation.h"
#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

#include "../Platform/Window_SDL_GL.h"
#include <gtc/type_ptr.hpp>

InputCameraRotation::InputCameraRotation(Node* father, Camera * cam) : Node(father), cam_(cam) {
	Platform_SDL::mouseMotionEventEmitter_.registerListener(this);
	Platform_SDL::keyEventEmitter_.registerListener(this);

	//hide and capture mouse
	//SDL_ShowCursor(SDL_DISABLE); //no need
	SDL_SetRelativeMouseMode(focus_ ? SDL_TRUE : SDL_FALSE);
}

InputCameraRotation::~InputCameraRotation() {}

bool InputCameraRotation::handleEvent(SDL_Event const & e) {
	bool handled = true;

	if (e.type == SDL_MOUSEMOTION) {
		rotY_ = e.motion.xrel;
		rotX_ = e.motion.yrel;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LALT) {
		focus_ = !focus_;
		SDL_SetRelativeMouseMode(focus_ ? SDL_TRUE : SDL_FALSE);
		rotY_ = rotX_ = 0;
	}
	else handled = false;

	//else printf("cube - ignored event type: %i\n", e.type);
	return handled;
}

void InputCameraRotation::update() {
	if (!focus_) return;

	//horizontal rotation
	if (rotY_ != 0) {
		float frame_rotY = sens_ * -rotY_;

		cam_->yaw(frame_rotY);
		rotY_ = 0;
	}

	//limit the vertical rotation (x axis)
	if (rotX_ != 0) {
		float frame_rotX = sens_ * -rotX_;
		total_rotX_ += frame_rotX;

		if (total_rotX_ > maxRotX_) {
			frame_rotX -= total_rotX_ - maxRotX_;
			total_rotX_ = maxRotX_;
		}
		else if (total_rotX_ < -maxRotX_) {
			frame_rotX -= total_rotX_ + maxRotX_;
			total_rotX_ = -maxRotX_;
		}

		cam_->pitch(frame_rotX);
		rotX_ = 0;
	}
}
