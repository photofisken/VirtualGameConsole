#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Fishdroids : public GameObject {
public:
	Fishdroids(GameObjectsVector* gameObjects, const VGCVector &position, const VGCVector &direction);
	 ~Fishdroids(); 
	 virtual void tick();
	 void render();
	 void initialize();
	 void finalize();
private:
	void move();
	void fire();
	VGCTimer mReload;
	VGCVector mPosition;
	VGCVector mDirection;
	VGCImage mImage;
};

