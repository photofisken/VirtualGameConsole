#include "Fishdroids.h"


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


Fishdroids::Fishdroids()
{
}


Fishdroids::~Fishdroids()
{
}

void Fishdroids::initialize() {
	image = VGCDisplay::openImage(textureName, 1, 1);
}

void Fishdroids::update() {
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

void Fishdroids::render() {
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}



void Fishdroids::finalize() {
	VGCDisplay::closeImage(image);
}
