#ifndef INCLUDED_SPACESHIP
#define INCLUDED_SPACESHIP

#include "Entity.h"
#include "VGCVirtualGameConsole.h"

class Spaceship : public Entity{
public:
	Spaceship();
	virtual ~Spaceship();
	virtual void update();
	virtual void render();
	static void initialize();
	static void finalize();
private:
	VGCVector mPosition;
};

#endif