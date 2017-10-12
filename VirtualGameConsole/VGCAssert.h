#ifndef INCLUDED_VGCASSERT
#define INCLUDED_VGCASSERT



/******************************************************************************

This component defines two macros for assertions. The debug version is only
active in debug builds (NDEBUG not defined) whereas the release version is
always active.

*******************************************************************************/



#include <string>
#include <cstdlib>



struct VGCAssertBox{
	
	/* Public functions */
	static void messageBox(const std::string &expression, const std::string &filename, int lineNumber);
};



#ifdef NDEBUG
#define VGCDebugAssert(exp) ((void)0)
#define VGCReleaseAssert(exp) if(!(exp)){VGCAssertBox::messageBox(#exp, __FILE__, __LINE__); std::exit(0);} ((void)0)
#else
#define VGCDebugAssert(exp) if(!(exp)){VGCAssertBox::messageBox(#exp, __FILE__, __LINE__); std::exit(0);} ((void)0)
#define VGCReleaseAssert(exp) ((void)0)
#endif

#define VGCAssert(exp) if(!(exp)){VGCAssertBox::messageBox(#exp, __FILE__, __LINE__); std::exit(0);} ((void)0)

#endif
