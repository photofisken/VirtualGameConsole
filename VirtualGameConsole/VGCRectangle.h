#ifndef INCLUDED_VGCRECTANGLE
#define INCLUDED_VGCRECTANGLE



/******************************************************************************

This component implements a discrete rectangle type. Each rectangle has a 
position, width and height. The position constitute the upper left corner of
the rectangle.

*******************************************************************************/



#include "VGCVector.h"
#include "VGCAssert.h"


class VGCRectangle{
public:

	/* Public creators */
	VGCRectangle() :
		mPosition(VGCVector(0, 0)),
		mWidth(0),
		mHeight(0){
		
		VGCAssert(invariant());
	}

	VGCRectangle(const VGCRectangle &rectangle) :
		mPosition(rectangle.mPosition),
		mWidth(rectangle.mWidth),
		mHeight(rectangle.mHeight){
			
		VGCAssert(invariant());
	}

	VGCRectangle(const VGCVector &position, int width, int height) :
		mPosition(position),
		mWidth(width),
		mHeight(height){
		VGCAssert(0 <= width);	
		VGCAssert(0 <= height);	
	
		VGCAssert(invariant());
	}

	~VGCRectangle(){
		VGCAssert(invariant());
		
		mWidth  = -1;
		mHeight = -1;

		VGCAssert(!invariant());
	}

	/* Public manipulators */
	VGCRectangle& operator=(const VGCRectangle &rectangle){
		VGCAssert(invariant());

		mPosition = rectangle.mPosition;
		mWidth    = rectangle.mWidth;
		mHeight   = rectangle.mHeight;

		VGCAssert(invariant());

		return *this;
	}

	void setHeight(int height){
		VGCAssert(invariant());
		VGCAssert(0 <= height);

		mHeight = height;

		VGCAssert(invariant());
	}

	void setPosition(const VGCVector &position){
		VGCAssert(invariant());

		mPosition = position;

		VGCAssert(invariant());
	}

	void setWidth(int width){
		VGCAssert(invariant());
		VGCAssert(0 <= width);

		mWidth = width;

		VGCAssert(invariant());
	}

	/* Public accessors */
	int getHeight() const{
		VGCAssert(invariant());

		return mHeight;
	}

	const VGCVector& getPosition() const{
		VGCAssert(invariant());

		return mPosition;
	}

	int getWidth() const{
		VGCAssert(invariant());

		return mWidth;
	}

	bool isInside(const VGCVector &position){
		VGCAssert(invariant());
	
		const int  X        = position.getX();
		const int  Y        = position.getY();
		const int  LEFT     = mPosition.getX();
		const int  RIGHT    = (mPosition.getX() + mWidth);
		const int  TOP      = mPosition.getY();
		const int  BOTTOM   = (mPosition.getY() + mHeight);
		return ((LEFT <= X) && (X < RIGHT) && (TOP <= Y) && (Y < BOTTOM));
	}

private:

	/* Private accessors */
	bool invariant() const{
		return ((0 <= mWidth) && (0 <= mHeight));
	}

	/* Private data */
	VGCVector mPosition;
	int       mWidth;
	int       mHeight;
};

inline bool operator==(const VGCRectangle &rectangle0, const VGCRectangle &rectangle1){
	return 
		(rectangle0.getPosition() == rectangle1.getPosition()) && 
		(rectangle0.getHeight() == rectangle1.getHeight()) && 
		(rectangle0.getWidth() == rectangle1.getWidth());
}

inline bool operator!=(const VGCRectangle &rectangle0, const VGCRectangle &rectangle1){
	return !(rectangle0 == rectangle1);
}

#endif