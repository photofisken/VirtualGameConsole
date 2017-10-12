#include "VGCVirtualGameConsole.h"
#include <string>
#include <vector>

using namespace std;



struct Ghost{
	double xPosition;
	double yPosition;
	double xVelocity;
	double yVelocity;
	double eyePosition;
	double eyeVelocity;
	int    color;
};

typedef std::vector<Ghost> GhostVector; 




int VGCMain(const VGCStringVector &parameters){

	const string applicationName = "Ghosts";
	const int    DISPLAY_WIDTH   = 512;
	const int    DISPLAY_HEIGHT  = 512;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	const string dropsFilename       = "drops.jpg";
	const int    DROPS_X_FRAME_COUNT = 1;
	const int    DROPS_Y_FRAME_COUNT = 1;
	VGCImage     drops               = VGCDisplay::openImage(
		dropsFilename, 
		DROPS_X_FRAME_COUNT, 
		DROPS_Y_FRAME_COUNT
	);

	const string ghostsFilename        = "ghosts.tif";
	const int    GHOSTS_X_FRAME_COUNT  = 4;
	const int    GHOSTS_Y_FRAME_COUNT  = 3;
	VGCImage ghosts                    = VGCDisplay::openImage(
		ghostsFilename, 
		GHOSTS_X_FRAME_COUNT, 
		GHOSTS_Y_FRAME_COUNT
	);

	const int    GHOST_COUNT   = 10;
	const int    GHOST_WIDTH   = VGCDisplay::getWidth(ghosts);
	const int    GHOST_HEIGHT  = VGCDisplay::getHeight(ghosts);
	const double MAX_GHOST_SPEED     = 1.0;
	const double MAX_GHOST_EYE_SPEED = 0.05;
	GhostVector  ghostVector;
	for(int ghostIndex = 0; ghostIndex < GHOST_COUNT; ghostIndex++){
		Ghost ghost;
		ghost.xPosition   = VGCRandomizer::getDouble(0.0, DISPLAY_WIDTH - GHOST_WIDTH);
		ghost.yPosition   = VGCRandomizer::getDouble(0.0, DISPLAY_HEIGHT - GHOST_HEIGHT);
		ghost.xVelocity   = VGCRandomizer::getDouble(-MAX_GHOST_SPEED, MAX_GHOST_SPEED);
		ghost.yVelocity   = VGCRandomizer::getDouble(-MAX_GHOST_SPEED, MAX_GHOST_SPEED);
		ghost.eyePosition = VGCRandomizer::getDouble(0.0, GHOSTS_X_FRAME_COUNT);
		ghost.eyeVelocity = VGCRandomizer::getDouble(-MAX_GHOST_EYE_SPEED, MAX_GHOST_EYE_SPEED);
		ghost.color       = VGCRandomizer::getInt(0, GHOSTS_Y_FRAME_COUNT - 1);
		ghostVector.push_back(ghost);
	}

	while(VGCVirtualGameConsole::beginLoop()){

		/* Update ghosts */
		for(int ghostIndex = 0; ghostIndex < GHOST_COUNT; ghostIndex++){
			Ghost &ghost = ghostVector[ghostIndex];
			ghost.xPosition   += ghost.xVelocity;
			ghost.yPosition   += ghost.yVelocity;
			ghost.eyePosition += ghost.eyeVelocity;
			if((ghost.xPosition < 0.0) || ((DISPLAY_WIDTH - GHOST_WIDTH) <= ghost.xPosition)){
				ghost.xVelocity = -ghost.xVelocity;
			}
			if((ghost.yPosition < 0.0) || ((DISPLAY_HEIGHT - GHOST_HEIGHT) <= ghost.yPosition)){
				ghost.yVelocity = -ghost.yVelocity;
			}
			if(ghost.eyePosition < 0.0){
				ghost.eyePosition += GHOSTS_X_FRAME_COUNT;
			}
			if(GHOSTS_X_FRAME_COUNT <= ghost.eyePosition){
				ghost.eyePosition -= GHOSTS_X_FRAME_COUNT;
			}
		}

		if(VGCDisplay::beginFrame()){
			
			/* Render drop image */
			const VGCVector     frameIndex = VGCVector(0, 0);
			const VGCVector     position   = VGCVector(0, 0);
			const VGCAdjustment adjustment = VGCAdjustment(0.0, 0.0);
			VGCDisplay::renderImage(drops, frameIndex, position, adjustment);

			/* Render ghosts */
			for(int ghostIndex = 0; ghostIndex < GHOST_COUNT; ghostIndex++){
				const Ghost         &ghost     = ghostVector[ghostIndex];
				const VGCVector     position   = VGCVector(int(ghost.xPosition), int(ghost.yPosition));
				const VGCVector     frameIndex = VGCVector(int(ghost.eyePosition), ghost.color);
				const VGCAdjustment adjustment = VGCAdjustment(0.0, 0.0);
				VGCDisplay::renderImage(ghosts, frameIndex, position, adjustment);
			}

			VGCDisplay::endFrame();
		}

		VGCVirtualGameConsole::endLoop();
	}

	VGCDisplay::closeImage(ghosts);

	VGCDisplay::closeImage(drops);

	VGCVirtualGameConsole::finalize();

	return 0;
}
