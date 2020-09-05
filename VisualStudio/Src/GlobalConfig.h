#pragma once
#include <SDL_keycode.h>

//static global config to easily edit hotkeys
class GlobalConfig
{
public:
	static SDL_Keycode
		ACTION_escape,					//exit application
		ACTION_captureCursor,			//switch free amd hidden cursor
		ACTION_screenPostFilterPortal,	//Switch post-processing effect (hold and press 1-9)
		ACTION_screenPostFilterGlobal,
		ACTION_screenPostFilterFrame,	//simplified shortcut
		ACTION_switchMainCameras,		//switch main cameras (fps or top-down)
		ACTION_toggleMiniView,
		ACTION_editMiniViewScale,
		ACTION_editTopDownZoom,

		ACTION_moveRIGHT,			//movement
		ACTION_moveLEFT,
		ACTION_moveBACK,
		ACTION_moveFORE,
		ACTION_moveGLOBALRIGHT,		//global movement
		ACTION_moveGLOBALLEFT,
		ACTION_moveGLOBALBACK,
		ACTION_moveGLOBALFORE,
		ACTION_moveUP,
		ACTION_moveDOWN,
		ACTION_rotENABLE,			//rotation
		ACTION_rotRIGHT,
		ACTION_rotLEFT,
		ACTION_FASTtransform,		//modifiers
		ACTION_SLOWtransform,
		ACTION_RESETtransform,
		ACTION_HARDRESETtransform,
		ACTION_COOLtransform,			//go to interesting trans
		ACTION_storeCOOLtransform,		//save interesting trans
		ACTION_editPlayerWidth,			//change width of player

		ACTION_switchControl,			//start/stop controling the portal to move/rotate it locally
		ACTION_cycleBlueCamPos,			//switch between camera positions
		ACTION_cycleRedCamPos,			//switch between camera positions
		ACTION_togglePortalCameraAxis,	//show/hide virtual xportal cameras axes

		ACTION_switchPortalRenderModes,	//switch portal rendering options
		ACTION_editPortalRec,			//change amount of recursion
		ACTION_editPortalWidth,			//change width of portal surfacesç

		ACTION_togglePortalSurfaces,	//toggle portal surfaces
		ACTION_togglePortalFrames,		//toggle portal frames
		ACTION_togglePortalCube,		//toggle cube to render as a portal
		ACTION_togglePortalWall,			//toggle wall
		ACTION_togglePortalBottom
		;

private:
	GlobalConfig() {}; //non instanciable
};