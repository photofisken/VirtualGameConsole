#include "VGCVirtualGameConsole.h"
#include <string>
#include <sstream>

using namespace std;

int VGCMain(const VGCStringVector &parameters){

	const string applicationName = "Text input";
	const int    DISPLAY_WIDTH   = 640;
	const int    DISPLAY_HEIGHT  = 320;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	const int FONT_SIZE = 24;
	VGCFont font = VGCDisplay::openFont("Times New Roman", FONT_SIZE);

	while(!VGCKeyboard::wasPressed(VGCKey::ESCAPE_KEY) && VGCVirtualGameConsole::beginLoop()){
	
		if(VGCDisplay::beginFrame()){

			VGCDisplay::clear(VGCColor(255, 255, 255, 255));

			/* Attach cursor | to the character buffer and output it */
			ostringstream output;
			output << VGCKeyboard::getBuffer() << '|';
			const VGCColor      color      = VGCColor(255, 255, 0, 0);
			const VGCVector     position   = VGCVector(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
			const VGCAdjustment adjustment = VGCAdjustment(0.5, 0.5);
			VGCDisplay::renderString(font, output.str(), color, position, adjustment);

			VGCDisplay::endFrame();
		}

		VGCVirtualGameConsole::endLoop();
	}

	VGCDisplay::closeFont(font);

	VGCVirtualGameConsole::finalize();

	return 0;
}