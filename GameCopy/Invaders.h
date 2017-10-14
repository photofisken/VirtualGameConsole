#pragma once
class Invaders {
public:
	typedef std::vector<Entity*> EntityVector;
	Invaders();
	~Invaders();
	void run();
private:
	void spawnInvader();
	void tick();
	void detectCollisions();
	void detectGameOver();
	void renderBackground();
	void renderForeground();
	void renderLife();
	void renderScore();
	void killDeadEntities();
	void killEdgeEntities();
	static bool isOverlap(Entity *entity0, Entity *entity1);
	VGCTimer mSpawnTimer;
	VGCFont mFont;
	Ship *mShip;
	EntityVector mEntities;
	int mScore;
	bool mGameOver;
	78
};
