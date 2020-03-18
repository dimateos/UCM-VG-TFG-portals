#include "FPS.h"
#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

#include "../Platform/Window_SDL_GL.h"
#include <gtc/type_ptr.hpp>

FPS::FPS(Camera * cam) : Node(&Node::ROOT), cam_(cam) {
	Platform_SDL::keyEventEmitter_.registerListener(this);
	Platform_SDL::mouseMotionEventEmitter_.registerListener(this);

	cam_->father = this;

	//hide and capture mouse
	//SDL_ShowCursor(SDL_DISABLE); //no need
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//SDL_ShowCursor(SDL_ENABLE);
	//SDL_SetRelativeMouseMode(SDL_FALSE);
}

FPS::~FPS() {}

bool FPS::handleEvent(SDL_Event const & e) {
	bool handled = true;

	if (e.type == SDL_MOUSEMOTION) {
		rotY_ = e.motion.xrel;
		rotX_ = e.motion.yrel;
	}

	else if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_d: xAxis_.push_front(RIGHT); break;
		case SDLK_a: xAxis_.push_front(LEFT); break;
		case SDLK_s: zAxis_.push_front(BACK); break;
		case SDLK_w: zAxis_.push_front(FORE); break;
		case SDLK_SPACE: yAxis_.push_front(UP); break;
		case SDLK_c: yAxis_.push_front(DOWN); break;

		default: handled = false;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_d: xAxis_.remove(RIGHT); break;
		case SDLK_a: xAxis_.remove(LEFT); break;
		case SDLK_s: zAxis_.remove(BACK); break;
		case SDLK_w: zAxis_.remove(FORE); break;
		case SDLK_SPACE: yAxis_.remove(UP); break;
		case SDLK_c: yAxis_.remove(DOWN); break;

		default: handled = false;
		}
	}

	else handled = false;

	//else printf("cube - ignored event type: %i\n", e.type);
	return handled;
}

void FPS::update() {
	//ROTATION
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

		cam_->trans.localRotation *= glm::angleAxis(glm::radians(frame_rotX), glm::vec3(1.f, 0.f, 0.f));
		//printf("fps - total x rot: %f\n", total_rotX_);
		rotX_ = 0;
	}

	if (rotY_ != 0) {
		float frame_rotY = sens_ * -rotY_;

		trans.localRotation *= glm::angleAxis(glm::radians(frame_rotY), glm::vec3(0.f, 1.f, 0.f));
		printf("fps - local rot: %f %f %f %f\n", trans.localRotation.x, trans.localRotation.y, trans.localRotation.z, trans.localRotation.w);
		rotY_ = 0;
	}

	//MOVEMENT
	velocity_ = glm::vec3(0);

	if (!xAxis_.empty()) {
		if (xAxis_.front() == RIGHT) velocity_.x = 1;
		else velocity_.x = -1;
	}
	if (!zAxis_.empty()) {
		if (zAxis_.front() == FORE) velocity_.z = -1;
		else velocity_.z = 1;
	}
	if (!yAxis_.empty()) {
		if (yAxis_.front() == UP) velocity_.y = 1;
		else velocity_.y = -1;
	}

	if (velocity_.x != 0 || velocity_.z != 0 || velocity_.y != 0) {
		velocity_ = glm::normalize(velocity_) * speed_;
		cam_->trans.localPostion += velocity_ * Platform_SDL::getDeltaTimef();
	}

	updateInvTransform();
	cam_->updateInvTransform();
}
