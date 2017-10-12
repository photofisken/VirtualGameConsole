#include "VGCDisplayTest.h"
#include "VGCAssert.h"
#include "VGCDisplay.h"
#include "VGCWindow.h"
#include <cstdlib>
#include <time.h>



using namespace std;



/* File scope data */
static const double DISPLAY_TIME = 2.0;

/* File scope functions */
static double fGetTime(){
	return double(clock()) / double(CLOCKS_PER_SEC);
}

void testVGCImage(){
	VGCImage i0;
	VGCImage i1(i0);
	VGCImage i2;
	i2 = i0;
	VGCAssert(i0 == i1);
	VGCAssert(i1 == i2);
	VGCAssert(!(i0 != i1));
	VGCAssert(!(i1 != i2));
}

void testVGCFont(){
	VGCFont f0;
	VGCFont f1(f0);
	VGCFont f2;
	f2 = f0;
	VGCAssert(f0 == f1);
	VGCAssert(f1 == f2);
	VGCAssert(!(f0 != f1));
	VGCAssert(!(f1 != f2));
}

void fClearDisplay(int displayWidth, int displayHeight){
	const VGCColor color = VGCColor(255, 0, 0, 0);
	VGCDisplay::clear(color);
}

void fRenderRectangles(int displayWidth, int displayHeight){
	const VGCRectangle  rectangle   = VGCRectangle(
		VGCVector(displayWidth / 2, displayHeight / 2), 
		displayWidth / 2, 
		displayHeight /2);
	const VGCColor      fillColor   = VGCColor(255, 255, 255, 255);
	const VGCColor      borderColor = VGCColor(255, 255, 0, 0);
	const VGCAdjustment adjustment  = VGCAdjustment(0.5, 0.5);
	VGCDisplay::renderRectangle(rectangle, fillColor, adjustment, true);
	VGCDisplay::renderRectangle(rectangle, borderColor, adjustment, false);
	
	VGCDisplay::renderRectangle(
		VGCRectangle(VGCVector(0, 0), 10, 10),
		VGCColor(255, 255, 255, 255),
		VGCAdjustment(0.0, 0.0),
		true
	);
	VGCDisplay::renderRectangle(
		VGCRectangle(VGCVector(displayWidth - 1, 0), 10, 10),
		VGCColor(255, 255, 255, 255),
		VGCAdjustment(1.0, 0.0),
		false
	);
	VGCDisplay::renderRectangle(
		VGCRectangle(VGCVector(displayWidth - 1, displayHeight - 1), 10, 10),
		VGCColor(255, 255, 255, 255),
		VGCAdjustment(1.0, 1.0),
		true
	);
	VGCDisplay::renderRectangle(
		VGCRectangle(VGCVector(0, displayHeight - 1), 10, 10),
		VGCColor(255, 255, 255, 255),
		VGCAdjustment(0.0, 1.0),
		false
	);
}	

void fRenderEllipses(int displayWidth, int displayHeight){
	const VGCRectangle  rectangle   = VGCRectangle(
		VGCVector(displayWidth / 2, displayHeight / 2), 
		displayWidth / 2, 
		displayHeight /2);
	const VGCColor      fillColor   = VGCColor(255, 000, 0, 255);
	const VGCColor      borderColor = VGCColor(255, 255, 0, 0);
	const VGCAdjustment adjustment  = VGCAdjustment(0.5, 0.5);
	VGCDisplay::renderEllipse(rectangle, fillColor, adjustment, true);
	VGCDisplay::renderEllipse(rectangle, borderColor, adjustment, false);

	VGCDisplay::renderEllipse(
		VGCRectangle(VGCVector(0, 0), displayWidth, displayHeight),
		VGCColor(255, 255, 255, 255),
		VGCAdjustment(0.0, 0.0),
		false
	);
}

void fRenderLines(int displayWidth, int displayHeight){
	VGCColor color = VGCColor(255, 255, 0, 0);
	VGCDisplay::renderLine(color, VGCVector(0, 0), VGCVector(displayWidth, displayHeight));
	VGCDisplay::renderLine(color, VGCVector(0, displayHeight), VGCVector(displayWidth, 0));
}

void fRenderStrings(const VGCFont &font, int displayWidth, int displayHeight){
	const std::string   string     = std::string("HELLO");
	const VGCColor      color      = VGCColor(255, 0, 255, 0);
	const VGCVector     position   = VGCVector(displayWidth / 2, displayHeight / 2);
	const VGCAdjustment adjustment = VGCAdjustment(0.5, 0.5);
	VGCDisplay::renderString(font, string, color, position, adjustment);
}

void fRenderImages(const VGCImage &image, int displayWidth, int displayHeight){
	const VGCColor      color      = VGCColor(255, 0, 255, 0);
	const VGCVector     index      = VGCVector(0, 0);
	const VGCVector     position   = VGCVector(displayWidth / 2, displayHeight / 2);
	const VGCAdjustment adjustment = VGCAdjustment(0.5, 0.5);
	VGCDisplay::renderImage(image, index, position, adjustment);
}

void fRenderPoints(int displayWidth, int displayHeight){
	const int       POINT_COUNT = 100;
	for(int i = 0; i < POINT_COUNT; i++){
		const int X1 = (rand() % displayWidth);
		const int Y1 = (rand() % displayHeight);
		const int X2 = (rand() % displayWidth);
		const int Y2 = (rand() % displayHeight);
		const int X3 = (rand() % displayWidth);
		const int Y3 = (rand() % displayHeight);
		const int X4 = (rand() % displayWidth);
		const int Y4 = (rand() % displayHeight);
		VGCDisplay::renderPoint(VGCColor(200, 255, 255, 255), VGCVector(X1, Y1));
		VGCDisplay::renderPoint(VGCColor(200, 255, 0, 0), VGCVector(X2, Y2));
		VGCDisplay::renderPoint(VGCColor(200, 0, 255, 0), VGCVector(X3, Y3));
		VGCDisplay::renderPoint(VGCColor(200, 0, 0, 255), VGCVector(X4, Y4));
	}
}

void testVGCDisplay(){
	const std::string windowTitle   = "Hello world!";
	const int         DISPLAY_WIDTH  = 320;
	const int         DISPLAY_HEIGHT = 200;
		
	VGCDisplay::initializeDisplay("Hello world!", DISPLAY_WIDTH, DISPLAY_HEIGHT);
	VGCDisplay::initializeDisplay("Hello world!", DISPLAY_WIDTH, DISPLAY_HEIGHT);

	VGCFont font = VGCDisplay::openFont("Times New Roman", 32);

	VGCImage image = VGCDisplay::openImage("image.tif", 1, 1);
	VGCAssert(64 == VGCDisplay::getWidth(image));
	VGCAssert(64 == VGCDisplay::getHeight(image));

	const double START_TIME = fGetTime();
	while((fGetTime() - START_TIME < DISPLAY_TIME) && VGCWindow::windowIsOpen()){
		if(VGCDisplay::beginFrame() && VGCDisplay::beginFrame()){

			fClearDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);
			fRenderRectangles(DISPLAY_WIDTH, DISPLAY_HEIGHT);
			fRenderEllipses(DISPLAY_WIDTH, DISPLAY_HEIGHT);
			fRenderLines(DISPLAY_WIDTH, DISPLAY_HEIGHT);
			fRenderStrings(font, DISPLAY_WIDTH, DISPLAY_HEIGHT);
			fRenderImages(image, DISPLAY_WIDTH, DISPLAY_HEIGHT);
			fRenderPoints(DISPLAY_WIDTH, DISPLAY_HEIGHT);

			VGCDisplay::endFrame();
			VGCDisplay::endFrame();
		}

		VGCWindow::handleMessages();	
		Sleep(100);
	}

	VGCDisplay::closeImage(image);

	VGCDisplay::closeFont(font);

	VGCDisplay::finalizeDisplay();
	VGCDisplay::finalizeDisplay();

	VGCDisplay::initializeDisplay("Hello world!", DISPLAY_WIDTH, DISPLAY_HEIGHT);
	VGCDisplay::finalizeDisplay();
}



/* VGCDisplayTest */
	
/* Public functions */
void VGCDisplayTest::run(){
	testVGCImage();
	testVGCFont();
	testVGCDisplay();
}

