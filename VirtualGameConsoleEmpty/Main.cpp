#include "VGCVirtualGameConsole.h"
#include <string>
#include <vector>
#include "Sputnik.h"
#include "Types.h"


int VGCMain(const VGCStringVector &arguments) {
	// Below is the window and window size
	const std::string applicationName = "Sputnik: the game";
	const int DISPLAY_WIDTH = 800;
	const int DISPLAY_HEIGHT = 557;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	GameObjectsVector GOVector;

	//create an object out of the Sputnik (class)
	GOVector.push_back(new Sputnik());
	for (unsigned int i = 0; i < GOVector.size(); i++)
	{
		GOVector[i]->initialize();
	}

	// Update (gameloop) (every frame)
	while (VGCVirtualGameConsole::beginLoop()) {

		// Draw
		if (VGCDisplay::beginFrame()) {

			const VGCColor backgroundColor = VGCColor(255, 0, 0, 0);
			VGCDisplay::clear(backgroundColor);

			for (unsigned int i = 0; i < GOVector.size(); i++)
			{
				GOVector[i]->render();
			}

			VGCDisplay::endFrame();
		}

		for (unsigned int i = 0; i < GOVector.size(); i++)
		{
			GOVector[i]->tick();
		}

		VGCVirtualGameConsole::endLoop();
	}

	// Stop the program
	for (unsigned int i = 0; i < GOVector.size(); i++)
	{
		GOVector[i]->finalize();
	}

	VGCVirtualGameConsole::finalize();

	return 0;
}

//My old hello world below
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
