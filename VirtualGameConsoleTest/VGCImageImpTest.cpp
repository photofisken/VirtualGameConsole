#include "VGCImageImpTest.h"
#include "VGCAssert.h"
#include "VGCImageImp.h"
#include "VGCWindow.h"  
#include <windows.h>
#include <gdiplus.h>
#include <cstdlib>
#include <time.h>



using namespace std;
using namespace Gdiplus;



/* File scope data */
static const double DISPLAY_TIME = 2.0;



/* File scope functions */
static double fGetTime(){
	return double(clock()) / double(CLOCKS_PER_SEC);
}


static void testVGCImageImp(){
	const std::string windowTitle   = "Hello world!";
	const int         WINDOW_WIDTH  = 200;
	const int         WINDOW_HEIGHT = 200;
	VGCImageImp::initializeImageImp();
	VGCImageImp::initializeImageImp();
	VGCWindow::initializeWindow(windowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	const double START_TIME = fGetTime();
	while((fGetTime() - START_TIME < DISPLAY_TIME) && VGCWindow::windowIsOpen()){
		VGCWindow::handleMessages();	
	}

	VGCWindow::finalizeWindow();
	VGCImageImp::finalizeImageImp();
	VGCImageImp::finalizeImageImp();
}

static void testVGCSimpleImageImp(){
	const std::string windowTitle   = "Hello world!";
	const int         WINDOW_WIDTH  = 320;
	const int         WINDOW_HEIGHT = 200;
	VGCImageImp::initializeImageImp();
	VGCWindow::initializeWindow(windowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

	Graphics *graphics = new Graphics(VGCWindow::getHandle(), FALSE);

	VGCSimpleImageImp *simpleImageImp = new VGCSimpleImageImp(graphics, "simpletestimage.tif");
	VGCAssert(160 == simpleImageImp->getWidth());
	VGCAssert(100 == simpleImageImp->getHeight());
	VGCAssert(0 == simpleImageImp->getXFrameCount());
	VGCAssert(0 == simpleImageImp->getYFrameCount());
	
	const double START_TIME = fGetTime();
	while((fGetTime() - START_TIME < DISPLAY_TIME) && VGCWindow::windowIsOpen()){
		graphics->Clear(Color(255, 0, 255, 255));
		
		simpleImageImp->render(
			VGCVector(0,0),
			VGCVector((WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2)),
			VGCAdjustment(0.5, 0.5));


		VGCWindow::handleMessages();	

		Sleep(100);
	}

	delete simpleImageImp;

	delete graphics;

	VGCWindow::finalizeWindow();
	VGCImageImp::finalizeImageImp();
}

static void testVGCComplexImageImp(){
	const std::string windowTitle   = "Hello world!";
	const int         WINDOW_WIDTH  = 320;
	const int         WINDOW_HEIGHT = 200;
	VGCImageImp::initializeImageImp();
	VGCWindow::initializeWindow(windowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

	Graphics *graphics = new Graphics(VGCWindow::getHandle(), FALSE);

	VGCComplexImageImp *complexImageImp = new VGCComplexImageImp(graphics, "complextestimage.tif", 3, 2);
	VGCAssert(64 == complexImageImp->getWidth());
	VGCAssert(64 == complexImageImp->getHeight());
	VGCAssert(3 == complexImageImp->getXFrameCount());
	VGCAssert(2 == complexImageImp->getYFrameCount());
	
	const double START_TIME = fGetTime();
	while((fGetTime() - START_TIME < DISPLAY_TIME) && VGCWindow::windowIsOpen()){
		graphics->Clear(Color(255, 255, 255, 255));
		
		complexImageImp->render(
			VGCVector(0, 0),
			VGCVector(0, 0),
			VGCAdjustment(0.5, 0.5));
		complexImageImp->render(
			VGCVector(2, 0),
			VGCVector(WINDOW_WIDTH, 0),
			VGCAdjustment(0.5, 0.5));
		complexImageImp->render(
			VGCVector(0, 1),
			VGCVector(0, WINDOW_HEIGHT),
			VGCAdjustment(0.5, 0.5));
		complexImageImp->render(
			VGCVector(2, 1),
			VGCVector(WINDOW_WIDTH, WINDOW_HEIGHT),
			VGCAdjustment(0.5, 0.5));
		complexImageImp->render(
			VGCVector(1, 0),
			VGCVector(WINDOW_WIDTH / 2, WINDOW_HEIGHT /2),
			VGCAdjustment(0.5, 0.5));


		VGCWindow::handleMessages();	

		Sleep(100);
	}

	delete complexImageImp;

	delete graphics;

	VGCWindow::finalizeWindow();
	VGCImageImp::finalizeImageImp();
}



/* VGCImageImpTest */

/* Public functions */
void VGCImageImpTest::run(){
	testVGCImageImp();
	testVGCSimpleImageImp();
	testVGCComplexImageImp();
}

