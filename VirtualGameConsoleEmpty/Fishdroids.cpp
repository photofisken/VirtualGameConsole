#include "Fishdroids.h"
#include "Bullet.h"
using namespace std;

static const int DAMAGE = 10;
static const int RADIUS = 20;
static const int SCORE = 100;
static const double RELOAD = 1.8;
static const int SPEED = 2;
static const int HEIGHT = 40;
static const int WIDTH = 40;
static const std::string textureName = "fishdroids.png";
// Bullet* bullet;


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
	mReload(VGCClock::openTimer(RELOAD)),
	mPosition(position),
	mDirection(direction)
{
	initialize();
	mCategory = ENEMY;
	mRadius = RADIUS;
	mHealth = 3;
}


Fishdroids::~Fishdroids()
{
	finalize();
}

void Fishdroids::initialize() {
	mImage = VGCDisplay::openImage(textureName, 1, 1);
}
void Fishdroids::tick() {
	move();
	shoot();
}

void Fishdroids::move() {
	mPosition += SPEED * mDirection;
	int x = mPosition.getX();
	int y = mPosition.getY();
	const int MIN_X = RADIUS;
	const int MAX_X = VGCDisplay::getWidth() - RADIUS;
	if (x < MIN_X) {
		x = MIN_X;
		mDirection.setX(-mDirection.getX());
	}
	if (MAX_X < x) {
		x = MAX_X;
			mDirection.setX(-mDirection.getX());
	}
	mPosition.setX(x);
	mPosition.setY(y);

	}
	/*
	const int MIN_X = WIDTH / 2;
	int x = mPosition.getX();
	x -= SPEED;
	if (x < MIN_X) {
		mPosition = getRandomPosition();
	}
	else {
		mPosition.setX(x);*/


void Fishdroids::shoot() {
	if (VGCClock::isExpired(mReload)) {
		VGCVector directionEnemyBullet(0, 1);
		Bullet* bullet = new Bullet(mGameObjects, mPosition.getX(), mPosition.getY(), directionEnemyBullet, false, DAMAGE);
		mGameObjects->push_back(bullet);
		VGCClock::reset(mReload);
	}
}

void Fishdroids::damage(int damage) {
	mHealth -= damage;

	if (mHealth <= 0) {
		isAlive = false;
	}
}

//collide/hit
/*
int Fishdroids::hit() {
	if (getHealth() <= 0) {
		isAlive = false;
		//gameObjects.push_back(new Explosion(mPosition));
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
	VGCDisplay::renderImage(mImage, index, mPosition, adjustment);
}



void Fishdroids::finalize() {
	VGCClock::closeTimer(mReload);
	VGCDisplay::closeImage(mImage);
}

VGCVector Fishdroids::getPosition() {
	return mPosition;
}