#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Sputnik : public GameObject
{
public:
	Sputnik();
	~Sputnik();
	 void initialize();
	 bool isAlive();
	 Category getCategory();
	 VGCVector getPosition();
	 int getRadius();
	 int getDamage();
	 void tick(GameObjectVector &gameObjects);
	 int collide(GameObject *e, GameObjectVector &gameObjects);
	 void render() override;
	 void finalize();

private: 
	VGCVector mPosition;
	bool mIsAlive;
};

