#pragma once
#include "VGCVirtualGameConsole.h"

class GameObject
{
public:
	enum Category {FRIEND, ENEMY};
	enum Layer {BACKGROUND, FOREGROUND};
	typedef std::vector<GameObject*> GameObjectVector; //wat is dis
	GameObject();
	virtual ~GameObject();
	virtual bool isAlive() = 0;
	virtual Category getCategory() = 0;
	virtual VGCVector getPosition() = 0;
	virtual int getRadius() = 0;
	virtual int getDamage() = 0;
	virtual void tick(GameObjectVector &gameObjects) = 0;
	virtual int collide(GameObject *gameObject, GameObjectVector &gameObjects) = 0;
	virtual void render() = 0;

};

