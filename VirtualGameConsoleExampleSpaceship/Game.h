#ifndef INCLUDED_GAME
#define INCLUDED_GAME

#include <string>
#include <vector>
#include "VGCVirtualGameConsole.h"
#include "Spaceship.h"
#include "Asteroid.h"

class Game{
public:
	Game();
	~Game();
	void run();
private:
	void update();
	void render();
	void create();
	void destroy();
	typedef std::vector<Entity*> EntityVector;
	EntityVector mEntities;
};

#endif