#ifndef INCLUDED_VGCDISPLAY
#define INCLUDED_VGCDISPLAY



/******************************************************************************

This component implements a type that represents a display device. Functions 
are available for rendering various objects onto the display. Before drawing,
clients must call beginFrame. When rendering is done, clients must call
endFrame. 

*******************************************************************************/



#include "VGCVector.h"
#include "VGCRectangle.h"
#include "VGCColor.h"
#include "VGCAdjustment.h"
#include <string>
#include <set>



class VGCImageImp;
class VGCFontImp;



class VGCImage{
public:

	/* Friends */
	friend struct VGCDisplay;
	friend bool operator==(const VGCImage &image0, const VGCImage &image1);
	friend bool operator!=(const VGCImage &image0, const VGCImage &image1);

	/* Public creators */
	VGCImage() :
		mImageImp(0){
	}

	VGCImage(const VGCImage &image) :
		mImageImp(image.mImageImp){
	}	

	~VGCImage(){
		mImageImp = 0;
	}

	/* Public manipulators */
	VGCImage& operator=(const VGCImage &image){
		mImageImp = image.mImageImp;
		return *this;
	}

private:
	
	/* Private creators */
	VGCImage(VGCImageImp *imageImp) :
	   mImageImp(imageImp){
	}

	/* Private manipulators */
	void setImageImp(VGCImageImp *imageImp){
		mImageImp = imageImp;
	}

	/* Private accessors */
	VGCImageImp* getImageImp() const{
		return mImageImp;
	}

	/* Private data */
	VGCImageImp *mImageImp;
};

inline bool operator==(const VGCImage &image0, const VGCImage &image1){
	return (image0.getImageImp() == image1.getImageImp());
}

inline bool operator!=(const VGCImage &image0, const VGCImage &image1){
	return (image0.getImageImp() != image1.getImageImp());
}



class VGCFont{
public:

	/* Friends */
	friend struct VGCDisplay;
	friend bool operator==(const VGCFont &font0, const VGCFont &font1);
	friend bool operator!=(const VGCFont &font0, const VGCFont &font1);

	/* Public creators */
	VGCFont() :
		mFontImp(0){
	}

	VGCFont(const VGCFont &font) :
		mFontImp(font.mFontImp){
	}

	~VGCFont(){
		mFontImp = 0;	
	}

	/* Public manipulators */
	VGCFont& operator=(const VGCFont &font){
		mFontImp = font.mFontImp;
		return *this;
	}

private:
	
	/* Private creators */
	VGCFont(VGCFontImp *fontImp) :
	   mFontImp(fontImp){
	}

	/* Private manipulators */
	void setFontImp(VGCFontImp *fontImp){
		mFontImp = fontImp;   
	}

	/* Private accessors */
	VGCFontImp* getFontImp() const{
		return mFontImp;
	}

	/* Private data */
	VGCFontImp *mFontImp;
};

inline bool operator==(const VGCFont &font0, const VGCFont &font1){
	return (font0.getFontImp() == font1.getFontImp());
}

inline bool operator!=(const VGCFont &font0, const VGCFont &font1){
	return (font0.getFontImp() != font1.getFontImp());
}



struct VGCDisplay{

	/* Public types */
	typedef std::set<VGCImageImp*> ImageImpSet;
	typedef std::set<VGCFontImp*>  FontImpSet;

	/* Public functions */
	static bool                beginFrame();
	static void                clear(const VGCColor &color);
	static void                closeFont(const VGCFont &font);
	static void                closeImage(const VGCImage &image);
	static void                endFrame();
	static void                finalizeDisplay();
	static const VGCRectangle& getClipRectangle();
	static int                 getHeight();
	static int                 getHeight(const VGCImage &image);
	static int                 getWidth();
	static int                 getWidth(const VGCImage &image);
	static void                initializeDisplay(const std::string &applicationName,
                                                 int displayWidth,
                                                 int displayHeight);
	static VGCFont             openFont(const std::string &name, int size);
	static VGCImage            openImage(const std::string &filename, int xFrameCount, int yFrameCount);
	static void                renderEllipse(const VGCRectangle &rectangle, 
                                             const VGCColor &color, 
                                             const VGCAdjustment &adjustment, 
                                             bool fill);
	static void                renderImage(const VGCImage &image,
		                                   const VGCVector &frameIndex,
                                           const VGCVector &position,
                                           const VGCAdjustment &adjustment);
	static void                renderLine(const VGCColor &color,
                                          const VGCVector &from, 
		                                  const VGCVector &to);
	static void                renderPoint(const VGCColor &color, const VGCVector &position);
	static void                renderRectangle(const VGCRectangle &rectangle, 
                                               const VGCColor &color, 
                                               const VGCAdjustment &adjustment, 
											   bool fill);
	static void                renderString(const VGCFont &font,
                                            const std::string &string, 
                                            const VGCColor &color, 
                                            const VGCVector &position, 
                                            const VGCAdjustment &adjustment);
	static void                setClipRectangle(const VGCRectangle &clipRectangle);
};

#endif