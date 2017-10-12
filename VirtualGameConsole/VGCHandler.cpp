#include "VGCHandler.h"
#include "VGCReferenced.h"
#include "VGCAssert.h"



/* VGCHandler */

/* Public creators */
VGCHandler::VGCHandler() :
	VGCReferenced(){
	
	VGCAssert(invariant());
}

VGCHandler::VGCHandler(const VGCHandler &handler) :
	VGCReferenced(){
	
	VGCAssert(invariant());
}

VGCHandler::~VGCHandler(){
	VGCAssert(invariant());
}

/* Protected accessors */
bool VGCHandler::invariant() const{
	return VGCReferenced::invariant();
}



/* VGCFunctionHandler */

/* Public creators */
VGCFunctionHandler::VGCFunctionHandler(FunctionPointer function) :
	VGCHandler(),
	mFunction(function){
		
	VGCAssert(invariant());
}

VGCFunctionHandler::VGCFunctionHandler(const VGCFunctionHandler &functionHandler) :
	VGCHandler(),
	mFunction(functionHandler.mFunction){
	
	VGCAssert(invariant());
}

VGCFunctionHandler::~VGCFunctionHandler(){
	VGCAssert(invariant());

	mFunction = 0;

	VGCAssert(!invariant());
}

/* Public manipulators */
void VGCFunctionHandler::setFunction(FunctionPointer function){
	VGCAssert(invariant());

	mFunction = function;

	VGCAssert(invariant());
}

/* Public accessors */
VGCFunctionHandler::FunctionPointer VGCFunctionHandler::getFunction() const{
	VGCAssert(invariant());

	return mFunction;
}

void VGCFunctionHandler::handleMessage(const VGCMessage &message) const{
	VGCAssert(invariant());

	(*mFunction)(message);

	VGCAssert(invariant());
}

/* Protected accessors */
bool VGCFunctionHandler::invariant() const{
	return (VGCHandler::invariant()) && (0 != mFunction);
}
