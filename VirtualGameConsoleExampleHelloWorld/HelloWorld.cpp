#include "VGCVirtualGameConsole.h"
#include <string>

using namespace std;

int VGCMain(const VGCStringVector &arguments){

	const string applicationName = "Hello world";
	const int    DISPLAY_WIDTH   = 320;
	const int    DISPLAY_HEIGHT  = 200;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	const int FONT_SIZE = 48;
	VGCFont   font      = VGCDisplay::openFont("Times New Roman", FONT_SIZE);

	while(VGCVirtualGameConsole::beginLoop()){
	
		if(VGCDisplay::beginFrame()){
			
			const VGCColor backgroundColor = VGCColor(255, 255, 255, 255);
			VGCDisplay::clear(backgroundColor);
		
			const string        text           = "Hello World!";
			const VGCColor      textColor      = VGCColor(255, 255, 0, 0);
			const VGCVector     textPosition   = VGCVector(0, 0);
			const VGCAdjustment textAdjustment = VGCAdjustment(0.0, 0.0);
			VGCDisplay::renderString(
				font, 
				text, 
				textColor, 
				textPosition,
				textAdjustment);

			VGCDisplay::endFrame();
		}

		VGCVirtualGameConsole::endLoop();
	}

	VGCDisplay::closeFont(font);

	VGCVirtualGameConsole::finalize();

	return 0;
}