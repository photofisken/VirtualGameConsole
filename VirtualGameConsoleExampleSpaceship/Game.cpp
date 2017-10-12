#include "Game.h"

using namespace std;

static const string name = "Spaceship";
static const int WIDTH = 640;
static const int HEIGHT = 480;
static const int ASTEROID_COUND = 10;
static const double FRAMES_PER_SECOND = 50;
static const double UPDATE_TIME = 1.0 / FRAMES_PER_SECOND;

Game::Game() :
	mEntities(){
	VGCVirtualGameConsole::initialize(name, WIDTH, HEIGHT);
	Spaceship::initialize();
	Asteroid::initialize();
}


Game::~Game(){
	Asteroid::finalize();
	Spaceship::finalize();
	VGCVirtualGameConsole::finalize();
}

void Game::run(){
	create();
	VGCTimer timer = VGCClock::openTimer(UPDATE_TIME);
	while(VGCVirtualGameConsole::beginLoop()){
		VGCClock::reset(timer);
		update();
		if(VGCDisplay::beginFrame()){
			VGCColor backgroundColor(255, 0, 0, 255);
			VGCDisplay::clear(backgroundColor);
			render();
			VGCDisplay::endFrame();
		}
		VGCVirtualGameConsole::endLoop();
		VGCClock::wait(timer);
	}
	VGCClock::closeTimer(timer);
	destroy();
}

void Game::update(){
	for(EntityVector::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->update();
	}
}

void Game::render(){
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++){
		mEntities[i]->render();
	}
}

void Game::create(){
	mEntities.push_back(new Spaceship());
	for(int i = 0; i < ASTEROID_COUND; i++){
		mEntities.push_back(new Asteroid());
	}
}

void Game::destroy(){
	while(!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}
}