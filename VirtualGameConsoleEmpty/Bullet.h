#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(GameObjectsVector* gameObjects, int playerX, int playerY);
	~Bullet();

	void initialize() override;

	void render() override;
	void tick() override;

	void finalize() override;

	void move();
private:
	VGCImage mImage;
};