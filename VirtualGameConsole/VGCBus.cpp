#include "VGCBus.h"
#include "VGCHandler.h"
#include "VGCMessage.h"
#include "VGCAssert.h"
#include <list>
#include <algorithm>



/* File scope data */
static int                 fInitializeMinusFinalizeCount = 0;
static VGCBus::MessageList fMessageList                  = VGCBus::MessageList();
static VGCBus::HandlerList fHandlerList                  = VGCBus::HandlerList();



/* File scope functions */
static bool fHandlerIsRegistered(VGCHandler *handler){
	return (fHandlerList.end() != std::find(fHandlerList.begin(), fHandlerList.end(), handler));
}

static bool fInvariant(){
	return (0 < fInitializeMinusFinalizeCount);
}



/* VGCBus */

/* Public functions */
void VGCBus::dispatchMessages(){
	VGCAssert(fInvariant());

	while(!fMessageList.empty()){
		VGCMessage *message = fMessageList.front();
		VGCAssert(message);
		for(HandlerList::iterator i = fHandlerList.begin(); i != fHandlerList.end(); i++){
			VGCHandler *handler = *i;
			VGCAssert(handler);
			handler->handleMessage(*message);
		}
		delete message;
		fMessageList.pop_front();
	}

	VGCAssert(fMessageList.empty());
	VGCAssert(fInvariant());
}

void VGCBus::finalizeBus(){
	VGCAssert(fInvariant());

	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		VGCAssert(fHandlerList.empty());
		while(!fMessageList.empty()){
			VGCMessage *message = fMessageList.front();
			VGCAssert(message);
			delete message;
			fMessageList.pop_front();
		}	
		VGCAssert(fMessageList.empty());		
		VGCAssert(!fInvariant());
	}
}

void VGCBus::initializeBus(){
	if(0 == fInitializeMinusFinalizeCount){
		VGCAssert(fMessageList.empty());
		VGCAssert(fHandlerList.empty());
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

void VGCBus::postMessage(const VGCMessage &messagePrototype){
	VGCAssert(fInvariant());

	fMessageList.push_back(messagePrototype.clone());

	VGCAssert(fInvariant());
}

void VGCBus::registerHandler(VGCHandler *handler){
	VGCAssert(fInvariant());
	VGCAssert(handler);
	VGCAssert(!fHandlerIsRegistered(handler));
	
	handler->increaseReferenceCount();
	fHandlerList.push_back(handler);

	VGCAssert(fHandlerIsRegistered(handler));
	VGCAssert(fInvariant());
}

void VGCBus::unregisterHandler(VGCHandler *handler){
	VGCAssert(fInvariant());
	VGCAssert(handler);
	VGCAssert(fHandlerIsRegistered(handler));
	
	HandlerList::iterator i = std::find(fHandlerList.begin(), fHandlerList.end(), handler);
	VGCAssert(i != fHandlerList.end());
	fHandlerList.erase(i);
	handler->decreaseReferenceCount();

	VGCAssert(!fHandlerIsRegistered(handler));
	VGCAssert(fInvariant());
}

