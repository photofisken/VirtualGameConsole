#include "Explosion.h"
#include <string>

using namespace std;

static const std::string textureName = "explosion.png";

Explosion::Explosion(GameObjectsVector* gameObjects, VGCVector position)
	: GameObject(gameObjects)
	, mPosition(position)
{
	mTimer = 30;
	initialize();
}


Explosion::~Explosion(){
	finalize();
}

void Explosion::initialize() {
	mImage = VGCDisplay::openImage(textureName, 1, 1);
}

void Explosion::tick() {
	mTimer--;
	if (mTimer <= 0)
		isAlive = false;
}

void Explosion::render() {
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(mImage, index, mPosition, adjustment);

}

void Explosion::finalize() {
	VGCDisplay::closeImage(mImage);
}

void Explosion::damage(int damage) {
}