#include "VGCVirtualGameConsole.h"
#include "Invaders.h"
using namespace std;
static const string applicationName = "Invaders";
static const int DISPLAY_WIDTH = 512;
static const int DISPLAY_HEIGHT = 512;
int VGCMain(const VGCStringVector &arguments) {
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH,
		DISPLAY_HEIGHT);
	Bullet::initialize();
	Explosion::initialize();
	Ship::initialize();
	81
		Invader::initialize();
	Invaders *invaders = new Invaders();
	invaders->run();
	delete invaders;
	Ship::finalize();
	Explosion::finalize();
	Bullet::finalize();
	Invader::finalize();
	VGCVirtualGameConsole::finalize();
	return 0;
}