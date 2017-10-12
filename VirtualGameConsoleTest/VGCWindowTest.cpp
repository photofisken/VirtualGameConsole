#include "VGCWindowTest.h"
#include "VGCAssert.h"
#include "VGCWindow.h"
#include <cstdlib>
#include <time.h>



using namespace std;



static double fGetTime(){
	return double(clock()) / double(CLOCKS_PER_SEC);
}



/* VGCWindowTest */

/* Public functions */
void VGCWindowTest::run(){
	const int REPEAT_COUNT = 2;
	for(int i = 0; i < REPEAT_COUNT; i++){
		const double      DISPLAY_TIME  = 2.0;
		const std::string windowTitle   = "Hello world!";
		const int         WINDOW_WIDTH  = 200;
		const int         WINDOW_HEIGHT = 200;
		VGCWindow::initializeWindow(windowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);
		VGCWindow::initializeWindow(windowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

		VGCAssert(WINDOW_WIDTH == VGCWindow::getWidth());
		VGCAssert(WINDOW_HEIGHT == VGCWindow::getHeight());
		VGCAssert(NULL != VGCWindow::getHandle());
	
		const double START_TIME = fGetTime();
		while((fGetTime() - START_TIME < DISPLAY_TIME) && VGCWindow::windowIsOpen()){
			VGCWindow::handleMessages();	
		}

		VGCWindow::finalizeWindow();
		VGCWindow::finalizeWindow();
	}
}

