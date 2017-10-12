#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Sputnik : public GameObject
{
public:
	Sputnik();
	~Sputnik();
	void initialize() override;
	void render() override;
	void update() override;
	void finalize() override;
private: 
	VGCVector mPosition;
	VGCImage image;
};

