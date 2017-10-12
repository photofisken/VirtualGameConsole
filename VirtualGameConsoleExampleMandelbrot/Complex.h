#ifndef INCLUDED_COMPLEX
#define INCLUDED_COMPLEX



/******************************************************************************

This component implements a complex number type.

*******************************************************************************/



#include <cmath>



class Complex{
public:

	/* Public creators */
	Complex(double real = 0.0, double imag = 0.0) :
		mReal(real),
		mImag(imag){
	}

	Complex(const Complex &complex) :
		mReal(complex.mReal),
		mImag(complex.mImag){
	}

	~Complex(){
	}

	/* Public manipulators */
	Complex& operator=(const Complex &complex){
		mReal = complex.mReal;
		mImag = complex.mImag;
		return *this;
	}

	void setImag(double imag){
		mImag = imag;
	}

	void setReal(double real){
		mReal = real;
	}

	/* Public accessors */
	double getImag() const{
		return mImag;
	}

	double getReal() const{
		return mReal;
	}

private:

	/* Private data */
	double mReal;
	double mImag;
};

inline double abs(const Complex &complex){
	return std::sqrt((complex.getReal() * complex.getReal()) + (complex.getImag() * complex.getImag()));
}


inline bool operator==(const Complex &complex0, const Complex &complex1){
	return ((complex0.getReal() == complex1.getReal()) && (complex0.getImag() == complex1.getImag()));
}

inline bool   operator!=(const Complex &complex0, const Complex &complex1){
	return ((complex0.getReal() != complex1.getReal()) || (complex0.getImag() != complex1.getImag()));
}

inline Complex operator+(const Complex &complex0, const Complex &complex1){
	return Complex(complex0.getReal() + complex1.getReal(), complex0.getImag() + complex1.getImag());
}

inline Complex operator-(const Complex &complex0, const Complex &complex1){
	return Complex(complex0.getReal() - complex1.getReal(), complex0.getImag() - complex1.getImag());
}

inline Complex operator*(const Complex &complex0, const Complex &complex1){
	const double REAL = 
		(complex0.getReal() * complex1.getReal()) - 
		(complex0.getImag() * complex1.getImag());
	const double IMAG = 
		(complex0.getReal() * complex1.getImag()) + 
		(complex0.getImag() * complex1.getReal());
	return Complex(REAL, IMAG);
}

#endif