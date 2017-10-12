#include "VGCGDIPlus.h"
#include "VGCVector.h"
#include "VGCColor.h"
#include "VGCRectangle.h"
#include "VGCAssert.h"
#include "VGCError.h"
#include <windows.h>
#include <gdiplus.h>
#include <string>


using namespace Gdiplus;



/* File scope data */
static int                 fInitializeMinusFinalizeCount = 0;
static GdiplusStartupInput fGDIPlusStartupInput          = GdiplusStartupInput(NULL, NULL, FALSE);
static ULONG_PTR           fGDIPlusToken                 = 0;



/* File scope functions */
static std::string fGetStatusDescription(Status status){
	std::string description = "";
	switch(status){
    case Ok:
		description = "Status ok.";
		break;
    case GenericError:
		description = "Generic error.";
		break;
    case InvalidParameter:
		description = "Invalid parameter.";
		break;
    case OutOfMemory:
		description = "Out of memory.";
		break;
    case ObjectBusy:
		description = "Object busy.";
		break;
    case InsufficientBuffer:
		description = "Insufficient buffer.";
		break;
    case NotImplemented:
		description = "Not implemented.";
		break;
    case Win32Error:
		description = "Win32 error.";
		break;
    case WrongState:
		description = "Wrong state.";
		break;
    case Aborted:
		description = "Aborted.";
		break;
    case FileNotFound:
		description = "File not found.";
		break;
    case ValueOverflow:
		description = "Value overflow.";
		break;
    case AccessDenied:
		description = "Access denied.";
		break;
    case UnknownImageFormat:
		description = "Unknown image format.";
		break;
    case FontFamilyNotFound:
		description = "Font family not found.";
		break;
    case FontStyleNotFound:
		description = "Font style not found.";
		break;
    case NotTrueTypeFont:
		description = "Not a true type font.";
		break;
    case UnsupportedGdiplusVersion:
		description = "Unsupported GDI+ version.";
		break;
    case GdiplusNotInitialized:
		description = "GDI+ not initialized.";
		break;
    case PropertyNotFound:
		description = "Property not found.";
		break;
    case PropertyNotSupported:
		description = "Property not supported.";
		break;
	default:
		description = "Unknown status.";
		break;
	}
	return description;
}

static bool fInvariant(){
	return (0 < fInitializeMinusFinalizeCount);
}



/* VGCGDIPlus */

/* Public functions */
void VGCGDIPlus::finalizeGDIPlus(){
	VGCAssert(fInvariant());

	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		GdiplusShutdown(fGDIPlusToken);		
	}
}

std::string VGCGDIPlus::getStatusDescription(Gdiplus::Status status){
	VGCAssert(fInvariant());
	
	return fGetStatusDescription(status);
}

void VGCGDIPlus::initializeGDIPlus(){
	if(0 == fInitializeMinusFinalizeCount){
		Status status = GdiplusStartup(&fGDIPlusToken, &fGDIPlusStartupInput, NULL);
		if(Ok != status){
			VGCError("Could not initialize GDI+. " + fGetStatusDescription(status));
		}
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

Color VGCGDIPlus::translateColor(const VGCColor &color){
	VGCAssert(fInvariant());

	return Color(color.getAlpha(), color.getRed(), color.getGreen(), color.getBlue());
}

VGCColor VGCGDIPlus::translateColor(const Gdiplus::Color &color){
	VGCAssert(fInvariant());

	return VGCColor(color.GetAlpha(), color.GetRed(), color.GetGreen(), color.GetBlue());
}

Rect VGCGDIPlus::translateRectangle(const VGCRectangle &rectangle){
	VGCAssert(fInvariant());
	
	const int X      = rectangle.getPosition().getX();
	const int Y      = rectangle.getPosition().getY();
	const int WIDTH  = rectangle.getWidth();
	const int HEIGHT = rectangle.getHeight();
	return Rect(X, Y, WIDTH, HEIGHT);
}

VGCRectangle VGCGDIPlus::translateRectangle(const Rect &rectangle){
	VGCAssert(fInvariant());
	
	const int X      = rectangle.GetLeft();
	const int Y      = rectangle.GetTop();
	const int WIDTH  = (rectangle.GetRight() - rectangle.GetLeft());
	const int HEIGHT = (rectangle.GetBottom() - rectangle.GetTop());
	return VGCRectangle(VGCVector(X, Y), WIDTH, HEIGHT);
}

std::wstring VGCGDIPlus::translateString(const std::string &string){
	VGCAssert(fInvariant());

	std::wstring wideString      = std::wstring();
	const int    CHARACTER_COUNT = int(string.size());
	for(int i = 0; i < CHARACTER_COUNT; i++){
		wideString += wchar_t(string[i]);
	}
	return wideString;
}
