#ifndef INCLUDED_VGCVIRTUALGAMECONSOLE
#define INCLUDED_VGCVIRTUALGAMECONSOLE



/******************************************************************************

This component implements overarching functionality for the virtual game 
console (VGC). Also, it includes, for client convenience, all public VGC  
headers. 

*******************************************************************************/



#include "VGCError.h"
#include "VGCColor.h"
#include "VGCVector.h"
#include "VGCAssert.h"
#include "VGCBootstrap.h"
#include "VGCRectangle.h"
#include "VGCAdjustment.h"
#include "VGCKey.h"
#include "VGCRandomizer.h"
#include "VGCClock.h"
#include "VGCKeyboard.h"
#include "VGCDisplay.h"
#include <string>
#include <vector>



struct VGCVirtualGameConsole{

	/* Public functions */
	static bool beginLoop();
	static void endLoop();
	static void finalize();
	static void initialize(const std::string &applicationName, int displayWidth, int displayHeight);

};

#endif