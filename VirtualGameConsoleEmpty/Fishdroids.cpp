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


Fishdroids::Fishdroids(const VGCVector &position, const VGCVector &direction) :
GameObject(),
mIsAlive(true),
mReloadTimer(VGCClock::openTimer(RELOAD_TIME)),
mPosition(position),
mDirection(direction)
{
}


Fishdroids::~Fishdroids()
{
}

bool Fishdroids::isAlive() {
	return mIsAlive;
}
Fishdroids::Category Fishdroids::getCategory() {
	return ENEMY;
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

int Fishdroids::getRadius() {
	return RADIUS;
}
int Fishdroids::getDamage() {
	return DAMAGE;
}
void Fishdroids::render() {
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}



void Fishdroids::finalize() {
	VGCDisplay::closeImage(image);
}
