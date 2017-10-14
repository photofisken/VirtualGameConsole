#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Sputnik : public GameObject
{
public:
	Sputnik();
	~Sputnik();
	static void initialize();
	virtual bool isAlive();
	virtual Category getCategory();
	virtual VGCVector getPosition();
	virtual int getRadius();
	virtual int getDamage();
	virtual void tick(GameObjectVector &gameObjects);
	virtual int collide(GameObject *e, GameObjectVector &gameObjects);
	static void render();
	static void finalize();

private: 
	VGCVector mPosition;
	bool mIsAlive;
};

