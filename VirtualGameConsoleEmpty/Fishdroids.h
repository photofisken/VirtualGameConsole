#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Fishdroids : public GameObject {
public:
	Fishdroids();
	 ~Fishdroids();
	void update();
	void render();
	void initialize();
	void finalize();
private:
	VGCVector mPosition;
	VGCImage image;
};

