#pragma once
#include "VGCVirtualGameConsole.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void initialize() = 0;
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void finalize() = 0;
};

