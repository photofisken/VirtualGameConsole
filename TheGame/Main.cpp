//This is my from scratch game.. in case everything screws up 
#include "VGCVirtualGameConsole.h"
#include <string>
#include <vector>
#include "CatShip.h"

// Below is the window and window size
int VGCMain(const VGCStringVector &arguments) {
	const std::string applicationName = "Sputnik: the game";
	const int DISPLAY_WIDTH = 800;
	const int DISPLAY_HEIGHT = 557;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);