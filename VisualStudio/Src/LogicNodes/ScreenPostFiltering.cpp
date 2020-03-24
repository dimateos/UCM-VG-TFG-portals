#include "ScreenPostFiltering.h"
#include <glad\glad.h>
#include <iostream>

#include "../Platform/Window_SDL_GL.h"
#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

ScreenPostFiltering::ScreenPostFiltering(Node * father, RenderTarget* renderTarget) : Node(father), renderTarget_(renderTarget) {
	//innput
	Platform_SDL::keyEventEmitter_.registerListener(this);

	//MESH
	mesh_ = new PlaneMesh();

	//SHADER
	postFilterShader_.build("../Shaders/V_screenTexture.glsl", "../Shaders/F_screenTexture_postFiltering.glsl");
	setOption(0);

	//TEXTURE
	preview_res_ = 0.25;
	rtt_.createRenderTargetTexture(renderTarget_->getID(), renderTarget_->getVP()->getW(), renderTarget_->getVP()->getH());
}
ScreenPostFiltering::~ScreenPostFiltering() {
	delete mesh_;
}

void ScreenPostFiltering::setOption(int n) {
	option_ = n;
	postFilterShader_.bind();
	postFilterShader_.setInt("option", option_);
}

bool ScreenPostFiltering::handleEvent(SDL_Event const & e) {
	bool handled = true;

	if (e.type == SDL_KEYDOWN) {
		if (!readingInput_) {
			//If p not pressed then ignore input
			if (e.key.keysym.sym == SDLK_p) readingInput_ = true;
			else handled = false;
		}
		else {
			//0-9 numbers
			if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) setOption(e.key.keysym.sym - SDLK_0);
			else handled = false;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_p) {
		readingInput_ = false;
	}
	else handled = false;

	return handled;
}

void ScreenPostFiltering::render() {
	postFilterShader_.bind();
	postFilterShader_.setFloat("time", Platform_SDL::getDeltaTimeSinceStartf() * 2.0f);

	//glDisable(GL_DEPTH_TEST);
	rtt_.bind();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //to check the quad on top
	mesh_->draw();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//smaller window
	//postFilterShader_.setInt("option", 2);
	//glViewport(0, 0, Window_SDL_GL::getWidth() *preview_res_, Window_SDL_GL::getWidth() *preview_res_);
	//mesh_->draw();
	//glViewport(0, 0, Window_SDL_GL::getWidth(), Window_SDL_GL::getWidth());
}
