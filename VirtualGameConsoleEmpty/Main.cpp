#include "VGCVirtualGameConsole.h"
#include <string>
#include <string>
#include <vector>
#include "Sputnik.h"

// Below is the window and window size
int VGCMain(const VGCStringVector &arguments) {
	const std::string applicationName = "Sputnik: the game";
	const int DISPLAY_WIDTH = 800;
	const int DISPLAY_HEIGHT = 557;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	//create an object out of the Sputnik (class)
	Sputnik* sputnik = new Sputnik();
	sputnik->initialize();

	// Update (gameloop) (every frame)
	while (VGCVirtualGameConsole::beginLoop()) {

		// Draw
		if (VGCDisplay::beginFrame()) {

			const VGCColor backgroundColor = VGCColor(255, 0, 0, 0);
			VGCDisplay::clear(backgroundColor);

			sputnik->render();

			VGCDisplay::endFrame();
		}

		sputnik->update();

		VGCVirtualGameConsole::endLoop();
	}

	// Stop the program
	sputnik->finalize();

	VGCVirtualGameConsole::finalize();

	return 0;
}

/*
int VGCMain(const VGCStringVector &arguments){
	const string applicationName = "Hello World!!";
	const int DISPLAY_WIDTH = 370;
	const int DISPLAY_HEIGHT = 100;
	//this initializes stuff lol (makes the window)
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	//font size 
	const int FONT_SIZE = 48;
	//here's the font "open"
	VGCFont font = VGCDisplay::openFont("Times New Roman", FONT_SIZE);
	//the gameloop!
	while (VGCVirtualGameConsole::beginLoop()) {
		// inform VGC about the beginning and end of the rendering step of the game loop. 
		if (VGCDisplay::beginFrame()) {
			const VGCColor backgroundColor = VGCColor(255, 63, 61, 76);
			//please go through what below means
			VGCDisplay::clear(backgroundColor);

			const string text = "Hello World!";
			const VGCColor textColor = VGCColor(255, 76, 186, 160);
			const VGCVector textPosition = VGCVector(0, 0);
			const VGCAdjustment textAdjustment = VGCAdjustment(0.0, 0.0);
			VGCDisplay::renderString(
				font,
				text,
				textColor,
				textPosition,
				textAdjustment);

				
			VGCDisplay::endFrame();
		}

	
	if (VGCKeyboard::isPressed(VGCKey::D_KEY)) {
		double x = textPosition.getX();
		x += 1;
		textPosition.setX(x);
	}
	else if (VGCKeyboard::isPressed(VGCKey::A_KEY)) {
		double x = textPosition.getX();
		x -= 1;
		textPosition.setX(x);
	}

		VGCVirtualGameConsole::endLoop();
	}
	//close font?
	VGCDisplay::closeFont(font);
	VGCVirtualGameConsole::finalize();

	return 0;
}
*/
