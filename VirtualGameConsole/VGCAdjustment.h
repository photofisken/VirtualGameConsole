#ifndef INCLUDED_VGCADJUSTMENT
#define INCLUDED_VGCADJUSTMENT



/******************************************************************************

This component implements types for adjustment. Adjustments are specified in
the range [0.0, 1.0]. Horizontally, for example, 0.0 represnts left adjustment,
0.5 represent center adjustment and 1.0 represents right adjustment. 

*******************************************************************************/



#include "VGCAssert.h"



class VGCFraction{
public:
	
	/* Public creators */
	VGCFraction(double fraction = 0.0) :
		mFraction(fraction){
		
		VGCAssert(invariant());
	}

	VGCFraction(const VGCFraction &fraction) :
	mFraction(fraction.mFraction){
	
		VGCAssert(invariant());
	}

	~VGCFraction(){
		VGCAssert(invariant());

		mFraction = -1.0;

		VGCAssert(!invariant());	
	}

	/* Public manipulators */
	VGCFraction& operator=(const VGCFraction &fraction){
		VGCAssert(invariant());
		
		mFraction = fraction.mFraction;

		VGCAssert(invariant());
		return *this;	
	}

	void setFraction(double fraction){
		VGCAssert(invariant());

		mFraction = fraction;

		VGCAssert(invariant());
	}
	
	/* Public accessors */
	int computeOffset(int count) const{
		VGCAssert(invariant());
		VGCAssert(0 <= count);
		
		int offset = 0;
		if(0 < count){
			offset = int(mFraction * double(count));
			if(offset == count){
				offset = count - 1;
			}
		}

		VGCAssert((0 <= offset) && (offset <= count));
		VGCAssert(invariant());
		return offset;
	}

	double getFraction() const{
		VGCAssert(invariant());

		return mFraction;
	}

private:

	/* Private accessors */
	bool invariant() const{
		return ((0.0 <= mFraction) && (mFraction <= 1.0));
	}

	/* Private data */
	double mFraction;
};

inline bool operator==(const VGCFraction &fraction0, const VGCFraction &fraction1){
	return (fraction0.getFraction() == fraction1.getFraction());
}

inline bool operator!=(const VGCFraction &fraction0, const VGCFraction &fraction1){
	return (fraction0.getFraction() != fraction1.getFraction());
}



class VGCAdjustment{
public:

	/* Public creators */
	VGCAdjustment(
		const VGCFraction &xAdjustment = VGCFraction(), 
		const VGCFraction &yAdjustment = VGCFraction()) :
		mXAdjustment(xAdjustment),
		mYAdjustment(yAdjustment){
	}

	VGCAdjustment(const VGCAdjustment &adjustment) :
		mXAdjustment(adjustment.mXAdjustment),
		mYAdjustment(adjustment.mYAdjustment){
	}

	~VGCAdjustment(){
	}

	/* Public manipulators */
	void setXAdjustment(const VGCFraction &xAdjustment){
		mXAdjustment = xAdjustment;
	}

	void setYAdjustment(const VGCFraction &yAdjustment){
		mYAdjustment = yAdjustment;
	}

	VGCAdjustment& operator=(const VGCAdjustment &adjustment){
		mXAdjustment = adjustment.mXAdjustment;
		mYAdjustment = adjustment.mYAdjustment;
		return *this;
	}

	/* Public accessors */
	const VGCFraction& getXAdjustment() const{
		return mXAdjustment;
	}

	const VGCFraction& getYAdjustment() const{
		return mYAdjustment;
	}

private:

	/* Private data */
	VGCFraction mXAdjustment;
	VGCFraction mYAdjustment;
};

inline bool operator==(const VGCAdjustment &adjustment0, const VGCAdjustment &adjustment1){
	return 
		(adjustment0.getXAdjustment() == adjustment1.getXAdjustment()) && 
		(adjustment0.getYAdjustment() == adjustment1.getYAdjustment()); 
}

inline bool operator!=(const VGCAdjustment &adjustment0, const VGCAdjustment &adjustment1){
	return 
		(adjustment0.getXAdjustment() != adjustment1.getXAdjustment()) || 
		(adjustment0.getYAdjustment() != adjustment1.getYAdjustment()); 
}

#endif