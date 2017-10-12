#include "VGCImageImp.h"
#include "VGCError.h"
#include "VGCAssert.h"
#include "VGCAdjustment.h"
#include "VGCVector.h"
#include "VGCRectangle.h"
#include "VGCReferenced.h"
#include "VGCGDIPlus.h"
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>



using namespace Gdiplus;



/* File scope data */
static int fInitializeMinusFinalizeCount = 0;



/* File scope functions */
static bool fInvariant(){
	return (0 < fInitializeMinusFinalizeCount);
}



/* VGCImageImp */

/* Public creators */
VGCImageImp::VGCImageImp() :
	VGCReferenced(){

	VGCAssert(invariant());
}

VGCImageImp::~VGCImageImp(){
	VGCAssert(invariant());
}

/* Public functions */
void VGCImageImp::finalizeImageImp(){
	VGCAssert(fInvariant());

	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		VGCGDIPlus::finalizeGDIPlus();
	}
}

void VGCImageImp::initializeImageImp(){
	if(0 == fInitializeMinusFinalizeCount){
		VGCGDIPlus::initializeGDIPlus();
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

/* Protected accessors */
bool VGCImageImp::invariant() const{
	return (VGCReferenced::invariant() && fInvariant());
}


/* VGCSimpleImageImp */

/* Public creators */
VGCSimpleImageImp::VGCSimpleImageImp(Graphics *graphics, const std::string &filename) :
	VGCImageImp(),
	mGraphics(graphics),
	mBitmap(0),
	mCachedBitmap(0){

	VGCAssert(fInvariant());
	VGCAssert(graphics);

	mBitmap = new Bitmap(VGCGDIPlus::translateString(filename).c_str(), FALSE);
	VGCAssert(mBitmap);
	Status status = mBitmap->GetLastStatus();
	if(Ok != status){
		VGCError("Could not create bitmap. " + VGCGDIPlus::getStatusDescription(status));
	}
	update();

	VGCAssert(invariant());	
}

VGCSimpleImageImp::VGCSimpleImageImp(Graphics *graphics, Gdiplus::Bitmap *bitmap, const VGCRectangle &rectangle) :
	VGCImageImp(),
	mGraphics(graphics),
	mBitmap(0),
	mCachedBitmap(0){

	VGCAssert(fInvariant());
	VGCAssert(graphics);	
	VGCAssert(bitmap);	

	const int         WIDTH            = rectangle.getWidth();
	const int         HEIGHT           = rectangle.getHeight();
	const PixelFormat PIXEL_FORMAT     = bitmap->GetPixelFormat();
	Rect              sourceRectangle  = VGCGDIPlus::translateRectangle(rectangle);
	BitmapData        sourceBitmapData = BitmapData();
	Status            status           = bitmap->LockBits(&sourceRectangle, ImageLockModeRead, PIXEL_FORMAT, &sourceBitmapData);
	if(Ok != status){
		VGCError("Could not lock source bitmap. " + VGCGDIPlus::getStatusDescription(status));
	}
	const INT  STRIDE  = sourceBitmapData.Stride;
	BYTE       *pixels = (BYTE*)sourceBitmapData.Scan0;
	mBitmap = new Bitmap(WIDTH, HEIGHT, STRIDE, PIXEL_FORMAT, pixels);
	if(Ok != mBitmap->GetLastStatus()){
		VGCError("Could not create target bitmap. " + VGCGDIPlus::getStatusDescription(status));
	}
	status = bitmap->UnlockBits(&sourceBitmapData);
	if(Ok != status){
		VGCError("Could not unlock source bitmap. " + VGCGDIPlus::getStatusDescription(status));
	}
	update();

	/* Previous implementation, works, but there is a faster one...
	const int X_BASE = rectangle.getPosition().getX();
	const int Y_BASE = rectangle.getPosition().getY();
	const int WIDTH  = rectangle.getWidth();
	const int HEIGHT = rectangle.getHeight();
	mBitmap          = new Bitmap(WIDTH, HEIGHT, bitmap->GetPixelFormat());
	Status status    = mBitmap->GetLastStatus();
	if(Ok != status){
		VGCError("Could not create bitmap. " + VGCGDIPlus::getStatusDescription(status));
	}
	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			Color color;
			bitmap->GetPixel(X_BASE + x, Y_BASE + y, &color);
			mBitmap->SetPixel(x, y, color);
		}
	}
	update(); 
	*/

	/* Previous implementation, works but is slow, for some reason...
	Rect rect = VGCGDIPlus::translateRectangle(rectangle);
	mBitmap = bitmap->Clone(rect, bitmap->GetPixelFormat());
	VGCAssert(mBitmap);
	Status status = mBitmap->GetLastStatus();
	if(Ok != status){
		VGCError("Could not create bitmap. " + VGCGDIPlus::getStatusDescription(status));
	}
	update();
	*/

	VGCAssert(invariant());	
}

VGCSimpleImageImp::~VGCSimpleImageImp(){
	VGCAssert(invariant());	
	
	delete mCachedBitmap;
	delete mBitmap;
	mGraphics     = 0;
	mCachedBitmap = 0;
	mBitmap       = 0;

	VGCAssert(!invariant());	
}

/* Public accessors */
Graphics* VGCSimpleImageImp::getGraphics() const{
	VGCAssert(invariant());	

	return mGraphics;
}

int VGCSimpleImageImp::getHeight() const{
	VGCAssert(invariant());	

	return int(mBitmap->GetHeight());
}

int VGCSimpleImageImp::getWidth() const{
	VGCAssert(invariant());	

	return int(mBitmap->GetWidth());
}

int VGCSimpleImageImp::getXFrameCount() const{
	VGCAssert(invariant());	

	return 0;
}

int VGCSimpleImageImp::getYFrameCount() const{
	VGCAssert(invariant());	

	return 0;
}

void VGCSimpleImageImp::render(
	const VGCVector &frameIndex, 
	const VGCVector &position,
	const VGCAdjustment &adjustment) const{

	VGCAssert(invariant());	
	VGCAssert(VGCVector(0, 0) == frameIndex);
	
	const int X          = position.getX();
	const int Y          = position.getY();
	const int WIDTH      = mBitmap->GetWidth();
	const int HEIGHT     = mBitmap->GetHeight();
	const int ADJUSTED_X = (X - adjustment.getXAdjustment().computeOffset(WIDTH));
	const int ADJUSTED_Y = (Y - adjustment.getYAdjustment().computeOffset(HEIGHT));
	Status    status     = mGraphics->DrawCachedBitmap(mCachedBitmap, ADJUSTED_X, ADJUSTED_Y);
	if(Ok != status){
		VGCError("Could not render cached bitmap. " + VGCGDIPlus::getStatusDescription(status));
	}

	VGCAssert(invariant());	
}

/* Private accessors */
bool VGCSimpleImageImp::invariant() const{
	return 
		VGCImageImp::invariant() && 
		(0 != mGraphics) &&
		(0 != mBitmap) &&
		(0 != mCachedBitmap);
}

/* Private manipulators */
void VGCSimpleImageImp::update(){
	VGCAssert(mGraphics);
	VGCAssert(mBitmap);

	if(0 != mCachedBitmap){
		delete mCachedBitmap;
	}
	mCachedBitmap = new CachedBitmap(mBitmap, mGraphics);
	VGCAssert(mCachedBitmap);
	Status status = mCachedBitmap->GetLastStatus();
	if(Ok != status){
		VGCError("Could not create cached bitmap. " + VGCGDIPlus::getStatusDescription(status));
	}
}



/* VGCComplexImageImp */

/* Public creators */
VGCComplexImageImp::VGCComplexImageImp(
	Graphics *graphics,
	const std::string &filename, 
	int xFrameCount, 
	int yFrameCount) :
	mXFrameCount(xFrameCount),
	mYFrameCount(yFrameCount){

	VGCAssert(fInvariant());
	VGCAssert(graphics);
	VGCAssert(0 < mXFrameCount);
	VGCAssert(0 < mYFrameCount);

	Bitmap bitmap(VGCGDIPlus::translateString(filename).c_str(), FALSE);
	Status status = bitmap.GetLastStatus();
	if(Ok != status){
		VGCError("Could not create bitmap. " + VGCGDIPlus::getStatusDescription(status));
	}
	const int BITMAP_WIDTH  = bitmap.GetWidth();
	const int BITMAP_HEIGHT = bitmap.GetHeight();
	VGCAssert(0 == (BITMAP_WIDTH % mXFrameCount));
	VGCAssert(0 == (BITMAP_HEIGHT % mYFrameCount));
	const int SUB_BITMAP_WIDTH  = (BITMAP_WIDTH / mXFrameCount);
	const int SUB_BITMAP_HEIGHT = (BITMAP_HEIGHT / mYFrameCount);
	for(int yFrameIndex = 0; yFrameIndex < mYFrameCount; yFrameIndex++){
		for(int xFrameIndex = 0; xFrameIndex < mXFrameCount; xFrameIndex++){
			const int          SUB_X        = (xFrameIndex * SUB_BITMAP_WIDTH);
			const int          SUB_Y        = (yFrameIndex * SUB_BITMAP_HEIGHT);
			const VGCRectangle subRectangle = VGCRectangle(
				VGCVector(SUB_X, SUB_Y), 
				SUB_BITMAP_WIDTH, 
				SUB_BITMAP_HEIGHT); 
			VGCSimpleImageImp *subBitmap = new VGCSimpleImageImp(graphics, &bitmap, subRectangle);
			VGCAssert(subBitmap);
			mSimpleImageImpVector.push_back(subBitmap);
		}
	}

	VGCAssert(invariant());
}

VGCComplexImageImp::~VGCComplexImageImp(){
	VGCAssert(invariant());
	
	while(!mSimpleImageImpVector.empty()){
		VGCSimpleImageImp *simpleImageImp = mSimpleImageImpVector.back();
		VGCAssert(simpleImageImp);
		delete simpleImageImp;
		mSimpleImageImpVector.pop_back();
	}
	mXFrameCount = -1;
	mYFrameCount = -1;

	VGCAssert(!invariant());
}

/* Public accessors */
Graphics* VGCComplexImageImp::getGraphics() const{
	VGCAssert(invariant());	

	return mSimpleImageImpVector[0]->getGraphics();
}

int VGCComplexImageImp::getHeight() const{
	VGCAssert(invariant());

	return mSimpleImageImpVector[0]->getHeight();
}

int VGCComplexImageImp::getWidth() const{
	VGCAssert(invariant());

	return mSimpleImageImpVector[0]->getWidth();
}

int VGCComplexImageImp::getXFrameCount() const{
	VGCAssert(invariant());

	return mXFrameCount;
}

int VGCComplexImageImp::getYFrameCount() const{
	VGCAssert(invariant());

	return mYFrameCount;
}

void VGCComplexImageImp::render(
	const VGCVector &frameIndex, 
	const VGCVector &position,
	const VGCAdjustment &adjustment) const{

	VGCAssert(invariant());
	
	VGCSimpleImageImp *simpleImageImp = getFrame(frameIndex);
	simpleImageImp->render(VGCVector(0, 0), position, adjustment);

	VGCAssert(invariant());
}

/* Private accessors */
VGCSimpleImageImp* VGCComplexImageImp::getFrame(const VGCVector &frameIndex) const{
	const int FRAME_INDEX = ((mXFrameCount * frameIndex.getY()) + frameIndex.getX());
	VGCAssert((0 <= FRAME_INDEX) && (FRAME_INDEX < int(mSimpleImageImpVector.size())));
	VGCSimpleImageImp *simpleImageImp = mSimpleImageImpVector[FRAME_INDEX];
	VGCAssert(simpleImageImp);
	return simpleImageImp;
}

bool VGCComplexImageImp::invariant() const{
	return 
		VGCImageImp::invariant() &&
		(0 < mXFrameCount) &&
		(0 < mYFrameCount) &&
		((mXFrameCount * mYFrameCount) == int(mSimpleImageImpVector.size()));
}
