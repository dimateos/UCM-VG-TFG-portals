#include "SampleScene.h"
#include "../Entities/Test.h"

SampleScene::SampleScene() {}

SampleScene::~SampleScene() {}

bool SampleScene::init() {
	_ents.push_back(new Test());
	return true;
}
