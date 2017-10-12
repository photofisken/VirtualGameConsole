#include "VGCVirtualGameConsole.h"
#include <string>
#include <sstream>
#include <cmath>



using namespace std;



int VGCMain(const VGCStringVector &arguments){
	const string applicationName = "Blobs";
	const int    DISPLAY_WIDTH   = 512;
	const int    DISPLAY_HEIGHT  = 512;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	const double FRAMES_PER_SECOND = 40;
	const double FRAME_TIMEOUT     = (1.0 / FRAMES_PER_SECOND);
	VGCTimer     frameTimer        = VGCClock::openTimer(FRAME_TIMEOUT);

	const string fontName  = "Times New Roman";
	const int    FONT_SIZE = 42;
	VGCFont      font      = VGCDisplay::openFont(fontName, FONT_SIZE);

	VGCImage background = VGCDisplay::openImage("drops.jpg", 1, 1);

	const int BLOB_X_FRAME_COUNT = 4;
	const int BLOB_Y_FRAME_COUNT = 4;
	VGCImage  blobImage          = VGCDisplay::openImage("blobs.tif", BLOB_X_FRAME_COUNT, BLOB_Y_FRAME_COUNT);
	const int BLOB_WIDTH         = VGCDisplay::getWidth(blobImage);
	const int BLOB_HEIGHT        = VGCDisplay::getHeight(blobImage);

	const int    BLOB_COUNT = 200;
	const double PI         = 3.1415926535897932384626433832795;
	const double MIN_SPEED  = 0.01;
	const double MAX_SPEED  = 0.04;
	const double MIN_OFFSET = 0.1;
	const double MAX_OFFSET = 0.25;
	const double X_SPEED_0  = VGCRandomizer::getDouble(MIN_SPEED, MAX_SPEED);
	const double X_SPEED_1  = VGCRandomizer::getDouble(MIN_SPEED, MAX_SPEED);
	const double Y_SPEED_0  = VGCRandomizer::getDouble(MIN_SPEED, MAX_SPEED);
	const double Y_SPEED_1  = VGCRandomizer::getDouble(MIN_SPEED, MAX_SPEED);
	const double X_OFFSET_0 = VGCRandomizer::getDouble(MIN_OFFSET, MAX_OFFSET);  
	const double X_OFFSET_1 = VGCRandomizer::getDouble(MIN_OFFSET, MAX_OFFSET);  
	const double Y_OFFSET_0 = VGCRandomizer::getDouble(MIN_OFFSET, MAX_OFFSET);  
	const double Y_OFFSET_1 = VGCRandomizer::getDouble(MIN_OFFSET, MAX_OFFSET);  
	double       xBase0     = VGCRandomizer::getDouble(0.0, 2.0 * PI);
	double       xBase1     = VGCRandomizer::getDouble(0.0, 2.0 * PI);
	double       yBase0     = VGCRandomizer::getDouble(0.0, 2.0 * PI);
	double       yBase1     = VGCRandomizer::getDouble(0.0, 2.0 * PI);

	int framesPerSecond = 0;

	while(VGCVirtualGameConsole::beginLoop()){
		VGCClock::reset(frameTimer);

		xBase0 += X_SPEED_0;
		xBase1 += X_SPEED_1;
		yBase0 += Y_SPEED_0;
		yBase1 += Y_SPEED_1;
		xBase0 = (xBase0 < 2.0 * PI) ? (xBase0) : (xBase0 - 2.0 * PI); 
		xBase1 = (xBase1 < 2.0 * PI) ? (xBase1) : (xBase1 - 2.0 * PI); 
		yBase0 = (yBase0 < 2.0 * PI) ? (yBase0) : (yBase0 - 2.0 * PI); 
		yBase1 = (yBase1 < 2.0 * PI) ? (yBase1) : (yBase1 - 2.0 * PI); 

		if(VGCDisplay::beginFrame()){

			VGCColor backgroundColor = VGCColor(255, 0, 64, 0);
			//VGCDisplay::clear(backgroundColor);				
			VGCDisplay::renderImage(background, VGCVector(0, 0), VGCVector(0, 0), VGCAdjustment(0.0, 0.0));

			for(int blobIndex = 0; blobIndex < BLOB_COUNT; blobIndex++){
				const double        X_FACTOR_0 = sin(xBase0 + (blobIndex * X_OFFSET_0));
				const double        X_FACTOR_1 = sin(xBase1 + (blobIndex * X_OFFSET_1));
				const double        Y_FACTOR_0 = sin(yBase0 + (blobIndex * Y_OFFSET_0));
				const double        Y_FACTOR_1 = sin(yBase1 + (blobIndex * Y_OFFSET_1));
				const double        X_FACTOR   = ((2.0 + X_FACTOR_0 + X_FACTOR_1) / 4.0);
				const double        Y_FACTOR   = ((2.0 + Y_FACTOR_0 + Y_FACTOR_1) / 4.0);
				const int           X          = int(X_FACTOR * (DISPLAY_WIDTH - BLOB_WIDTH));
				const int           Y          = int(Y_FACTOR * (DISPLAY_HEIGHT - BLOB_HEIGHT));
				const VGCVector     position   = VGCVector(X, Y);
				const int           INDEX_X    = ((blobIndex / BLOB_X_FRAME_COUNT) % BLOB_X_FRAME_COUNT); 
				const int           INDEX_Y    = (blobIndex % BLOB_Y_FRAME_COUNT); 
				const VGCVector     frameIndex = VGCVector(INDEX_X, INDEX_Y);
				const VGCAdjustment adjustment = VGCAdjustment(0.0, 0.0);
				VGCDisplay::renderImage(blobImage, frameIndex, position, adjustment);
			}

			VGCColor      labelColor      = VGCColor(255, 255, 255, 255);
			VGCVector     labelPosition   = VGCVector(0, 0);
			VGCAdjustment labelAdjustment = VGCAdjustment(0.0, 0.0);
			ostringstream label;
			label << "FPS: " << framesPerSecond << '\0';
			VGCDisplay::renderString(font, label.str(), labelColor, labelPosition, labelAdjustment);

			VGCDisplay::endFrame();
		}

		//VGCClock::wait(frameTimer);
		framesPerSecond = int(0.5 + 1.0 /VGCClock::getTime(frameTimer));

		VGCKeyboard::clearBuffer();

		VGCVirtualGameConsole::endLoop();
	}

	VGCDisplay::closeFont(font);

	VGCClock::closeTimer(frameTimer);

	VGCDisplay::closeImage(blobImage);

	VGCDisplay::closeImage(background);

	VGCVirtualGameConsole::finalize();

	return 0;
}

