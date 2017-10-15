#include "Sputnik.h"
#include <string>
#include "Bullet.h"
using namespace std;

static const int DAMAGE = 1;
static const int RADIUS = 4;
static const int speed = 7;
static const int height = 40;
static const int width = 40;
VGCImage image;
static const std::string textureName = "sputnik.png";
Bullet* bullet;

//where the sputnik will spawn
Sputnik::Sputnik(GameObjectsVector* gameObjects)
	: GameObject(gameObjects)
	, mPosition(VGCDisplay::getWidth() / 2, VGCDisplay::getHeight() - 50)

{
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

//the stuff that will happen constantly: the sputnik will move if key is pressed
void Sputnik::tick() {
	move();
	shoot();
}

void Sputnik::finalize() {

	VGCDisplay::closeImage(image);
}

void Sputnik::move() {
	const int MIN_X = width / 2;
	const int MAX_X = VGCDisplay::getWidth() - width / 2;
	const int MAX_Y = VGCDisplay::getHeight() - height / 2;
	int x = mPosition.getX();
	if (VGCKeyboard::isPressed(VGCKey::ARROW_RIGHT_KEY)) {
		x += speed;
		//Can't breach the screennnn :o
		if (MAX_X < x) {
			x = MAX_X;
		}
	}
	else if (VGCKeyboard::isPressed(VGCKey::ARROW_LEFT_KEY)) {
		x -= speed;
		if (MIN_X > x) {
			x = MIN_X;
		}
	}
	mPosition.setX(x);
}

void Sputnik::shoot()
{
	// Spawn bullet when space is pressed
	if (VGCKeyboard::isPressed(VGCKey::SPACE_KEY))
	{
		// Create a bullet at the ship coordinates
		bullet = new Bullet(mGameObjects, mPosition.getX(), mPosition.getY());
		// Add bullet to GameObject vector
		mGameObjects->push_back(bullet);
	}
}