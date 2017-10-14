#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Fishdroids : public GameObject {
public:
	Fishdroids(const VGCVector &position, const VGCVector &direction);
	 ~Fishdroids(); 
	 virtual bool isAlive();      
	 virtual Category getCategory();
	 virtual VGCVector getPosition();
	 virtual int getRadius();
	 virtual int getDamage();
	 virtual void tick();
	 void render();
	 void initialize();
	 void finalize();
private:
	void move();
	void fire(GameObjectVector &gameObjects);
	bool mIsAlive;
	VGCTimer mReloadTimer;
	VGCVector mPosition;
	VGCVector mDirection;
	VGCImage image;
};

