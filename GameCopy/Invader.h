#pragma once
class Invader : public Entity {
public:
	Invader(const VGCVector &position, const VGCVector &direction);
	virtual ~Invader();
	virtual bool isAlive();
	virtual Category getCategory();
	virtual VGCVector getPosition();
	75
		virtual int getRadius();
	virtual int getDamage();
	virtual void tick(EntityVector &entities);
	virtual int collide(Entity *entity, EntityVector &entities);
	virtual void render(Layer layer);
	static void initialize();
	static void finalize();
private:
	void move();
	void fire(EntityVector &entities);
	bool mIsAlive;
	VGCTimer mReloadTimer;
	VGCVector mPosition;
	VGCVector mDirection;
};
