#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Sputnik : public GameObject
{
public:
	Sputnik(GameObjectsVector* gameObjects);
	~Sputnik();
	 void initialize() override;   
	 void tick() override;     
	 void render() override;   
	 void finalize() override;
	 //void detectHits();
	 void damage(int damage);
	 void move();
	 void shoot();
	 VGCVector getPosition();
private: 
	VGCVector mPosition;
	VGCTimer mReload;

};

