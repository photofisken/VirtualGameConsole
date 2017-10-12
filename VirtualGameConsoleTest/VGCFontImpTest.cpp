#include "VGCFontImpTest.h"
#include "VGCAssert.h"
#include "VGCFontImp.h"
#include "VGCWindow.h"
#include "vgcgdiplus.h"
#include <windows.h>
#include <gdiplus.h>
#include <tchar.h>
#include <string>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <time.h>



using namespace std;
using namespace Gdiplus;



static const double DISPLAY_TIME = 5.0;

static double fGetTime(){
	return double(clock()) / double(CLOCKS_PER_SEC);
}



/* VGCFontTest */

/* Public functions */
void VGCFontImpTest::run(){
	const std::string windowTitle   = "Hello world!";
	const int         WINDOW_WIDTH  = 200;
	const int         WINDOW_HEIGHT = 200;
		
	VGCFontImp::initializeFontImp();
	VGCFontImp::initializeFontImp();
	VGCWindow::initializeWindow(windowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

	Graphics *graphics = new Graphics(VGCWindow::getHandle(), FALSE);

	VGCFontImp *font = new VGCFontImp(graphics, "Times New Roman", 24);
	font->setSize(32);
	font->setName("Times New Roman");
	VGCAssert(32 == font->getSize());
	VGCAssert("Times New Roman" == font->getName());
	VGCAssert(0 < font->getLineHeight());
	VGCAssert(0 < font->getLineWidth("Crap"));
	VGCAssert(0 == font->getLineWidth(""));

	const double START_TIME = fGetTime();
	while((fGetTime() - START_TIME < DISPLAY_TIME) && VGCWindow::windowIsOpen()){
		graphics->Clear(Color(255, 255, 255, 255));	

		font->render(
			"Hello world!",
			VGCColor(255, 255, 0, 0),
			VGCVector(0, 0),
			VGCAdjustment(0.0, 0.0));
		font->render(
			"Hello world!",
			VGCColor(128, 255, 0, 0),
			VGCVector(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
			VGCAdjustment(0.5, 0.5));
		font->render(
			"Hello world!",
			VGCColor(64, 255, 0, 0),
			VGCVector(WINDOW_WIDTH, WINDOW_HEIGHT),
			VGCAdjustment(1.0, 1.0));

		VGCWindow::handleMessages();	

		Sleep(100);
	}

	delete font;

	delete graphics;

	VGCWindow::finalizeWindow();
	VGCFontImp::finalizeFontImp();
	VGCFontImp::finalizeFontImp();
}

