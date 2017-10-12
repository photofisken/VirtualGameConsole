#include "VGCKeyboardTest.h"
#include "VGCAssert.h"
#include "VGCKeyboard.h"
#include "VGCMessage.h"
#include "VGCBus.h"



/* VGCKeyboardTest */

/* Public functions */
void VGCKeyboardTest::run(){
	VGCKeyboard::initializeKeyboard();
	VGCKeyboard::initializeKeyboard();

	VGCKeyboard::beginLoop();
	VGCBus::postMessage(VGCKeyMessage(VGCKeyMessage::PRESS_EVENT, VGCKey::A_KEY));
	VGCBus::postMessage(VGCKeyMessage(VGCKeyMessage::PRESS_EVENT, VGCKey::B_KEY));
	VGCBus::postMessage(VGCKeyMessage(VGCKeyMessage::RELEASE_EVENT, VGCKey::A_KEY));
	VGCBus::postMessage(VGCCharacterMessage('A'));
	VGCBus::postMessage(VGCCharacterMessage('B'));
	VGCBus::dispatchMessages();	
	
	VGCAssert(!VGCKeyboard::wasPressed(VGCKey::ESCAPE_KEY));

	VGCAssert(!VGCKeyboard::isPressed(VGCKey::A_KEY));
	VGCAssert(VGCKeyboard::wasPressed(VGCKey::A_KEY));
	VGCAssert(VGCKeyboard::isPressed(VGCKey::B_KEY));
	VGCAssert("AB" == VGCKeyboard::getBuffer());
	VGCKeyboard::clearBuffer();
	VGCAssert("" == VGCKeyboard::getBuffer());
	
	VGCKeyboard::endLoop();
	VGCKeyboard::finalizeKeyboard();
	VGCKeyboard::finalizeKeyboard();

	VGCKeyboard::initializeKeyboard();
	VGCKeyboard::finalizeKeyboard();
}

