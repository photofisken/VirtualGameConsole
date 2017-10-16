#include "Bullet.h"
#include "Sputnik.h"

#include <string>

static const int SPEED = 6;
static const int DAMAGE = 5;
static const std::string textureName = "bullet.png";


Bullet::Bullet(GameObjectsVector* gameObjects, int playerX, int playerY, VGCVector direction, bool friendly)
	: GameObject(gameObjects)
{
	mPosition = VGCVector(playerX, playerY);
	mCategory = friendly ? FRIEND : ENEMY;
	mDirection = direction;
	mImage = VGCDisplay::openImage(textureName, 1, 1);
	mRadius = 2;
	mHealth = 5;
}

Bullet::~Bullet()
{
	//finalize to close picture
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
	detectHits();
}

void Bullet::detectHits()
{
	for (unsigned int i = 0; i < mGameObjects->size(); i++)
	{
		GameObject* obj = (*mGameObjects)[i];

		if (detectHit(obj))
		{
			isAlive = false;
			obj->isAlive = false;
		}
	}
}

void Bullet::move()
{
	mPosition += SPEED* mDirection;
	int x = mPosition.getX();
	int y = mPosition.getY();
	mPosition.setY(y);
	mPosition.setX(x);

	

	// Delete if offscreen
	if (y < 0)
	{
		isAlive = false;
	}
}

void Bullet::damage(int damage) {
	mHealth -= damage;

	if (mHealth <= 0) {
		isAlive = false;
	}
}

void Bullet::finalize()
{
	VGCDisplay::closeImage(mImage);
}
