#pragma once
#include "VGCVirtualGameConsole.h"
#include "Object.h"

class Sputnik : public Object
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


