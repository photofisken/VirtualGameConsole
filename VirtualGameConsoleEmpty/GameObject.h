#pragma once
#include "VGCVirtualGameConsole.h"
#include "Types.h"

class GameObject
{
public:
	enum Category {FRIEND, ENEMY};
	enum Layer {BACKGROUND, FOREGROUND}; //I guess I don't have this atm
	typedef std::vector<GameObject*> GameObjectVector; 
	GameObject(GameObjectsVector* gameObjects);
	virtual ~GameObject();
	virtual void initialize() = 0;
	virtual Category getCategory();
	virtual VGCVector getPosition();
	virtual int getRadius();
	virtual int getDamage();
	virtual void tick() = 0;
	virtual void render() = 0;
	virtual void finalize() = 0;
	bool isAlive;
protected:         //Middleground for public and private: everything connected to GO gets it
	GameObjectsVector* mGameObjects;
	VGCVector mPosition;
	Category mCategory;
	Layer mLayer;
	int mRadius;
	int mDamage;
};

