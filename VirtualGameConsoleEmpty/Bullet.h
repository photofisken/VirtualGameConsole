#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(GameObjectsVector* gameObjects, int playerX, int playerY, VGCVector direction, bool friendly, int damage);
	~Bullet();

	void initialize();
	void render();
	void tick();
	void finalize();
	void move();
	void detectHits();
	void damage(int damage);
	bool friendly;
private:
	VGCImage mImage;
	VGCVector mDirection;
	int mDamage;
};