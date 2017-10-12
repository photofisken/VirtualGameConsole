#ifndef INCLUDED_VGCBUS
#define INCLUDED_VGCBUS



/******************************************************************************

This component implements a bus (VGCBus) over which messages (VGCMessage) flow 
between client handlers (VGCHandler).

*******************************************************************************/



#include "VGCHandler.h"
#include "VGCMessage.h"
#include <list>



struct VGCBus{

	/* Public types */
	typedef std::list<VGCMessage*> MessageList;
	typedef std::list<VGCHandler*> HandlerList;

	/* Public functions */
	static void dispatchMessages();
	static void finalizeBus();
	static void initializeBus();
	static void postMessage(const VGCMessage &messagePrototype);
	static void registerHandler(VGCHandler *handler);
	static void unregisterHandler(VGCHandler *handler);
};

#endif