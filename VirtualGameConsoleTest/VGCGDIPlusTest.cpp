#include "VGCGDIPlusTest.h"
#include "VGCAssert.h"
#include "VGCGDIPlus.h"



using namespace Gdiplus;



/* VGCGDIPlusTest */

/* Public functions */
void VGCGDIPlusTest::run(){
	VGCGDIPlus::initializeGDIPlus();
	VGCGDIPlus::initializeGDIPlus();

	Color    c0a(1, 2, 3, 4);	
	VGCColor c1a(1, 2, 3, 4);
	Color    c0b = VGCGDIPlus::translateColor(c1a);
	VGCColor c1b = VGCGDIPlus::translateColor(c0a);
	VGCAssert(1 == c0b.GetAlpha());
	VGCAssert(2 == c0b.GetRed());
	VGCAssert(3 == c0b.GetGreen());
	VGCAssert(4 == c0b.GetBlue());
	VGCAssert(1 == c1b.getAlpha());
	VGCAssert(2 == c1b.getRed());
	VGCAssert(3 == c1b.getGreen());
	VGCAssert(4 == c1b.getBlue());

	VGCAssert("" != VGCGDIPlus::getStatusDescription(Ok));

	Rect         rect      = Rect(0, 1, 2, 3);
	VGCRectangle rectangle = VGCRectangle(VGCVector(0, 1), 2, 3);
	rect                   = VGCGDIPlus::translateRectangle(rectangle);
	rectangle              = VGCGDIPlus::translateRectangle(rect);
	VGCAssert(0 == rect.GetLeft());
	VGCAssert(1 == rect.GetTop());
	VGCAssert(2 == rect.GetRight());
	VGCAssert(4 == rect.GetBottom());
	VGCAssert(VGCRectangle(VGCVector(0, 1), 2, 3) == rectangle);
	
	VGCAssert(2 == sizeof(wchar_t));
	std::string  string("Hej!");
	std::wstring wideString = VGCGDIPlus::translateString(string);
	VGCAssert(4 == wideString.size());
	VGCAssert(L"Hej!" == wideString);

	VGCGDIPlus::finalizeGDIPlus();
	VGCGDIPlus::finalizeGDIPlus();
}


