#include "InputFreeMovement.h"
#include "../GlobalConfig.h" //input config

//delta time and events
#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

InputFreeMovement::InputFreeMovement(Node * father, Node * target, Node * rotationReference, bool disable_rotation)
	: Node(father), target_(target), rotationReference_(rotationReference), disable_rotation_(disable_rotation) {
	Platform_SDL::keyEventEmitter_.registerListener(this);

	setTarget(target, rotationReference);
	hardInitialTrans_ = initialTrans_;
}

InputFreeMovement::~InputFreeMovement() {}

bool InputFreeMovement::handleEvent(SDL_Event const & e) {
	bool handled = true;

	if (e.type == SDL_KEYDOWN) {
		const SDL_Keycode key = e.key.keysym.sym;

		//movement
		if (key == GlobalConfig::ACTION_moveRIGHT) !rotating_ ? xAxis_.push_front(RIGHT) : rot_yAxis_.push_front(RIGHT);
		else if (key == GlobalConfig::ACTION_moveLEFT) !rotating_ ? xAxis_.push_front(LEFT) : rot_yAxis_.push_front(LEFT);
		else if (key == GlobalConfig::ACTION_moveBACK) !rotating_ ? zAxis_.push_front(BACK) : rot_xAxis_.push_front(BACK);
		else if (key == GlobalConfig::ACTION_moveFORE) !rotating_ ? zAxis_.push_front(FORE) : rot_xAxis_.push_front(FORE);
		else if (key == GlobalConfig::ACTION_moveUP) !CFG_independetAxisY_ ? yAxis_.push_front(UP) : yGAxis_.push_front(UP);
		else if (key == GlobalConfig::ACTION_moveDOWN) !CFG_independetAxisY_ ? yAxis_.push_front(DOWN) : yGAxis_.push_front(DOWN);
		else if (key == GlobalConfig::ACTION_moveGLOBALRIGHT) xGAxis_.push_front(RIGHT);
		else if (key == GlobalConfig::ACTION_moveGLOBALLEFT) xGAxis_.push_front(LEFT);
		else if (key == GlobalConfig::ACTION_moveGLOBALBACK) zGAxis_.push_front(BACK);
		else if (key == GlobalConfig::ACTION_moveGLOBALFORE) zGAxis_.push_front(FORE);
		//rotation
		else if (key == GlobalConfig::ACTION_rotENABLE && !disable_rotation_) rotating_ = (CFG_toggleRotation_ ? !rotating_ : true);
		else if (key == GlobalConfig::ACTION_rotRIGHT && rotating_) rot_zAxis_.push_front(RIGHT);
		else if (key == GlobalConfig::ACTION_rotLEFT&& rotating_) rot_zAxis_.push_front(LEFT);

		//modifiers
		else if (key == GlobalConfig::ACTION_FASTtransform) {
			fast_ = (CFG_toggleSpeed_ ? !fast_ : true);
			currentSpeedMultiplier_ = (fast_ ? fastSpeedMuliplier_ : 1.0f);
		}
		else if (key == GlobalConfig::ACTION_SLOWtransform) {
			slow_ = (CFG_toggleSpeed_ ? !slow_ : true);
			currentSpeedMultiplier_ = (slow_ ? slowSpeedMuliplier_ : 1.0f);
		}
		else if (key == GlobalConfig::ACTION_RESETtransform) {
			!rotating_ ? target_->setLocalPos(initialTrans_.postion) : target_->setLocalRot(initialTrans_.rotation);
		}
		else if (key == GlobalConfig::ACTION_HARDRESETtransform) {
			!rotating_ ? target_->setLocalPos(hardInitialTrans_.postion) : target_->setLocalRot(hardInitialTrans_.rotation);
		}
		else handled = false;
	}
	else if (e.type == SDL_KEYUP) {
		const SDL_Keycode key = e.key.keysym.sym;

		//movement
		if (key == GlobalConfig::ACTION_moveRIGHT) !rotating_ ? xAxis_.remove(RIGHT) : rot_yAxis_.remove(RIGHT);
		else if (key == GlobalConfig::ACTION_moveLEFT) !rotating_ ? xAxis_.remove(LEFT) : rot_yAxis_.remove(LEFT);
		else if (key == GlobalConfig::ACTION_moveBACK) !rotating_ ? zAxis_.remove(BACK) : rot_xAxis_.remove(BACK);
		else if (key == GlobalConfig::ACTION_moveFORE) !rotating_ ? zAxis_.remove(FORE) : rot_xAxis_.remove(FORE);
		else if (key == GlobalConfig::ACTION_moveUP) !CFG_independetAxisY_ ? yAxis_.remove(UP) : yGAxis_.remove(UP);
		else if (key == GlobalConfig::ACTION_moveDOWN) !CFG_independetAxisY_ ? yAxis_.remove(DOWN) : yGAxis_.remove(DOWN);
		else if (key == GlobalConfig::ACTION_moveGLOBALRIGHT) xGAxis_.remove(RIGHT);
		else if (key == GlobalConfig::ACTION_moveGLOBALLEFT) xGAxis_.remove(LEFT);
		else if (key == GlobalConfig::ACTION_moveGLOBALBACK) zGAxis_.remove(BACK);
		else if (key == GlobalConfig::ACTION_moveGLOBALFORE) zGAxis_.remove(FORE);
		//rotation
		else if (key == GlobalConfig::ACTION_rotENABLE && !disable_rotation_) rotating_ = (CFG_toggleRotation_ ? rotating_ : false);
		else if (key == GlobalConfig::ACTION_rotRIGHT && rotating_) rot_zAxis_.remove(RIGHT);
		else if (key == GlobalConfig::ACTION_rotLEFT&& rotating_) rot_zAxis_.remove(LEFT);

		//modifiers
		else if (key == GlobalConfig::ACTION_FASTtransform && !CFG_toggleSpeed_) currentSpeedMultiplier_ = 1.0f;
		else if (key == GlobalConfig::ACTION_SLOWtransform && !CFG_toggleSpeed_) currentSpeedMultiplier_ = 1.0f;
		//else if (key == GlobalConfig::ACTION_FASTtransform)
		else handled = false;
	}
	else handled = false;

	//else printf("cube - ignored event type: %i\n", e.type);
	return handled;
}

void InputFreeMovement::update() {
	frame_velocity_ = glm::vec3(0);
	frame_Gvelocity_ = glm::vec3(0);

	if (rotating_) applyFrameRotation();
	else calculateFrameTranslation();

	applyFrameGLOBALTranslation();
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
	if (glm::length2(frame_rotation_) > EPSILON * EPSILON) {
		frame_rotation_ = glm::normalize(frame_rotation_) * baseRotSpeed_;
		frame_rotation_ *= currentSpeedMultiplier_ * Platform_SDL::getDeltaTimef();

		//euler angles
		target_->rotate(frame_rotation_); //TODO: only local?
	}
}

void InputFreeMovement::calculateFrameTranslation() {
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
}

void InputFreeMovement::applyFrameGLOBALTranslation() {
	if (!xGAxis_.empty()) {
		if (xGAxis_.front() == RIGHT) frame_Gvelocity_.x = 1;
		else frame_Gvelocity_.x = -1;
	}
	if (!zGAxis_.empty()) {
		if (zGAxis_.front() == FORE) frame_Gvelocity_.z = -1;
		else frame_Gvelocity_.z = 1;
	}
	if (!yGAxis_.empty()) {
		if (yGAxis_.front() == UP) frame_Gvelocity_.y = 1;
		else frame_Gvelocity_.y = -1;
	}

	bool local = glm::length2(frame_velocity_) > EPSILON * EPSILON;
	bool global = glm::length2(frame_Gvelocity_) > EPSILON * EPSILON;

	//half the speeds in case of both movements
	float frameSpeed_ = baseSpeed_ * (local && global) ? 0.5 : 1.0;

	//local translation
	if (local) {
		frame_velocity_ = glm::normalize(frame_velocity_) * frameSpeed_;
		frame_velocity_ *= currentSpeedMultiplier_ * Platform_SDL::getDeltaTimef();
		//rotate by rotation
		target_->translate(rotationReference_->getLocalRot() * frame_velocity_);
	}

	//global translation
	if (global) {
		frame_Gvelocity_ = glm::normalize(frame_Gvelocity_) * frameSpeed_;
		frame_Gvelocity_ *= currentSpeedMultiplier_ * Platform_SDL::getDeltaTimef();
		//directly add (no orientation so global)
		target_->translate(frame_Gvelocity_);
	}
}
