#include "Invaders.h"
using namespace std;
static const int FRAMES_PER_SECOND = 85;
static const int EDGE_DELTA = 32;
static const int SPAWN_DELTA = 16;
static const double SPAWN_TIME = 1.0;
static const VGCColor backgroundColor(255, 0, 0, 0);
static const VGCColor fontColor(255, 255, 0, 0);
static const string fontName("Times New Roman");
static const int FONT_SIZE = 24;
/* Invaders */
Invaders::Invaders() :
	mSpawnTimer(VGCClock::openTimer(SPAWN_TIME)),
	mFont(VGCDisplay::openFont(fontName, FONT_SIZE)),
	mShip(new Ship(VGCVector(VGCDisplay::getWidth() / 2,
		VGCDisplay::getHeight() / 2))),
	mEntities(),
	mScore(0),
	mGameOver(false) {
	mEntities.push_back(mShip);
}
Invaders::~Invaders() {
	while (!mEntities.empty()) {
		delete mEntities.back();
		mEntities.pop_back();
	}
	VGCDisplay::closeFont(mFont);
	VGCClock::closeTimer(mSpawnTimer);
}
void Invaders::run() {
	VGCTimer timer = VGCClock::openTimer(1.0 / FRAMES_PER_SECOND);
	while (!mGameOver && VGCVirtualGameConsole::beginLoop()) {
		VGCClock::reset(timer);
		if (VGCDisplay::beginFrame()) {
			VGCDisplay::clear(backgroundColor);
			spawnInvader();
			tick();
			detectCollisions();
			detectGameOver();
			renderBackground();
			renderForeground();
			renderLife();
			renderScore();
			killDeadEntities();
			killEdgeEntities();
			VGCDisplay::endFrame();
		}
		79
			VGCVirtualGameConsole::endLoop();
		VGCKeyboard::clearBuffer();
		VGCClock::wait(timer);
	}
	VGCClock::closeTimer(timer);
}
void Invaders::spawnInvader() {
	if (VGCClock::isExpired(mSpawnTimer)) {
		...
	}
}
void Invaders::tick() {
	EntityVector entities(mEntities);
	for (EntityVector::iterator i = entities.begin(); i != entities.end();
		i++) {
		Entity *entity = *i;
		entity->tick(mEntities);
	}
}
void Invaders::detectCollisions() {
	EntityVector entities(mEntities);
	for (EntityVector::size_type i = 0; i < entities.size(); i++) {
		Entity *entity0 = entities[i];
		for (EntityVector::size_type j = i + 1; j < entities.size(); j++) {
			Entity *entity1 = entities[j];
			if (isOverlap(entity0, entity1) && entity0->getCategory() !=
				entity1->getCategory()) {
				mScore += entity0->collide(entity1, mEntities);
				mScore += entity1->collide(entity0, mEntities);
			}
		}
	}
}
...
void Invaders::renderBackground() {
	for (EntityVector::iterator i = mEntities.begin(); i != mEntities.end();
		i++) {
		Entity *entity = *i;
		entity->render(Entity::BACKGROUND);
	}
}
void Invaders::renderForeground() {
	...
}
void Invaders::renderLife() {
	ostringstream output;
	output << "Life: " << mShip->getLife();
	const string text = output.str();
	const VGCVector position(0, 0);
	const VGCAdjustment adjustment(0.0, 0.0);
	80
		VGCDisplay::renderString(mFont, text, fontColor, position, adjustment);
}
void Invaders::renderScore() {
	...
}
void Invaders::killDeadEntities() {
	EntityVector entities;
	for (EntityVector::iterator i = mEntities.begin(); i != mEntities.end();
		i++) {
		Entity *entity = *i;
		if (entity->isAlive()) {
			entities.push_back(entity);
		}
		else {
			delete entity;
		}
	}
	mEntities = entities;
}
void Invaders::killEdgeEntities() {
	...
}
bool Invaders::isOverlap(Entity *entity0, Entity *entity1) {
	const VGCVector position0 = entity0->getPosition();
	const int X0 = position0.getX();
	const int Y0 = position0.getY();
	const int R0 = entity0->getRadius();
	const VGCVector position1 = entity1->getPosition();
	const int X1 = position1.getX();
	const int Y1 = position1.getY();
	const int R1 = entity1->getRadius();
	const int DX = X0 - X1;
	const int DY = Y0 - Y1;
	return DX * DX + DY * DY < (R0 + R1) * (R0 + R1);
}