#ifndef INCLUDED_ASTEROID
#define INCLUDED_ASTEROID

#include <string>
#include "VGCVirtualGameConsole.h"
#include "Entity.h"

class Asteroid : public Entity{
public:
	Asteroid();
	virtual ~Asteroid();
	virtual void update();
	virtual void render();
	static void initialize();
	static void finalize();
private:
	VGCVector mPosition;
};

#endif