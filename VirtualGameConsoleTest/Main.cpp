#include "VGCVirtualGameConsole.h"
#include "VGCErrorTest.h"
#include "VGCColorTest.h"
#include "VGCVectorTest.h"
#include "VGCAssertTest.h"
#include "VGCBootstrapTest.h"
#include "VGCRectangleTest.h"
#include "VGCAdjustmentTest.h"
#include "VGCReferencedTest.h"
#include "VGCKeyTest.h"
#include "VGCRandomizerTest.h"
#include "VGCTimerImpTest.h"
#include "VGCGDIPlusTest.h"
#include "VGCHandlerTest.h"
#include "VGCMessageTest.h"
#include "VGCClockTest.h"
#include "VGCBusTest.h"
#include "VGCWindowTest.h"
#include "VGCKeyboardTest.h"
#include "VGCImageImpTest.h"
#include "VGCFontImpTest.h"
#include "VGCDisplayTest.h"
#include "VGCVirtualGameConsoleTest.h"
#include <exception>
#include <iostream>
#include <string>



using namespace std;



int VGCMain(const VGCStringVector &arguments){
	try{
		VGCErrorTest::run();
		VGCColorTest::run();
		VGCVectorTest::run();
		VGCAssertTest::run();
		VGCBootstrapTest::run();
		VGCRectangleTest::run();
		VGCAdjustmentTest::run();
		VGCReferencedTest::run();
		VGCRandomizerTest::run();
		VGCTimerImpTest::run();
		VGCKeyTest::run();
		VGCGDIPlusTest::run();
		VGCHandlerTest::run();
		VGCMessageTest::run();
		VGCClockTest::run();
		VGCBusTest::run();
		VGCWindowTest::run();
		VGCKeyboardTest::run();
		VGCImageImpTest::run();
		VGCFontImpTest::run();
		VGCDisplayTest::run();
		VGCVirtualGameConsoleTest::run();
	}
	catch(const exception &exception){
		VGCError(string("Exception: ") + exception.what());
		return -1;
	}
	catch(...){
		VGCError("Unknown exception.");
		return -1;
	}
	return 0;
}