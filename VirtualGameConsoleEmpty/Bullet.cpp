#include "Bullet.h"
#include "Sputnik.h"

#include <string>

static const int SPEED = 6;
static const std::string textureName = "bullet.png";

Bullet::Bullet(GameObjectsVector* gameObjects, int playerX, int playerY)
	: GameObject(gameObjects)
{
	mPosition = VGCVector(playerX, playerY);
	mImage = VGCDisplay::openImage(textureName, 1, 1);
}

Bullet::~Bullet()
{
	finalize();
}

void Bullet::initialize()
{
}

void Bullet::render()
{
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(mImage, index, mPosition, adjustment);
}

void Bullet::tick()
{
	move();
}

void Bullet::move()
{
	int y = mPosition.getY();
	y -= SPEED;
	mPosition.setY(y);

	// Delete if offscreen
	if (y < 0)
	{
		isAlive = false;
	}
}

void Bullet::finalize()
{
	VGCDisplay::closeImage(mImage);
}
