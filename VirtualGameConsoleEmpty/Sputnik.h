#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Sputnik : public GameObject
{
public:
	Sputnik();
	~Sputnik();
	static void initialize();
	virtual void render();
	virtual void update();
	static void finalize();
private: 
	VGCVector mPosition;
	VGCImage image;
};

