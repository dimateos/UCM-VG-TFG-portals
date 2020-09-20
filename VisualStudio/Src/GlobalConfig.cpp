#include "GlobalConfig.h"

char* GlobalConfig::usage =
	"/// USAGE"

	"\n"
	"\nGeneral and view:"
	"\n	ESC: exit app."
	"\n	ALT : captura / free cursor."
	"\n	V : block / free rotation(and add orange frame)."
	"\n	M : switch bottom view."
	"\n	N : switch FPS between top - down view."
	"\n	Comma y + / -: edit cenital zoom."
	"\n	Period y + / -: edit button view size."

	"\n"
	"\nProperties of the portals :"
	"\n	1 to 9 y O : switch properties of the portals."
	"\n	L y + / -: edit max levels of recursion."
	"\n	K y + / -: edit skipped levels of recursion."
	"\n	J y + / -: edit the width of the portals."

	"\n"
	"\nMovements and transformations :"
	"\n	WASD + MOUSE movement : free movement in first person."
	"\n		MOUSE wheel : main camera zoom(click resets the zoom)."
	"\n	TAB : switch between controlable objects(player and portals)"
	"\n		TAB y B : switch control between player and cenital camera."
	"\n	FLECHAS : movement over global XZ plane(controlled object)."
	"\n	ESPACIO / C : movement over global Y plane(controlled object)."
	"\n	R + Q / E : enable rotation plus ROLL controlled object."
	"\n		When rotation enabled WASD applies PITCH and YAW"
	"\n	SHIFT / CONTROL : speed modificaros for movement / rotation."
	"\n	T : reset movement / rotation(controlled object) to the start of its control."
	"\n	Y : reset movement / rotation(controlled object) to the start of the scene."
	"\n	G / H : store and load full transformation of the controlled object."
	"\n		H y B at the same time : load the saved transformation onto all the objects."

	"\n"
	"\nSwitch elements of the scene and post - processing :"
	"\n	1 to 9 : switch scene elements."
	"\n	1 to 9 y P : switch post - process filter for the portals."
	"\n	1 to 9 y B : switch post - process filter for the whole portals."

	"\n"
	"\nMiscellaneous :"
	"\n	F y + / -: edit player body width."
	"\n	X / Z : switch between the main camera and the virtual ones."
	"\n	I : switch visibility of the portal and player axes."
	"\n		I y O : switch visibility of all the camera axes."
	"\n		I y F : switch visibility of the player whole body."

	"\n"
	"\n"
	"/// USAGE"
	;

SDL_Keycode GlobalConfig::ACTION_escape = SDLK_ESCAPE;
SDL_Keycode GlobalConfig::ACTION_captureCursor = SDLK_LALT;
//SDL_Keycode GlobalConfig::ACTION_blockCamera = SDLK_LALT;
SDL_Keycode GlobalConfig::ACTION_toggleMiniView = SDLK_m;
SDL_Keycode GlobalConfig::ACTION_switchMainCameras = SDLK_n;
SDL_Keycode GlobalConfig::ACTION_editTopDownZoom = SDLK_COMMA;		//+-
SDL_Keycode GlobalConfig::ACTION_editMiniViewScale = SDLK_PERIOD;	//+-

SDL_Keycode GlobalConfig::ACTION_switchPortalProblems = SDLK_o;		//hold + 1-9
SDL_Keycode GlobalConfig::ACTION_editPortalRec = SDLK_l;			//+-
SDL_Keycode GlobalConfig::ACTION_editPortalRecSteps = SDLK_k;		//+-
SDL_Keycode GlobalConfig::ACTION_editPortalWidth = SDLK_j;			//+-

SDL_Keycode GlobalConfig::ACTION_switchControl = SDLK_TAB;			//+holding b :: control topdown cam
SDL_Keycode GlobalConfig::ACTION_moveRIGHT = SDLK_d;
SDL_Keycode GlobalConfig::ACTION_moveLEFT = SDLK_a;
SDL_Keycode GlobalConfig::ACTION_moveBACK = SDLK_s;
SDL_Keycode GlobalConfig::ACTION_moveFORE = SDLK_w;
SDL_Keycode GlobalConfig::ACTION_moveGLOBALRIGHT = SDLK_RIGHT;
SDL_Keycode GlobalConfig::ACTION_moveGLOBALLEFT = SDLK_LEFT;
SDL_Keycode GlobalConfig::ACTION_moveGLOBALBACK = SDLK_DOWN;
SDL_Keycode GlobalConfig::ACTION_moveGLOBALFORE = SDLK_UP;
SDL_Keycode GlobalConfig::ACTION_moveUP = SDLK_SPACE;
SDL_Keycode GlobalConfig::ACTION_moveDOWN = SDLK_c;
SDL_Keycode GlobalConfig::ACTION_rotENABLE = SDLK_r;
SDL_Keycode GlobalConfig::ACTION_rotRIGHT = SDLK_e;
SDL_Keycode GlobalConfig::ACTION_rotLEFT = SDLK_q;
SDL_Keycode GlobalConfig::ACTION_FASTtransform = SDLK_LSHIFT;
SDL_Keycode GlobalConfig::ACTION_SLOWtransform = SDLK_LCTRL;

SDL_Keycode GlobalConfig::ACTION_RESETtransform = SDLK_t;
SDL_Keycode GlobalConfig::ACTION_HARDRESETtransform = SDLK_y;
SDL_Keycode GlobalConfig::ACTION_COOLtransform = SDLK_h;			//+holding b :: set 3 objects to cool pos
SDL_Keycode GlobalConfig::ACTION_storeCOOLtransform = SDLK_g;

SDL_Keycode GlobalConfig::ACTION_togglePortalSurfaces = SDLK_1;
SDL_Keycode GlobalConfig::ACTION_togglePortalFrames = SDLK_2;
SDL_Keycode GlobalConfig::ACTION_toggleRedCubeAxis = SDLK_3;
SDL_Keycode GlobalConfig::ACTION_toggleRedCubePortal = SDLK_4;
SDL_Keycode GlobalConfig::ACTION_togglePortalBottom = SDLK_5;
SDL_Keycode GlobalConfig::ACTION_togglePortalWall = SDLK_6;
SDL_Keycode GlobalConfig::ACTION_toggleMidWall = SDLK_7;
SDL_Keycode GlobalConfig::ACTION_toggleRenderPanel = SDLK_8;
SDL_Keycode GlobalConfig::ACTION_toggleAxis = SDLK_9;

SDL_Keycode GlobalConfig::ACTION_screenPostFilterPortal = SDLK_p;	//hold + 1-9
SDL_Keycode GlobalConfig::ACTION_screenPostFilterGlobal = SDLK_b;	//hold + 1-9
SDL_Keycode GlobalConfig::ACTION_screenPostFilterFrame = SDLK_v;

SDL_Keycode GlobalConfig::ACTION_editPlayerWidth = SDLK_f;			//+-
SDL_Keycode GlobalConfig::ACTION_cycleBlueCamPos = SDLK_x;
SDL_Keycode GlobalConfig::ACTION_cycleRedCamPos = SDLK_z;
SDL_Keycode GlobalConfig::ACTION_togglePortalCameraAxis = SDLK_i;
