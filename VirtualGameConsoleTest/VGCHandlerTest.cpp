#include "VGCHandlerTest.h"
#include "VGCAssert.h"
#include "VGCHandler.h"



static void fHandler1(const VGCMessage &message){
}

static void fHandler2(const VGCMessage &message){
}

void testVGCHandler(){
	/* Abstract baseclass, not tested for now...*/
}

void testVGCFunctionHandler(){
	VGCFunctionHandler h0(&fHandler1);
	VGCAssert(&fHandler1 == h0.getFunction());
	h0.setFunction(&fHandler2);
	VGCAssert(&fHandler2 == h0.getFunction());

	VGCFunctionHandler h1(h0);
	VGCAssert(&fHandler2 == h1.getFunction());
}



/* VGCHandlerTest */

/* Public functions */
void VGCHandlerTest::run(){
	testVGCHandler();
	testVGCFunctionHandler();
}

