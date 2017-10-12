#pragma once

#include <string>
#include <vector>
#include "VGCVirtualGameConsole.h"
#include "Sputnik.h"
#include "Fishdroids.h"

class Fishgame {
public:
	Fishgame();
	~Fishgame();
	void run();
private:
	void update();
	void render();
	void create();
	void destroy();
	typedef std::vector<GameObject*> GameObjectVector;
	GameObjectVector mGameObject;
};
