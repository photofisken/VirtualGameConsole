#include "VGCVirtualGameConsole.h"
#include <string>
#include <vector>

using namespace std;

const int SPHERE_COUNT = 20;

const string applicationName = "Bounce";
const int DISPLAY_WIDTH = 500;
const int DISPLAY_HEIGHT = 500;

const string sphereFilename = "Sphere.png";
const int SPHERE_WIDTH = 64;
const int SPHERE_HEIGHT = 64;
const int MIN_X = SPHERE_WIDTH / 2;
const int MIN_Y = SPHERE_HEIGHT / 2;
const int MAX_X = DISPLAY_WIDTH - SPHERE_WIDTH / 2;
const int MAX_Y = DISPLAY_HEIGHT - SPHERE_HEIGHT / 2;

const double FRAMES_PER_SECOND = 50.0f;
const double UPDATE_TIME = 1.0 / FRAMES_PER_SECOND;


struct Sphere{
	int x;
	int y;
	int vx;
	int vy;
};

typedef vector<Sphere> SphereVector;


int getRandomDirection(){
	if(VGCRandomizer::getBool(0.5)){
		return 1;
	}
	else{
		return -1;
	}
}

SphereVector createSpheres(int sphereCount){
	SphereVector spheres;
	for(int i = 0; i < sphereCount; i++){
		Sphere sphere;
		sphere.x = VGCRandomizer::getInt(MIN_X, MAX_X);
		sphere.y = VGCRandomizer::getInt(MIN_Y, MAX_Y);
		sphere.vx = getRandomDirection();
		sphere.vy = getRandomDirection();
		spheres.push_back(sphere);
	}
	return spheres;
}

void updateSpheres(SphereVector &spheres){
	for(SphereVector::size_type i = 0; i < spheres.size(); i++){
		Sphere &sphere = spheres[i];
		sphere.x += sphere.vx;
		sphere.y += sphere.vy;
		if(sphere.x < MIN_X || MAX_X < sphere.x){
			sphere.vx = -sphere.vx;
		}
		if (sphere.y < MIN_Y || MAX_Y < sphere.y){
			sphere.vy = -sphere.vy;
		}
	}
}

void renderSpheres(SphereVector &spheres, VGCImage &sphereImage){
	for (SphereVector::size_type i = 0; i < spheres.size(); i++){
		VGCVector frameIndex = VGCVector(0, 0);
		VGCVector position = VGCVector(spheres[i].x, spheres[i].y);
		VGCAdjustment adjustment(0.5f, 0.5f);
		VGCDisplay::renderImage(sphereImage, frameIndex, position, adjustment);
	}
}

int VGCMain(const VGCStringVector &arguments){
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	VGCImage sphereImage = VGCDisplay::openImage(sphereFilename, 1, 1);
	VGCTimer timer = VGCClock::openTimer(UPDATE_TIME);
	SphereVector spheres = createSpheres(SPHERE_COUNT);
	while (VGCVirtualGameConsole::beginLoop()){
		VGCClock::reset(timer);
		updateSpheres(spheres);
		if (VGCDisplay::beginFrame()){
			VGCColor backgroundColor(255, 0, 0, 255);
			VGCDisplay::clear(backgroundColor);
			renderSpheres(spheres, sphereImage);
			VGCDisplay::endFrame();
		}
		VGCVirtualGameConsole::endLoop();
		VGCClock::wait(timer);
	}
	VGCClock::closeTimer(timer);
	VGCDisplay::closeImage(sphereImage);
	VGCVirtualGameConsole::finalize();
	return 0;
}