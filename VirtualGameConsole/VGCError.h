#ifndef INCLUDED_VGCERROR
#define INCLUDED_VGCERROR



/******************************************************************************

This component defines a macro for reporting errors.

*******************************************************************************/




#include <string>
#include <cstdlib>


struct VGCErrorBox{
	
	/* Public functions */
	static void messageBox(const std::string &description, const std::string &filename, int lineNumber);
};

#define VGCError(desc) VGCErrorBox::messageBox(desc, __FILE__, __LINE__); std::exit(0); ((void)0)

#endif