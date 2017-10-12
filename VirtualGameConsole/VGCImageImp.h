#ifndef INCLUDED_VGCIMAGEIMP
#define INCLUDED_VGCIMAGEIMP



/******************************************************************************

This component implements image types. Simple surfaces have only a single frame 
whereas complex surfaces consist of several frames (e.g. useful for animation).

*******************************************************************************/



#include "VGCAdjustment.h"
#include "VGCVector.h"
#include "VGCRectangle.h"
#include "VGCReferenced.h"
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <vector>



class VGCImageImp : public VGCReferenced{
public:

	/* Public creators */
	VGCImageImp();
	virtual ~VGCImageImp();

	/* Public accessors */
	virtual Gdiplus::Graphics* getGraphics()           const = 0;
	virtual int                getHeight()             const = 0;
	virtual int                getWidth()              const = 0;
	virtual int                getXFrameCount()        const = 0;
	virtual int                getYFrameCount()        const = 0;
	virtual void               render(
		const VGCVector &frameIndex, 
		const VGCVector &position,
		const VGCAdjustment &adjustment)               const = 0;

	/* Public functions */
	static void finalizeImageImp();
	static void initializeImageImp();

protected:

	/* Protected accessors */
	bool invariant() const;

private:

	/* Private creators */
	VGCImageImp(const VGCImageImp &imageImp);

	/* Private manipulators */
	VGCImageImp& operator=(const VGCImageImp &imageImp);
};



class VGCSimpleImageImp : public VGCImageImp{
public:

	/* Public creators */
	VGCSimpleImageImp(Gdiplus::Graphics *graphics, const std::string &filename);
	VGCSimpleImageImp(Gdiplus::Graphics *graphics, Gdiplus::Bitmap *bitmap, const VGCRectangle &rectangle);
	virtual ~VGCSimpleImageImp();

	/* Public accessors */
	virtual Gdiplus::Graphics* getGraphics()           const;
	virtual int                getHeight()             const;
	virtual int                getWidth()              const;
	virtual int                getXFrameCount()        const;
	virtual int                getYFrameCount()        const;
	virtual void               render(
		const VGCVector &frameIndex, 
		const VGCVector &position,
		const VGCAdjustment &adjustment)               const;

private:

	/* Private creators */
	VGCSimpleImageImp(const VGCSimpleImageImp &simpleImageImp);

	/* Private accessors */
	bool invariant() const;

	/* Private manipulators */
	VGCSimpleImageImp& operator=(const VGCSimpleImageImp &simpleImageImp);
	void               update();

	/* Private data */
	Gdiplus::Graphics     *mGraphics;
	Gdiplus::Bitmap       *mBitmap;
	Gdiplus::CachedBitmap *mCachedBitmap;
};



class VGCComplexImageImp : public VGCImageImp{
public:

	/* Public types */
	typedef std::vector<VGCSimpleImageImp*> SimpleImageImpVector;

	/* Public creators */
	VGCComplexImageImp(
		Gdiplus::Graphics *graphics,
		const std::string &filename, 
		int xFrameCount, 
		int yFrameCount);
	virtual ~VGCComplexImageImp();

	/* Public accessors */
	virtual Gdiplus::Graphics* getGraphics()    const;
	virtual int                getHeight()      const;
	virtual int                getWidth()       const;
	virtual int                getXFrameCount() const;
	virtual int                getYFrameCount() const;
	virtual void               render(
		const VGCVector &frameIndex, 
		const VGCVector &position,
		const VGCAdjustment &adjustment)        const;

private:

	/* Private creators */
	VGCComplexImageImp(const VGCComplexImageImp &complexImageImp);

	/* Private accessors */
	VGCSimpleImageImp* getFrame(const VGCVector &frameIndex) const;
	bool               invariant()                           const;

	/* Private manipulators */
	VGCComplexImageImp& operator=(const VGCComplexImageImp &complexImageImp);

	/* Private data */
	int                  mXFrameCount;
	int                  mYFrameCount;
	SimpleImageImpVector mSimpleImageImpVector;
};

#endif
