#include "VGCVirtualGameConsole.h"
#include "VGCAssert.h"
#include "VGCDisplay.h"
#include "VGCKeyboard.h"
#include "VGCRandomizer.h"
#include "VGCClock.h"
#include "VGCBus.h"
#include "VGCWindow.h"
#include <string>
#include <vector>
#include <strstream>


/* File scope data */
static int fInitializeMinusFinalizeCount = 0;
static int fBeginMinusEndCount           = 0;



/* File scope functions */
static bool fInvariant(){
	return (0 < fInitializeMinusFinalizeCount);
}

static bool fInLoop(){
	return (0 < fBeginMinusEndCount);
}



/* VGCVirtualGameConsole */

/* Public functions */
bool VGCVirtualGameConsole::beginLoop(){
	VGCAssert(fInvariant());	

	if(0 == fBeginMinusEndCount){
		VGCKeyboard::beginLoop();
		VGCWindow::handleMessages();
		VGCBus::dispatchMessages();
		const bool windowIsOpen = VGCWindow::windowIsOpen();
		if(windowIsOpen){
			fBeginMinusEndCount++;
			return true;
		}
		else{
			VGCKeyboard::endLoop();
			return false;
		}
	}
	else{
		fBeginMinusEndCount++;
		return true;
	}
}

void VGCVirtualGameConsole::endLoop(){
	VGCAssert(fInvariant());	
	VGCAssert(fInLoop());

	fBeginMinusEndCount--;
	if(0 == fBeginMinusEndCount){
		VGCKeyboard::endLoop();
	}

	VGCAssert(fInvariant());	
}

void VGCVirtualGameConsole::finalize(){
	VGCAssert(fInvariant());

	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		VGCClock::finalizeClock();
		VGCRandomizer::finalizeRandomizer();
		VGCKeyboard::finalizeKeyboard();
		VGCDisplay::finalizeDisplay();
	}
}

void VGCVirtualGameConsole::initialize(const std::string &applicationName, int displayWidth, int displayHeight){
	VGCAssert(0 <= displayWidth);
	VGCAssert(0 <= displayHeight);

	if(0 == fInitializeMinusFinalizeCount){
		VGCDisplay::initializeDisplay(applicationName, displayWidth, displayHeight);
		VGCKeyboard::initializeKeyboard();
		VGCRandomizer::initializeRandomizer();
		VGCClock::initializeClock();
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}







