#ifndef INCLUDED_VGCCOLOR
#define INCLUDED_VGCCOLOR



/******************************************************************************

This component implements a color type that represent a color using alpha, red,
green and blue components. Each component belongs to the range [0, 255].

*******************************************************************************/



class VGCColor{
public:
	
	/* Public creators */
	VGCColor() :
		mAlpha(0),
		mRed(0),
		mGreen(0),
		mBlue(0){
	}

	VGCColor(const VGCColor &color) :
		mAlpha(color.mAlpha),
		mRed(color.mRed),
		mGreen(color.mGreen),
		mBlue(color.mBlue){
	}

	VGCColor(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue) :
		mAlpha(alpha),
		mRed(red),
		mGreen(green),
		mBlue(blue){	
	}

	~VGCColor(){
		mAlpha = 0;
		mRed   = 0;
		mGreen = 0;
		mBlue  = 0;
	}

	/* Public manipulators */
	VGCColor& operator=(const VGCColor &color){
		mAlpha = color.mAlpha;
		mRed   = color.mRed;
		mGreen = color.mGreen;
		mBlue  = color.mBlue;
		return *this;
	}

	void setAlpha(unsigned char alpha){
		mAlpha = alpha;
	}

	void setBlue(unsigned char blue){
		mBlue = blue;
	}

	void setGreen(unsigned char green){
		mGreen = green;
	}

	void setRed(unsigned char red){
		mRed = red;
	}

	/* Public accessors */
	unsigned char getAlpha() const{
		return mAlpha;
	}

	unsigned char getBlue() const{
		return mBlue;
	}

	unsigned char getGreen() const{
		return mGreen;
	}

	unsigned char getRed() const{
		return mRed;
	}

private:

	/* Private data */
	unsigned char mAlpha;
	unsigned char mRed;
	unsigned char mGreen;
	unsigned char mBlue;
};

inline bool operator==(const VGCColor &color0, const VGCColor &color1){
	return 
		(color0.getAlpha() == color1.getAlpha()) &&
		(color0.getRed() == color1.getRed()) &&
		(color0.getGreen() == color1.getGreen()) &&
		(color0.getBlue() == color1.getBlue());
}

inline bool operator!=(const VGCColor &color0, const VGCColor &color1){
	return !(color0 == color1);
}

#endif