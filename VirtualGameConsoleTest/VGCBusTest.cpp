#include "VGCBusTest.h"
#include "VGCAssert.h"
#include "VGCBus.h"



static int fCounter = 0;

static void fHandler1(const VGCMessage &message){
	fCounter++;
}

static void fHandler2(const VGCMessage &message){
	fCounter++;
}



/* VGCBusTest */

/* Public functions */
void VGCBusTest::run(){
	VGCBus::initializeBus();
	VGCBus::initializeBus();

	fCounter = 0;

	VGCFunctionHandler *handler1 = new VGCFunctionHandler(&fHandler1);
	VGCFunctionHandler *handler2 = new VGCFunctionHandler(&fHandler2);
	VGCBus::registerHandler(handler1);
	VGCBus::registerHandler(handler2);

	VGCBus::postMessage(VGCNotificationMessage());
	VGCBus::postMessage(VGCNotificationMessage());

	VGCBus::dispatchMessages();

	VGCAssert(4 == fCounter);

	VGCBus::unregisterHandler(handler2);
	VGCBus::unregisterHandler(handler1);

	delete handler2;
	delete handler1;

	VGCBus::finalizeBus();
	VGCBus::finalizeBus();
}

