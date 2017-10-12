#include "Sputnik.h"
#include <string>

static const int speed = 2;
static const int height = 40;
static const int width = 40;
VGCImage image;
static const std::string textureName = "sputnik.png";

Sputnik::Sputnik() :
  mPosition(VGCDisplay::getWidth() / 2, VGCDisplay::getHeight() / 1.1) {
}


Sputnik::~Sputnik()
{
}

void Sputnik::initialize() {
	image = VGCDisplay::openImage(textureName, 1, 1);
}

void Sputnik::render() {
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}

void Sputnik::update() {
	const int MIN_X = width / 2;
	const int MAX_X = VGCDisplay::getWidth() - width / 2;
	const int MAX_Y = VGCDisplay::getHeight() - height / 2;
	int x = mPosition.getX();
	if (VGCKeyboard::isPressed(VGCKey::D_KEY)) {
		x += speed;
		//Can't breach the screennnn :o
		if (MAX_X < x) {
			x = MAX_X;
		}
	}
	else if (VGCKeyboard::isPressed(VGCKey::A_KEY)) {
		x -= speed < MIN_X;
		if (MIN_X > x) {       //this line might actually be wrong
			x = MIN_X;
		}
	}
	mPosition.setX(x);
}

void Sputnik::finalize() {
	VGCDisplay::closeImage(image);
}