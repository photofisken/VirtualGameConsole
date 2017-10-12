#ifndef INCLUDED_VGCVECTOR
#define INCLUDED_VGCVECTOR



/******************************************************************************

This component implements at (2D) vector type.  

*******************************************************************************/



class VGCVector{
public:

	/* Public creators */
	VGCVector() :
		mX(0),
		mY(0){			  
	}

	VGCVector(int x, int y) :	
		mX(x),
		mY(y){			
	}

	VGCVector(const VGCVector &vector) :
		mX(vector.mX),
		mY(vector.mY){
	}

	~VGCVector(){
		mX = 0;
		mY = 0;
	}

	/* Public manipulators */
	VGCVector& operator=(const VGCVector &vector){
		mX = vector.mX;
		mY = vector.mY;
		return *this;
	}

	VGCVector& operator+=(const VGCVector &vector){
		mX += vector.mX;
		mY += vector.mY;
		return *this;
	}

	VGCVector& operator-=(const VGCVector &vector){
		mX -= vector.mX;
		mY -= vector.mY;
		return *this;
	}

	VGCVector& operator*=(int scalar){
		mX *= scalar;
		mY *= scalar;
		return *this;
	}

	void setX(int x){
		mX = x;
	}

	void setY(int y){
		mY = y;
	}

	/* Public accessors */
	int getX() const{
		return mX;
	}

	int getY() const{
		return mY;
	}

private:

	/* Private data */
	int mX;
	int mY;
};

inline VGCVector operator+(const VGCVector &vector0, const VGCVector &vector1){
	return VGCVector(vector0.getX() + vector1.getX(), vector0.getY() + vector1.getY());
}

inline VGCVector operator-(const VGCVector &vector0, const VGCVector &vector1){
	return VGCVector(vector0.getX() - vector1.getX(), vector0.getY() - vector1.getY());
}

inline VGCVector operator*(const VGCVector &vector, int scalar){
	return VGCVector(vector.getX() * scalar, vector.getY() * scalar);
}

inline VGCVector operator*(int scalar, const VGCVector &vector){
	return VGCVector(vector.getX() * scalar, vector.getY() * scalar);
}

inline int operator*(const VGCVector &vector0, const VGCVector &vector1){
	return ((vector0.getX() * vector1.getX()) + (vector0.getY() * vector1.getY()));
}

inline bool operator==(const VGCVector &vector0, const VGCVector &vector1){
	return ((vector0.getX() == vector1.getX()) && (vector0.getY() == vector1.getY()));
}

inline bool operator!=(const VGCVector &vector0, const VGCVector &vector1){
	return ((vector0.getX() != vector1.getX()) || (vector0.getY() != vector1.getY()));
}

#endif