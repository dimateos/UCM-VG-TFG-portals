#include "GlobalConfig.h"

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
