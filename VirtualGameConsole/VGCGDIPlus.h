#ifndef INCLUDED_VGCGDIPLUS
#define INCLUDED_VGCGDIPLUS



/******************************************************************************

This component is used to synchronize GDIPlus initialization/finalization. 
The component also implements a few helper functions relating to GDIPlus.

*******************************************************************************/



#include "VGCColor.h"
#include "VGCRectangle.h"
#include <windows.h>
#include <gdiplus.h>
#include <string>



#pragma comment( lib, "gdiplus.lib" ) 



struct VGCGDIPlus{

	/* Public functions */
	static void           finalizeGDIPlus();
	static std::string    getStatusDescription(Gdiplus::Status status);
	static void           initializeGDIPlus();
	static Gdiplus::Color translateColor(const VGCColor &color);
	static VGCColor       translateColor(const Gdiplus::Color &color);
	static Gdiplus::Rect  translateRectangle(const VGCRectangle &rectangle);
	static VGCRectangle   translateRectangle(const Gdiplus::Rect &rectangle);
	static std::wstring   translateString(const std::string &string);
};

#endif