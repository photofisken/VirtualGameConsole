#pragma once
#include "VGCVirtualGameConsole.h"
#include "GameObject.h"

class Fishdroids : public GameObject {
public:
	Fishdroids(GameObjectsVector* gameObjects, const VGCVector &position, const VGCVector &direction);
	 ~Fishdroids(); 
	 virtual void tick();
	 //virtual int hit();
	 void render();
	 void initialize();
	 void finalize();
	 VGCVector getPosition();
	 void damage(int damage);
	 int getScore() override;
private:
	void move();
	void shoot();
	VGCTimer mReload;
	VGCVector mPosition;
	VGCVector mDirection;
	VGCImage mImage;
};

