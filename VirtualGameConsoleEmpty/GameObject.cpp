#include "GameObject.h"


GameObject::GameObject(GameObjectsVector* gameObjects):
	mGameObjects(gameObjects)
	, isAlive(true)
{
	mRadius = 10;
}


GameObject::~GameObject()
{
}

GameObject::Category GameObject::getCategory()
{
	return mCategory;
}

VGCVector GameObject::getPosition()
{
	return mPosition;
}

int GameObject::getRadius()
{
	return mRadius;
}

int GameObject::getHealth()
{
	return mHealth;
}

GameObject::Type GameObject::getType() {
	return mType;
}

bool GameObject::detectHit(GameObject *go)
{
	if (go->getCategory() != mCategory)
	{
		VGCVector isHit = go->getPosition() - this->getPosition();

		//formula for collision
		const int a = isHit.getX();
		const int b = isHit.getY();
		const int lengthSquared = a * a + b * b;

		const int or = go->getRadius();
		const int r = getRadius();

		return (lengthSquared < (r + or) * (r + or));
	}

	return false;
}