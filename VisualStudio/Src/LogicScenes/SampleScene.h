#pragma once

#include "../Logic/Scene.h"

class SampleScene : public Scene
{
public:
	SampleScene();
	virtual ~SampleScene();

	virtual bool init();

	virtual void update(float delta);
	virtual void render();
};