#include "FPS.h"

#include <glad\glad.h>

#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

#include "../Platform/Window_SDL_GL.h"
#include <gtc/type_ptr.hpp>

FPS::FPS(Camera * cam) : Node(&Node::ROOT), cam_(cam) {
	Platform_SDL::_keyEventEmitter.registerListener(this);

	cam_->father = this;
}

FPS::~FPS() {}

bool FPS::handleEvent(SDL_Event const & e) {
	bool handled = false;

	if (e.type == SDL_KEYDOWN) {
		handled = true;

		switch (e.key.keysym.sym) {
		case SDLK_d: xAxis_.push_front(RIGHT); break;
		case SDLK_a: xAxis_.push_front(LEFT); break;
		case SDLK_s: zAxis_.push_front(DOWN); break;
		case SDLK_w: zAxis_.push_front(UP); break;

		default: handled = false;
		}
	}
	else if (e.type == SDL_KEYUP) {
		handled = true;

		switch (e.key.keysym.sym) {
		case SDLK_d: xAxis_.remove(RIGHT); break;
		case SDLK_a: xAxis_.remove(LEFT); break;
		case SDLK_s: zAxis_.remove(DOWN); break;
		case SDLK_w: zAxis_.remove(UP); break;

		default: handled = false;
		}
	}

	//else printf("cube - ignored event type: %i\n", e.type);
	return handled;
}

void FPS::update() {
	velocity_ = glm::vec3(0);

	if (!xAxis_.empty()) {
		if (xAxis_.front() == RIGHT) velocity_.x = 1;
		else velocity_.x = -1;
	}
	if (!zAxis_.empty()) {
		if (zAxis_.front() == UP) velocity_.z = 1;
		else velocity_.z = -1;
	}

	if (velocity_.x != 0 || velocity_.z != 0) {
		velocity_ = glm::normalize(velocity_) * speed_;
		trans.localPostion += velocity_ * Platform_SDL::getDeltaTimef();
		updateInvTransform();
		cam_->updateInvTransform();
	}
}
