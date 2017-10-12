#include "Asteroid.h"

using namespace std;

static const int SPEED = 4;
static const int HEIGHT = 64;
static const int WIDTH = 64;
static const string filename = "Asteroid.png";
static VGCImage image;

static VGCVector getRandomPosition(){
	const int MIN_X = VGCDisplay::getWidth() + WIDTH / 2;
	const int MAX_X = 2 * VGCDisplay::getWidth() - WIDTH / 2;
	const int MIN_Y = HEIGHT / 2;
	const int MAX_Y = VGCDisplay::getHeight() - HEIGHT / 2;
	const int X = VGCRandomizer::getInt(MIN_X, MAX_X);
	const int Y = VGCRandomizer::getInt(MIN_Y, MAX_Y);
	const VGCVector position(X, Y);
	return position;
}

Asteroid::Asteroid() : 
	mPosition(getRandomPosition()){
}


Asteroid::~Asteroid(){
}

void Asteroid::update(){
	const int MIN_X = -WIDTH / 2;
	int x = mPosition.getX();
	x -= SPEED;
	if(x < MIN_X){
		mPosition = getRandomPosition();
	}
	else{
		mPosition.setX(x);
	}
}

void Asteroid::render(){
	VGCVector index(0, 0);
	VGCAdjustment adjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, mPosition, adjustment);
}

void Asteroid::initialize(){
	image = VGCDisplay::openImage(filename, 1, 1);
}

void Asteroid::finalize(){
	VGCDisplay::closeImage(image);
}
