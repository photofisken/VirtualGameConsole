#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

class Entity{
public:
	Entity();
	virtual ~Entity();
	virtual void update() = 0;
	virtual void render() = 0;
};

#endif