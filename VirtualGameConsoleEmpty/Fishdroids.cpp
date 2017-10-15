#include "Fishdroids.h"
using namespace std;

static const int DAMAGE = 5;
static const int RADIUS = 10;
static const int SCORE = 100;
static const double RELOAD_TIME = 0.7;
static const int SPEED = 5;
static const int HEIGHT = 40;
static const int WIDTH = 40;
static const std::string textureName = "fishdroids.png";
static VGCImage image;

static VGCVector getRandomPosition() {
	const int MIN_X = VGCDisplay::getWidth() + WIDTH / 2;
	const int MAX_X = 2 * VGCDisplay::getWidth() - WIDTH / 2;
	const int MIN_Y = HEIGHT / 2;
	const int MAX_Y = VGCDisplay::getHeight() - HEIGHT / 2;
	const int X = VGCRandomizer::getInt(MIN_X, MAX_X);
	const int Y = VGCRandomizer::getInt(MIN_Y, MAX_Y);
	const VGCVector position(X, Y);
	return position;
}


Fishdroids::Fishdroids(GameObjectsVector* gameObjects, const VGCVector &position, const VGCVector &direction) :
	GameObject(gameObjects),
	mReloadTimer(VGCClock::openTimer(RELOAD_TIME)),
	mPosition(position),
	mDirection(direction)
{
}


Fishdroids::~Fishdroids()
{
}

void Fishdroids::initialize() {
	image = VGCDisplay::openImage(textureName, 1, 1);
}
void Fishdroids::tick() {
	const int MIN_X = -WIDTH / 2;
	int x = mPosition.getX();
	x -= SPEED;
	if (x < MIN_X) {
		mPosition = getRandomPosition();
	}
	else {
		mPosition.setX(x);
	}
}
//collide
/*
int Fishdroids::collide(GameObject *gameObject, GameObjectVector &gameObjects) {
if (0 < gameObject->getDamage()) {
mIsAlive = false;
//entities.push_back(new Explosion(mPosition));
return SCORE;
}
else {
return 0;
}
}
*/
void Fishdroids::render() {
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}



void Fishdroids::finalize() {
	VGCDisplay::closeImage(image);
}