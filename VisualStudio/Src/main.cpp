/// TFG_dimateos
// Diego Mateos Arlanzon

#include "App.h"
App app;

int main(int argc, char* argv[]) {
	bool success = false;

	const float RES = 1.0f; //16.0f / 9.0f;
	const int RES_H = 720;
	const int RES_W = RES_H * RES;

	success = app.init(RES_W, RES_H);
	if (!success) return -1;
	success = app.start();
	if (!success) return -1;

	return 0;
}