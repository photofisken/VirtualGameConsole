#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Explosion : public GameObject
{
public:
	Explosion(GameObjectsVector* gameObjects, VGCVector position);
	~Explosion();
	void initialize();
	void damage(int damage);
	void tick();
	void render();
	void finalize();
private:
	VGCVector mPosition;
	VGCImage mImage;
	int mTimer;
};

