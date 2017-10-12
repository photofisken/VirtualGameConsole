#ifndef INCLUDED_VGCHANDLER
#define INCLUDED_VGCHANDLER



/******************************************************************************

This component implements a handler types that are used to receive and handle
messages, e.g. character input from the keyboard.

*******************************************************************************/



#include "VGCReferenced.h"



class VGCMessage;



class VGCHandler : public VGCReferenced{
public:

	/* Public creators */
	VGCHandler();
	VGCHandler(const VGCHandler &handler);
	virtual ~VGCHandler();

	/* Public accessors */
	virtual void handleMessage(const VGCMessage &message) const = 0;

protected:

	/* Protected accessors */
	bool invariant() const;

private:

	/* Private manipulators */
	VGCHandler& operator=(const VGCHandler &handler);
};



class VGCFunctionHandler : public VGCHandler{
public:

	/* Public types */
	typedef void (*FunctionPointer)(const VGCMessage &message);

	/* Public creators */
	VGCFunctionHandler(FunctionPointer function);
	VGCFunctionHandler(const VGCFunctionHandler &functionHandler);
	virtual ~VGCFunctionHandler();

	/* Public manipulators */
	void setFunction(FunctionPointer function);

	/* Public accessors */
	FunctionPointer getFunction()                            const;
	virtual void    handleMessage(const VGCMessage &message) const;

protected:

	/* Protected accessors */
	bool invariant() const;

private:

	/* Private manipulators */
	VGCFunctionHandler& operator=(const VGCFunctionHandler &functionHandler);

	/* Private data */
	FunctionPointer	mFunction;
};

#endif