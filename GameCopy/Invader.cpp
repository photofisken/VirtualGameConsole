
#include "Invader.h"
using namespace std;
static const int RADIUS = 16;
static const int DAMAGE = 10;
static const int SCORE = 100;
static const int SPEED = 2;
static const double RELOAD_TIME = 0.2;
static VGCImage invaderImage;
/* Invader */
Invader::Invader(const VGCVector &position, const VGCVector &direction) :
	Entity(),
	mIsAlive(true),
	mReloadTimer(VGCClock::openTimer(RELOAD_TIME)),
	mPosition(position),
	mDirection(direction) {
}
Invader::~Invader() {
	VGCClock::closeTimer(mReloadTimer);
}
bool Invader::isAlive() {
	return mIsAlive;
}
Invader::Category Invader::getCategory() {
	return ENEMY;
}
VGCVector Invader::getPosition() {
	return mPosition;
}
76
int Invader::getRadius() {
	return RADIUS;
}
int Invader::getDamage() {
	return DAMAGE;
}
void Invader::tick(EntityVector &entities) {
	move();
	fire(entities);
}
int Invader::collide(Entity *entity, EntityVector &entities) {
	if (0 < entity->getDamage()) {
		mIsAlive = false;
		entities.push_back(new Explosion(mPosition));
		return SCORE;
	}
	else {
		return 0;
	}
}
void Invader::render(Layer layer) {
	if (layer == BACKGROUND) {
		const VGCVector frameIndex(0, 0);
		const VGCAdjustment adjustment(0.5, 0.5);
		VGCDisplay::renderImage(invaderImage, frameIndex, mPosition,
			adjustment);
	}
}
void Invader::initialize() {
	const string filename = "Invader.png";
	const int X_FRAME_COUNT = 1;
	const int Y_FRAME_COUNT = 1;
	invaderImage = VGCDisplay::openImage(filename, X_FRAME_COUNT,
		Y_FRAME_COUNT);
}
void Invader::finalize() {
	VGCDisplay::closeImage(invaderImage);
}
void Invader::move() {
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
		77
			mDirection.setX(-mDirection.getX());
	}
	mPosition.setX(x);
	mPosition.setY(y);
}
void Invader::fire(EntityVector &entities) {
	if (VGCClock::isExpired(mReloadTimer)) {
		const VGCVector direction(0, 1);
		entities.push_back(new Bullet(ENEMY, mPosition, direction));
		VGCClock::reset(mReloadTimer);
	}
}