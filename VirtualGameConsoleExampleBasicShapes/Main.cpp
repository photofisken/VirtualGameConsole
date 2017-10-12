#include "VGCVirtualGameConsole.h"
#include <string>

using namespace std;

int VGCMain(const VGCStringVector &arguments){

	const string applicationName = "Basic shapes";
	const int    DISPLAY_WIDTH   = 320;
	const int    DISPLAY_HEIGHT  = 200;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	while(VGCVirtualGameConsole::beginLoop()){
	
		if(VGCDisplay::beginFrame()){
			
			VGCColor black(255, 0, 0, 0);
			VGCColor white(255, 255, 255, 255);

			VGCDisplay::clear(white);

			/*  Set lower left pixel */
			VGCDisplay::renderPoint(
				black, 
				VGCVector(0, DISPLAY_HEIGHT - 1)
			);

			/* Render a line from the upper left to the lower right corner */
			VGCDisplay::renderLine(
				black, 
				VGCVector(0, 0), 
				VGCVector(DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1)
			);

			/* Render 10 by 10 rectangle in the lower right corner */
			VGCDisplay::renderRectangle(
				VGCRectangle(VGCVector(DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1), 10, 10),
				black,
				VGCAdjustment(1.0, 1.0),
				false);

			/* Render an ellipse that spans the display area */
			VGCDisplay::renderEllipse(
				VGCRectangle(VGCVector(0, 0), 320, 200),
				black,
				VGCAdjustment(0.0, 0.0),
				false
			);

			VGCDisplay::endFrame();
		}

		VGCVirtualGameConsole::endLoop();
	}

	VGCVirtualGameConsole::finalize();

	return 0;
}