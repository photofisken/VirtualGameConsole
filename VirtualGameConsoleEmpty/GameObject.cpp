#include "GameObject.h"




GameObject::GameObject(GameObjectsVector* gameObjects):
	mGameObjects(gameObjects)
	, isAlive(true)
{
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

int GameObject::getDamage()
{
	return mDamage;
}