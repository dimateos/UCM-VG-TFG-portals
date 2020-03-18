#include "InputFreeMovement.h"

//delta time and events
#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

InputFreeMovement::InputFreeMovement(Node* fatherToMove) : Node(fatherToMove) {
	Platform_SDL::keyEventEmitter_.registerListener(this);

	iniPostion = father_->trans.localPostion;
	iniRotation = father_->trans.localRotation;
}

InputFreeMovement::~InputFreeMovement() {}

bool InputFreeMovement::handleEvent(SDL_Event const & e) {
	bool handled = true;

	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			//combined keys
		case SDLK_d: !rotating_ ? xAxis_.push_front(RIGHT) : rot_yAxis_.push_front(RIGHT); break;
		case SDLK_a: !rotating_ ? xAxis_.push_front(LEFT) : rot_yAxis_.push_front(LEFT); break;
		case SDLK_s: !rotating_ ? zAxis_.push_front(BACK) : rot_xAxis_.push_front(BACK); break;
		case SDLK_w: !rotating_ ? zAxis_.push_front(FORE) : rot_xAxis_.push_front(FORE); break;

			//separated keys
		case SDLK_SPACE: yAxis_.push_front(UP); break;
		case SDLK_c: yAxis_.push_front(DOWN); break;
		case SDLK_e: rot_zAxis_.push_front(RIGHT); break;
		case SDLK_q: rot_zAxis_.push_front(LEFT); break;

			//rotate / sprinting keys
		case SDLK_LSHIFT: sprinting_ = (sprint_toggleMode_ ? !sprinting_ : true); break;
		case SDLK_r: rotating_ = (rotate_toggleMode_ ? !rotating_ : true); break;

			//reset key
		case SDLK_t: !rotating_ ? father_->trans.localPostion = iniPostion : father_->trans.localRotation = iniRotation; break;

		default: handled = false;
		}
	}
	else if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			//combined keys
		case SDLK_d: !rotating_ ? xAxis_.remove(RIGHT) : rot_yAxis_.remove(RIGHT); break;
		case SDLK_a: !rotating_ ? xAxis_.remove(LEFT) : rot_yAxis_.remove(LEFT); break;
		case SDLK_s: !rotating_ ? zAxis_.remove(BACK) : rot_xAxis_.remove(BACK); break;
		case SDLK_w: !rotating_ ? zAxis_.remove(FORE) : rot_xAxis_.remove(FORE); break;

			//separated keys
		case SDLK_SPACE: yAxis_.remove(UP); break;
		case SDLK_c: yAxis_.remove(DOWN); break;
		case SDLK_e: rot_zAxis_.remove(RIGHT); break;
		case SDLK_q: rot_zAxis_.remove(LEFT); break;

			//rotate / sprinting keys
		case SDLK_LSHIFT: sprinting_ = (sprint_toggleMode_ ? sprinting_ : false); break;
		case SDLK_r: rotating_ = (rotate_toggleMode_ ? rotating_ : false); break;

		default: handled = false;
		}
	}

	else handled = false;

	//else printf("cube - ignored event type: %i\n", e.type);
	return handled;
}

void InputFreeMovement::update() {
	//ROTATION
	frame_rotation_ = glm::vec3(0);

	if (!rot_xAxis_.empty()) {
		if (rot_xAxis_.front() == BACK) frame_rotation_.x = 1;
		else frame_rotation_.x = -1;
	}
	if (!rot_zAxis_.empty()) {
		if (rot_zAxis_.front() == RIGHT) frame_rotation_.z = -1;
		else frame_rotation_.z = 1;
	}
	if (!rot_yAxis_.empty()) {
		if (rot_yAxis_.front() == RIGHT) frame_rotation_.y = 1;
		else frame_rotation_.y = -1;
	}

	//apply rotation if non zero
	if (frame_rotation_.x != 0 || frame_rotation_.z != 0 || frame_rotation_.y != 0) {
		frame_rotation_ = glm::normalize(frame_rotation_) * rotation_speed_;
		frame_rotation_ *= (sprinting_ ? sprint_scaler_ : 1.0f) * Platform_SDL::getDeltaTimef();

		//euler angles
		father_->trans.localRotation *= glm::angleAxis(glm::radians(frame_rotation_.x), glm::vec3(1.f, 0.f, 0.f));
		father_->trans.localRotation *= glm::angleAxis(glm::radians(frame_rotation_.y), glm::vec3(0.f, 1.f, 0.f));
		father_->trans.localRotation *= glm::angleAxis(glm::radians(frame_rotation_.z), glm::vec3(0.f, 0.f, 1.f));
	}

	//MOVEMENT
	frame_velocity_ = glm::vec3(0);

	if (!xAxis_.empty()) {
		if (xAxis_.front() == RIGHT) frame_velocity_.x = 1;
		else frame_velocity_.x = -1;
	}
	if (!zAxis_.empty()) {
		if (zAxis_.front() == FORE) frame_velocity_.z = -1;
		else frame_velocity_.z = 1;
	}
	if (!yAxis_.empty()) {
		if (yAxis_.front() == UP) frame_velocity_.y = 1;
		else frame_velocity_.y = -1;
	}

	//apply velocity if non zero
	if (frame_velocity_.x != 0 || frame_velocity_.z != 0 || frame_velocity_.y != 0) {
		frame_velocity_ = glm::normalize(frame_velocity_) * speed_;
		frame_velocity_ *= (sprinting_ ? sprint_scaler_ : 1.0f) * Platform_SDL::getDeltaTimef();

		//directly add
		father_->trans.localPostion += frame_velocity_;
	}

	father_->updateTransform();
}
