#include "ScreenPostProcessing.h"
#include "../GlobalConfig.h" //input config

#include <glad\glad.h>
#include <iostream>

#include "../Platform/Window_SDL_GL.h"
#include "../Platform/Platform_SDL.h"
#include <SDL_events.h>

ScreenPostProcessing::ScreenPostProcessing(Node * father, RenderTarget* renderTarget) : Node(father), renderTarget_(renderTarget) {
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
ScreenPostProcessing::~ScreenPostProcessing() {
	delete mesh_;
}

void ScreenPostProcessing::setOption(int n) {
	if (option_ == n) option_ = 0;
	else option_ = n;
	postFilterShader_.bind();
	postFilterShader_.setInt("option", option_);

	printf("PORTAL - set postprocessing %i\n", option_);
}

int ScreenPostProcessing::getOption() const {
	return option_;
}

Texture * ScreenPostProcessing::getTexture() {
	return &rtt_;
}

bool ScreenPostProcessing::handleEvent(SDL_Event const & e) {
	if (e.type == SDL_KEYDOWN) {
		//0-9 numbers
		if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) setOption(e.key.keysym.sym - SDLK_0);
		else return false;
	}
	else return false;

	return true;
}

void ScreenPostProcessing::render() {
	postFilterShader_.bind();
	postFilterShader_.setFloat("time", Platform_SDL::getDeltaTimeSinceStartf() * 2.0f); //animated post-processing

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

void ScreenPostProcessing::render(int frameOption) {
	postFilterShader_.bind();
	postFilterShader_.setInt("option", frameOption);

	rtt_.bind();
	mesh_->draw();

	postFilterShader_.setInt("option", option_);
}
