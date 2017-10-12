#include "VGCVirtualGameConsoleTest.h"
#include "VGCAssert.h"
#include "VGCVirtualGameConsole.h"
#include <string>
#include <cstdlib>
#include <time.h>



using namespace std;



/* File scope functions */
static double fGetTime(){
	return double(clock()) / double(CLOCKS_PER_SEC);
}


/* VGCTest */

/* Public functions */
void VGCVirtualGameConsoleTest::run(){
	const int REPEAT_COUNT = 2;
	for(int i = 0; i < REPEAT_COUNT; i++){
		const double      DISPLAY_TIME  = 2.0;
		const std::string windowTitle   = "Hello world!";
		const int         WINDOW_WIDTH  = 200;
		const int         WINDOW_HEIGHT = 200;
	
		const double START_TIME = fGetTime();
	
		VGCVirtualGameConsole::initialize(windowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);
		VGCVirtualGameConsole::initialize(windowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

		while(((fGetTime() - START_TIME < DISPLAY_TIME)) && VGCVirtualGameConsole::beginLoop() && VGCVirtualGameConsole::beginLoop()){
			VGCVirtualGameConsole::endLoop();
			VGCVirtualGameConsole::endLoop();
		}

		VGCVirtualGameConsole::finalize();
		VGCVirtualGameConsole::finalize();
	}
}

