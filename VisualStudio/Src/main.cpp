/// TFG_dimateos
// Diego Mateos Arlanzon

#include "App.h"
App app;

int main(int argc, char* argv[]) {
	bool success = false;

	success = app.init();
	if (!success) return -1;
	success = app.start();
	if (!success) return -1;

	return 0;
}