#pragma once
#include "VGCVirtualGameConsole.h"
#include "Types.h"

class GameObject
{
public:
	enum Category {FRIEND, ENEMY};
	enum Layer {BACKGROUND, FOREGROUND}; //I guess I don't have this atm
	enum Type {SPUTNIK, FISHDROID, BULLET};
	typedef std::vector<GameObject*> GameObjectVector; 
	GameObject(GameObjectsVector* gameObjects);
	virtual ~GameObject();
	virtual void initialize() = 0;
	virtual Category getCategory();
	virtual VGCVector getPosition();
	virtual int getRadius();
	virtual int getHealth();
	Type getType();
	//virtual void hit(int damage);
	virtual bool detectHit(GameObject * go);
	virtual void damage(int damage) = 0;
	virtual void tick() = 0;
	virtual void render() = 0;
	virtual void finalize() = 0;
	bool isAlive;
	bool isEnemy;
	virtual int getScore();
protected:         //Middleground for public and private: everything connected to GO gets it
	GameObjectsVector* mGameObjects;
	VGCVector mPosition;
	Category mCategory;
	Layer mLayer;
	Type mType;
	int mRadius;
	int mHealth;
};

