#include "VGCVirtualGameConsole.h"
#include <string>
#include <vector>
#include "Sputnik.h"
#include "Types.h"
#include "Fishdroids.h"
#include <sstream>


using namespace std;

static Sputnik *sputnik;

int VGCMain(const VGCStringVector &arguments) {
	// Below is the window and window size
	const std::string applicationName = "Sputnik: the game";
	const int DISPLAY_WIDTH = 800;
	const int DISPLAY_HEIGHT = 557;
	static const double FRAMES_PER_SECOND = 120;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	GameObjectsVector GOVector;

	//create an object out of the Sputnik (class)
	sputnik = new Sputnik(&GOVector);
	GOVector.push_back(sputnik);
	for (unsigned int i = 0; i < GOVector.size(); i++)
	{
		GOVector[i]->initialize();
	}

	VGCTimer timer = VGCClock::openTimer(1.0 / FRAMES_PER_SECOND);

	while (VGCVirtualGameConsole::beginLoop()) {       	// Update (gameloop) (every frame)

		VGCClock::reset(timer);       //something to "clean" the clock at startup
		if (VGCDisplay::beginFrame()) {

			const VGCColor backgroundColor = VGCColor(255, 0, 0, 0); //window colour
			VGCDisplay::clear(backgroundColor);

			for (unsigned int i = 0; i < GOVector.size(); i++)
			{
				GOVector[i]->render();
			}

			VGCDisplay::endFrame();
		}

		for (unsigned int i = 0; i < GOVector.size(); i++)
		{
			if (GOVector[i]->isAlive == false) {   //if it's dead, delete the place in the vector
				delete GOVector[i];               //delete object
				GOVector.erase(GOVector.begin() + i);   //delete spot in vector
			}
			else {                        
				GOVector[i]->tick();          //if it's alive, run the "update"
			}
		}
		// TODO: if ship has less health than 0: gameover
		if (VGCRandomizer::getBool(0.01)) {      //1% chance that it happens (spawns fishdroid)
			VGCVector enemyPosition = VGCVector(VGCRandomizer::getInt(0, 800), -1);    //spawn in x and y axis
			VGCVector enemyDirection = VGCVector(VGCRandomizer::getInt(-2, 2), 1);      //direction lul
			GOVector.push_back(new Fishdroids(&GOVector, enemyPosition, enemyDirection)); //New droid?
		}  

		VGCVirtualGameConsole::endLoop();
	}
	VGCClock::closeTimer(timer);
	// Stop the program
	for (unsigned int i = 0; i < GOVector.size(); i++)
	{
		GOVector[i]->finalize();
	}

	 VGCVirtualGameConsole::finalize(); 
	
		return 0;
	                                    
	
}

void renderLife() {
	ostringstream output;
	output << "Life: " << sput->getLife();
	const string text = output.str();
	const VGCVector position(0, 0);
	const VGCAdjustment adjustment(0.0, 0.0);

	VGCDisplay::renderString(mFont, text, fontColor, position, adjustment);
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
