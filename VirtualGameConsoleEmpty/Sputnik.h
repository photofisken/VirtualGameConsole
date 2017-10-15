#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Sputnik : public GameObject
{
public:
	Sputnik();
	~Sputnik();
	 void initialize() override;   
	 bool isAlive();
	 Category getCategory();
	 VGCVector getPosition();
	 int getRadius();
	 int getDamage();
	 void tick() override;     
	 void render() override;   
	 void finalize() override;

private: 
	VGCVector mPosition;
	bool mIsAlive;
};

