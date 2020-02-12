#include "Test.h"
#include "../Renderables/Cube.h"

Test::Test() {
	_renderables.push_back(new Cube());
}
Test::~Test() {}

bool Test::handleEvent(const SDL_Event & event) {
	return false;
}

void Test::update(float delta) {
}