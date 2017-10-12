#include "Spaceship.h"
#include <string>

using namespace std;
static const int SPEED = 8;
static const int HEIGHT = 32;
static const int WIDTH = 64;
static const string filename = "Spaceship.png";
static VGCImage image;


Spaceship::Spaceship() :
	mPosition(VGCDisplay::getWidth() / 1, VGCDisplay::getHeight() / 1){
}

Spaceship::~Spaceship(){
}

void Spaceship::update(){
	const int MIN_X = WIDTH / 2;
	const int MIN_Y = HEIGHT / 2;
	const int MAX_X = VGCDisplay::getWidth() - WIDTH / 2;
	const int MAX_Y = VGCDisplay::getHeight() - HEIGHT / 2;
	int x = mPosition.getX();
	int y = mPosition.getY();
	if (VGCKeyboard::isPressed(VGCKey::D_KEY)){
		x += SPEED;
		if(MAX_X < x){
			x = MAX_X;
		}
	}
	else if (VGCKeyboard::isPressed(VGCKey::A_KEY)){
		x -= SPEED;
		if (x < MIN_X){
			x = MIN_X;
		}
	}
	if (VGCKeyboard::isPressed(VGCKey::W_KEY)){
		y -= SPEED;
		if(y < MIN_Y){
			y = MIN_Y;
		}
	}
	else if (VGCKeyboard::isPressed(VGCKey::S_KEY)){
		y += SPEED;
		if(MAX_Y < y){
			y = MAX_Y;
		}
	}
	mPosition.setX(x);
	mPosition.setY(y);
}

void Spaceship::render(){
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}

void Spaceship::initialize(){
	image = VGCDisplay::openImage(filename, 1, 1);
}

void Spaceship::finalize(){
	VGCDisplay::closeImage(image);
}