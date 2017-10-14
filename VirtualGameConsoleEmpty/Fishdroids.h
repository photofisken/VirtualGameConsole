#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Fishdroids : public GameObject {
public:
	Fishdroids(const VGCVector &position, const VGCVector &direction);
	 ~Fishdroids(); 
	 virtual void tick() = 0;    //I tried adding this
	 virtual bool isAlive();      
	 virtual Category getCategory();
	 virtual VGCVector getPosition();
	 virtual int getRadius();
	 virtual int getDamage();
	 virtual void tick(GameObject *e, GameObjectVector &gameObjects);
	 virtual int collide(GameObject *gameObject, GameObjectVector &gameObjects);
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

