#pragma once
/* Entity */
class Entity {
public:
	enum Category {
		FRIEND,
		ENEMY
	};
	enum Layer {
		BACKGROUND,
		FOREGROUND
	};
	typedef std::vector<Entity*> EntityVector;
	Entity();
	virtual ~Entity();
	virtual bool isAlive() = 0;
	virtual Category getCategory() = 0;
	virtual VGCVector getPosition() = 0;
	virtual int getRadius() = 0;
	virtual int getDamage() = 0;
	virtual void tick(EntityVector &entities) = 0;
	virtual int collide(Entity *entity, EntityVector &entities) = 0;
	virtual void render(Layer layer) = 0;
};
