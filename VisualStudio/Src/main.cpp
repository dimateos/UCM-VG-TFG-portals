/// TFG_dimateos
// Diego Mateos Arlanzon

// WINDOWS
#include <SDL.h>
#include <glad\glad.h>
#include <stdio.h>

//#include <iostream>
//#include <string>
//using namespace std;

int main(int argc, char* argv[]) {
	printf("TFG - start app\n");
	bool initFailure = false;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow(
		"SDL + OpenGL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext mainContext = SDL_GL_CreateContext(window);

	// Only for Windows.
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	//if (initFailure) { printf("Init input failed... exit\n"); return 1; }
	printf("GL VERSION %s\n", glGetString(GL_VERSION));

	// Main loop
	printf("TFG - start loop\n");
	bool exit = false;
	SDL_Event event;

	//_deltaTimer.start();
	while (!exit) {
		// get elapsed time + wait for fps (if configured)
		//delta = _deltaTimer.getDelta();
		//#if DEBUG_FPS
		//	printf("%f fps (%f delta)\n", 1.0 / delta, delta);
		//#endif

		//update game input logic state
		//westBank.Input(input.getState());

		//update and render game
		//westBank.Update(delta);
		//westBank.Render(&renderThread);

		// Present + block if already max pending frames
		//renderThread.enqueueCommand(renderCommand);
		//while (renderThread.maxPendingFrames()) {
		//	//PlatSleeping::platSleep(Config::sleepMaxPendingFrames_seconds);
		//};

		// handle exit + poll events (ps4) or emit input events (pc)
		//exit = plat.Tick();

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				exit = true;
			}
		}

		glClearColor(1.0f, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}
	printf("TFG - end loop\n");

	// Release
	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("TFG - end app\n");
	return 0;
}