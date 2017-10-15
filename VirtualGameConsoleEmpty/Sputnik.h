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
	 void move();
	 void shoot();
private: 
	VGCVector mPosition;
	VGCTimer mReload;

};

