#ifndef INCLUDED_VGCKEYBOARD
#define INCLUDED_VGCKEYBOARD



/******************************************************************************

This compoenent implements keyboard functionality; including character input 
buffer management.

*******************************************************************************/



#include "VGCKey.h"
#include <set>
#include <string>


struct VGCKeyboard{

	/* Public types */
	typedef std::set<VGCKey> KeySet;

	/* File scope functions */
	static void               beginLoop();
	static void               clearBuffer();
	static void               endLoop();
	static void               finalizeKeyboard();
	static const std::string& getBuffer();
	static void               initializeKeyboard();
	static bool               isPressed(const VGCKey &key);
	static bool               wasPressed(const VGCKey &key);
};

#endif