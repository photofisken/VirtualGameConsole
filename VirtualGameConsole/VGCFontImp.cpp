#include "VGCFontImp.h"
#include "VGCAssert.h"
#include "VGCError.h"
#include "VGCReferenced.h"
#include "VGCVector.h"
#include "VGCAdjustment.h"
#include "VGCGDIPlus.h"
#include <string>
#include <windows.h>
#include <gdiplus.h>



using namespace Gdiplus;



/* File scope data */
static int fInitializeMinusFinalizeCount = 0;



/* File scope functions */
static bool fInvariant(){
	return (0 < fInitializeMinusFinalizeCount);
}

static int fRound(float value){
	if(0.0f == value){
		return 0;
	}
	else if (value < 0.0f){
		return int(value - 0.5f);
	}
	else{
		return int(value + 0.5f);
	}
}



/* VGCFontImp */

/* Public creators */
VGCFontImp::VGCFontImp(Graphics *graphics, const std::string &name, int size) :
	VGCReferenced(),
	mGraphics(graphics),
	mName(name),
	mSize(size),
	mFont(0){

	VGCAssert(fInvariant());
	VGCAssert(graphics);
	VGCAssert(0 <= mSize);
	VGCAssert("" != mName);

	update();

	VGCAssert(invariant());
}

VGCFontImp::~VGCFontImp(){
	VGCAssert(invariant());

	delete mFont;
	mFont = 0;

	VGCAssert(!invariant());
}

/* Public manipulators */
void VGCFontImp::setName(const std::string &name){
	VGCAssert(invariant());
	VGCAssert("" != name);

	mName = name;
	update();

	VGCAssert(invariant());
}

void VGCFontImp::setSize(int size){
	VGCAssert(invariant());
	VGCAssert(0 <= size);
	
	mSize = size;
	update();

	VGCAssert(invariant());
}

/* Public accessors */
Graphics* VGCFontImp::getGraphics() const{
	VGCAssert(invariant());

	return mGraphics;
}

int VGCFontImp::getLineHeight() const{
	VGCAssert(invariant());

	const int HEIGHT = fRound(mFont->GetHeight(mGraphics));
	VGCAssert(0 <= HEIGHT);
	return HEIGHT;
}

int VGCFontImp::getLineWidth(const std::string &string) const{
	VGCAssert(invariant());

	std::wstring wideString         = VGCGDIPlus::translateString(string);
	RectF        boundingRectangle;
	mGraphics->MeasureString(wideString.c_str(), -1, mFont, PointF(0.0f, 0.0f), &boundingRectangle);
	const int    WIDTH = fRound(boundingRectangle.GetRight() - boundingRectangle.GetLeft());
	VGCAssert(0 <= WIDTH);
	return WIDTH;
}

const std::string& VGCFontImp::getName() const{
	VGCAssert(invariant());

	return mName;
}

int VGCFontImp::getSize() const{
	VGCAssert(invariant());

	return mSize;
}

void VGCFontImp::render(const std::string &string,
                        const VGCColor &color,
                        const VGCVector &position,
                        const VGCAdjustment &adjustment) const{
	VGCAssert(invariant());
	
	std::wstring wideString = VGCGDIPlus::translateString(string);
	RectF        boundingRectangle;
	mGraphics->MeasureString(wideString.c_str(), -1, mFont, PointF(0.0f, 0.0f), &boundingRectangle);
	const int    WIDTH  = fRound(boundingRectangle.GetRight() - boundingRectangle.GetLeft());
	const int    HEIGHT = fRound(mFont->GetHeight(mGraphics));
	VGCAssert(0 <= WIDTH);
	VGCAssert(0 <= HEIGHT);
	const float  X      = float(position.getX() - adjustment.getXAdjustment().computeOffset(WIDTH));
	const float  Y      = float(position.getY() - adjustment.getYAdjustment().computeOffset(HEIGHT));
	SolidBrush   solidBrush(VGCGDIPlus::translateColor(color));
	PointF       floatPosition(X, Y);
	Status       status = mGraphics->DrawString(wideString.c_str(), -1, mFont, floatPosition, &solidBrush);
	if(Ok != status){
		VGCError("Could not draw string. " + VGCGDIPlus::getStatusDescription(status));
	}
}

/* Public functions */
void VGCFontImp::finalizeFontImp(){
	VGCAssert(fInvariant());

	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		VGCGDIPlus::finalizeGDIPlus();
	}
}

void VGCFontImp::initializeFontImp(){
	if(0 == fInitializeMinusFinalizeCount){
		VGCGDIPlus::initializeGDIPlus();
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

/* Private manipulators */
void VGCFontImp::update(){
	if(0 != mFont){
		delete mFont;
	}
	std::wstring wideName = VGCGDIPlus::translateString(mName);
	mFont = new Font(wideName.c_str(), float(mSize), FontStyleRegular, UnitPixel, NULL);
	VGCAssert(mFont);
	Status status = mFont->GetLastStatus();
	if(Ok != status){
		VGCError("Could not create font. " + VGCGDIPlus::getStatusDescription(status));		
	}
}

/* Private accessors */
bool VGCFontImp::invariant() const{
	return 
		VGCReferenced::invariant() &&
		("" != mName) &&
		(0 <= mSize) &&
		(0 != mFont);
}

