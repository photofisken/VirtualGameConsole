#include "VGCKeyboard.h"
#include "VGCAssert.h"
#include "VGCKey.h"
#include "VGCBus.h"
#include <set>
#include <string>



/* File scope data */
static int                 fInitializeMinusFinalizeCount = 0;
static int                 fBeginMinusEndCount           = 0;
static std::string         fBuffer                       = std::string();
static VGCKeyboard::KeySet fIsPressedKeySet              = VGCKeyboard::KeySet();
static VGCKeyboard::KeySet fWasPressedKeySet             = VGCKeyboard::KeySet();
static VGCFunctionHandler  *fMessageHandler              = 0;

/* File scope functions */
static bool fInvariant(){
	return (0 < fInitializeMinusFinalizeCount);
}

static void fHandleMessage(const VGCMessage &message){
	VGCAssert(0 < fBeginMinusEndCount);

	if(const VGCKeyMessage *keyMessage = dynamic_cast<const VGCKeyMessage*>(&message)){
		const VGCKeyMessage::Event event = keyMessage->getEvent();
		const VGCKey               &key  = keyMessage->getKey();
		if(VGCKeyMessage::PRESS_EVENT == event){
			fIsPressedKeySet.insert(key);
			const VGCKey backspaceKey = VGCKey(VGCKey::BACKSPACE_KEY);
			const VGCKey deleteKey    = VGCKey(VGCKey::DELETE_KEY);
			if((!fBuffer.empty()) && ((key == backspaceKey) || (key == deleteKey))){
				fBuffer.resize(fBuffer.size() - 1);
			}
		}
		else if(VGCKeyMessage::RELEASE_EVENT == event){
			fIsPressedKeySet.erase(key);
			fWasPressedKeySet.insert(key);
		}	
	}
	else if(const VGCCharacterMessage *characterMessage = dynamic_cast<const VGCCharacterMessage*>(&message)){
		char character = characterMessage->getCharacter();
		if((32 <= character) && (character <= 127)){
			fBuffer += character;		
		}

	}	
}


/* VGCKeyboard */

/* File scope functions */
void VGCKeyboard::beginLoop(){
	VGCAssert(fInvariant());

	if(0 == fBeginMinusEndCount){
		fWasPressedKeySet.clear();
	}
	fBeginMinusEndCount++;

	VGCAssert(fInvariant());
}

void VGCKeyboard::clearBuffer(){
	VGCAssert(fInvariant());

	fBuffer = "";

	VGCAssert(fInvariant());
}

void VGCKeyboard::endLoop(){
	VGCAssert(fInvariant());
	VGCAssert(0 < fBeginMinusEndCount);

	fBeginMinusEndCount--;

	VGCAssert(fInvariant());
}

void VGCKeyboard::finalizeKeyboard(){
	VGCAssert(fInvariant());
	VGCAssert(0 == fBeginMinusEndCount);

	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		fIsPressedKeySet.clear();
		fWasPressedKeySet.clear();
		fBuffer = "";
		VGCBus::unregisterHandler(fMessageHandler);
		delete fMessageHandler;
		fMessageHandler = 0;

		VGCBus::finalizeBus();
	}
}

const std::string& VGCKeyboard::getBuffer(){
	VGCAssert(fInvariant());

	return fBuffer;
}

void VGCKeyboard::initializeKeyboard(){
	if(0 == fInitializeMinusFinalizeCount){
		VGCBus::initializeBus();

		VGCAssert("" == fBuffer);
		VGCAssert(fIsPressedKeySet.empty());	
		VGCAssert(fWasPressedKeySet.empty());
		VGCAssert(!fMessageHandler);

		fMessageHandler = new VGCFunctionHandler(&fHandleMessage);
		VGCBus::registerHandler(fMessageHandler);		
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

bool VGCKeyboard::isPressed(const VGCKey &key){
	VGCAssert(fInvariant());
	
	const bool isPressed = (fIsPressedKeySet.find(key) != fIsPressedKeySet.end());
	return isPressed;
}

bool VGCKeyboard::wasPressed(const VGCKey &key){
	VGCAssert(fInvariant());
	
	const bool wasPressed = (fWasPressedKeySet.find(key) != fWasPressedKeySet.end());
	return wasPressed;
}
