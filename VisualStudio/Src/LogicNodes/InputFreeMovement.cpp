#include "InputFreeMovement.h"
#include "../GlobalConfig.h" //input config

//delta time and events
#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

InputFreeMovement::InputFreeMovement(Node * father, Node * target, Node * rotationReference, bool disable_rotation)
	: Node(father), target_(target), rotationReference_(rotationReference), disable_rotation_(disable_rotation) {
	Platform_SDL::keyEventEmitter_.registerListener(this);

	setTarget(target, rotationReference);
}

InputFreeMovement::~InputFreeMovement() {}

bool InputFreeMovement::handleEvent(SDL_Event const & e) {
	bool handled = true;

	if (e.type == SDL_KEYDOWN) {
		const char key = e.key.keysym.sym;

		//movement
		if (key == GlobalConfig::ACTION_moveRIGHT) !rotating_ ? xAxis_.push_front(RIGHT) : rot_yAxis_.push_front(RIGHT);
		else if (key == GlobalConfig::ACTION_moveLEFT) !rotating_ ? xAxis_.push_front(LEFT) : rot_yAxis_.push_front(LEFT);
		else if (key == GlobalConfig::ACTION_moveBACK) !rotating_ ? zAxis_.push_front(BACK) : rot_xAxis_.push_front(BACK);
		else if (key == GlobalConfig::ACTION_moveFORE) !rotating_ ? zAxis_.push_front(FORE) : rot_xAxis_.push_front(FORE);
		else if (key == GlobalConfig::ACTION_moveUP) yAxis_.push_front(UP);
		else if (key == GlobalConfig::ACTION_moveDOWN) yAxis_.push_front(DOWN);
		//rotation
		else if (key == GlobalConfig::ACTION_rotENABLE && !disable_rotation_) rotating_ = (rotate_toggleMode_ ? !rotating_ : true);
		else if (key == GlobalConfig::ACTION_rotRIGHT && rotating_) rot_zAxis_.push_front(RIGHT);
		else if (key == GlobalConfig::ACTION_rotLEFT&& rotating_) rot_zAxis_.push_front(LEFT);
		//modifiers
		else if (key == GlobalConfig::ACTION_SPRINTtransform) sprinting_ = (sprint_toggleMode_ ? !sprinting_ : true);
		else if (key == GlobalConfig::ACTION_RESETtransform) {
			!rotating_ ? target_->setLocalPos(initialTrans_.postion) : target_->setLocalRot(initialTrans_.rotation);
		}
		else handled = false;
	}
	else if (e.type == SDL_KEYUP) {
		const char key = e.key.keysym.sym;

		//movement
		if (key == GlobalConfig::ACTION_moveRIGHT) !rotating_ ? xAxis_.remove(RIGHT) : rot_yAxis_.remove(RIGHT);
		else if (key == GlobalConfig::ACTION_moveLEFT) !rotating_ ? xAxis_.remove(LEFT) : rot_yAxis_.remove(LEFT);
		else if (key == GlobalConfig::ACTION_moveBACK) !rotating_ ? zAxis_.remove(BACK) : rot_xAxis_.remove(BACK);
		else if (key == GlobalConfig::ACTION_moveFORE) !rotating_ ? zAxis_.remove(FORE) : rot_xAxis_.remove(FORE);
		else if (key == GlobalConfig::ACTION_moveUP) yAxis_.remove(UP);
		else if (key == GlobalConfig::ACTION_moveDOWN) yAxis_.remove(DOWN);
		//rotation
		else if (key == GlobalConfig::ACTION_rotENABLE && !disable_rotation_) rotating_ = (rotate_toggleMode_ ? rotating_ : false);
		else if (key == GlobalConfig::ACTION_rotRIGHT && rotating_) rot_zAxis_.remove(RIGHT);
		else if (key == GlobalConfig::ACTION_rotLEFT&& rotating_) rot_zAxis_.remove(LEFT);
		//modifiers
		else if (key == GlobalConfig::ACTION_SPRINTtransform) sprinting_ = (sprint_toggleMode_ ? sprinting_ : false);
		else handled = false;
	}
	else handled = false;

	//else printf("cube - ignored event type: %i\n", e.type);
	return handled;
}

void InputFreeMovement::update() {
	if (rotating_) applyFrameRotation();
	else applyFrameTranslation();
}

void InputFreeMovement::setTarget(Node * target, Node * rotationReference) {
	target_ = target;
	rotationReference_ = rotationReference;
	initialTrans_ = target_->getLocalTrans();
}

void InputFreeMovement::setRotating(bool rotating) { rotating_ = rotating; }

void InputFreeMovement::applyFrameRotation() {
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
		if (rot_yAxis_.front() == RIGHT) frame_rotation_.y = -1;
		else frame_rotation_.y = 1;
	}

	//apply rotation if non zero
	if (frame_rotation_.x != 0 || frame_rotation_.z != 0 || frame_rotation_.y != 0) {
		frame_rotation_ = glm::normalize(frame_rotation_) * rotation_speed_;
		frame_rotation_ *= (sprinting_ ? sprint_scaler_ : 1.0f) * Platform_SDL::getDeltaTimef();

		//euler angles
		target_->rotate(frame_rotation_); //TODO: only local?
	}
}

void InputFreeMovement::applyFrameTranslation() {
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
		target_->translate(rotationReference_->getLocalRot() * frame_velocity_);
	}
}