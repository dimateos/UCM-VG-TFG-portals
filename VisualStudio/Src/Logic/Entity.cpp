#include "Entity.h"
#include "Renderable.h"

Entity::Entity() {}
Entity::~Entity() {
	for each (auto r in _renderables) delete r;
	_renderables.clear();
}

bool Entity::handleEvent(const SDL_Event & event) {
	return false;
}

void Entity::update(float delta) {
}

void Entity::render(float delta) {
	for (auto r : _renderables) r->draw(delta, trans.getModelMatrix());
}
