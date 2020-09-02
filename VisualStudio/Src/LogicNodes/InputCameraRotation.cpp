#include "InputCameraRotation.h"
#include "../GlobalConfig.h" //input config

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
		//printf("cursor rel - x %i y %i\n", e.motion.x, e.motion.y);
		//printf("cursor rel - x %i y %i\n", e.motion.xrel, e.motion.yrel);
		frame_yaw_ += e.motion.xrel;
		frame_pitch_ += e.motion.yrel;
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == GlobalConfig::ACTION_captureCursor) {
		focus_ = !focus_;
		SDL_SetRelativeMouseMode(focus_ ? SDL_TRUE : SDL_FALSE);
		frame_yaw_ = frame_pitch_ = 0;
	}
	else handled = false;

	//else printf("cube - ignored event type: %i\n", e.type);
	return handled;
}

void InputCameraRotation::update() {
	if (!focus_) return;
	if (frame_yaw_ == 0 && frame_pitch_ == 0) return;

	//limit the vertical rotation (x axis)
	if (frame_pitch_ != 0) {
		total_pitch_ += sens_ * -frame_pitch_;
		if (cappedPitch_) capPitch();
		//ucapped may get over 360
		else total_pitch_ = fmod(total_pitch_, 360.0f);

		frame_pitch_ = 0;
	}

	//horizontal rotation
	if (frame_yaw_ != 0) {
		if (cappedPitch_) total_yaw_ += sens_ * -frame_yaw_;
		//with uncapped pitch maybe upside down yaw
		else if (glm::abs(total_pitch_) < 90) total_yaw_ += sens_ * -frame_yaw_;
		else total_yaw_ += sens_ * frame_yaw_;

		frame_yaw_ = 0;
		total_yaw_ = fmod(total_yaw_, 360.0f); //better to store it clean?
	}

	//reset and apply frist yaw to avoid rolling
	cam_->setLocalRot(Transformation::BASE_ROT);
	cam_->yaw(total_yaw_);
	cam_->pitch(total_pitch_);
}

void InputCameraRotation::setInputRot(glm::quat const & q) {
	//return pitch(x), yaw(y), roll(z)
	auto eulers = glm::degrees(glm::eulerAngles(q));
	//printf("camera set: %f %f %f\n", eulers.x, eulers.y, eulers.z);

	//possible undesired euler angles (non-null roll)
	if (glm::abs(eulers.z) >= 90) { //epsilon compareison?
		total_yaw_ = 180.f - eulers.y;
		total_pitch_ = 180.f + eulers.x;

		//possibly incorrect pitch sing (later capped by max pitch)
		if (cappedPitch_) {
			if (total_pitch_ > maxPitch_) {
				total_pitch_ = -360 + total_pitch_;
			}
			else if (total_pitch_ < -maxPitch_) {
				total_pitch_ = 360 + total_pitch_;
			}
		}

		//lower values
		total_yaw_ = fmod(total_yaw_, 360.0f);
		total_pitch_ = fmod(total_pitch_, 360.0f);

		//printf("end %f %f\n", total_pitch_, total_yaw_);
	}
	else {
		//printf("camera set - it was correct lol\n");
		total_yaw_ = eulers.y;
		total_pitch_ = eulers.x;
	}

	//update the rotation (maybe other logic node reads the camera before updated)
	cam_->setLocalRot(Transformation::BASE_ROT);
	cam_->yaw(total_yaw_);
	cam_->pitch(total_pitch_);
}

void InputCameraRotation::capPitch() {
	if (total_pitch_ > maxPitch_) {
		total_pitch_ = maxPitch_;
	}
	else if (total_pitch_ < -maxPitch_) {
		total_pitch_ = -maxPitch_;
	}
}
