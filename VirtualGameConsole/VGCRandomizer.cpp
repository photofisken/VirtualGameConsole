#include "VGCRandomizer.h"
#include "VGCAssert.h"
#include <cstdlib>
#include <ctime>



/* File scope data */
static int fInitializeMinusFinalizeCount = 0;



/* File scope functions */
static bool fInvariant(){
	return (0 < fInitializeMinusFinalizeCount);
}

static double fFraction(){	
	double fraction = ((std::rand()) / double(RAND_MAX));
	if(fraction < 0.0){
		fraction = 0.0;
	}
	if(1.0 < fraction){
		fraction = 1.0;
	}
	VGCAssert((0.0 <= fraction) && (fraction <= 1.0));
	return fraction;
}


/* VGCRandomizer */

/* Public functions */
void VGCRandomizer::finalizeRandomizer(){
	VGCAssert(fInvariant());

	fInitializeMinusFinalizeCount--;
}

void VGCRandomizer::initializeRandomizer(){
	if(0 == fInitializeMinusFinalizeCount){
		unsigned int seed = (unsigned int)(std::time(NULL));
		std::srand(seed);
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

bool VGCRandomizer::getBool(double truthProbability){
	VGCAssert(fInvariant());
	VGCAssert((0.0 <= truthProbability) && (truthProbability <= 1.0));

	const double FRACTION = fFraction();	
	VGCAssert(fInvariant());
	return (FRACTION < truthProbability);
}

double VGCRandomizer::getDouble(double min, double max){
	VGCAssert(fInvariant());
	VGCAssert(min <= max);	

	const double FRACTION = fFraction();
	const double DELTA    = (max - min);
	double       real     = (min + (FRACTION * DELTA));
	if(real < min){
		real = min;
	}
	if(max < real){
		real = max;	
	}
	VGCAssert((min <= real) && (real <= max));
	VGCAssert(fInvariant());
	return real;
}

float  VGCRandomizer::getFloat(float min, float max){
	VGCAssert(fInvariant());
	VGCAssert(min <= max);	

	const double FRACTION = fFraction();
	const double DELTA    = (max - min);
	float        real     = float(min + (FRACTION * DELTA));
	if(real < min){
		real = min;
	}
	if(max < real){
		real = max;	
	}
	VGCAssert((min <= real) && (real <= max));
	VGCAssert(fInvariant());
	return real;
}

int VGCRandomizer::getInt(int min, int max){
	VGCAssert(fInvariant());
	VGCAssert(min <= max);

	const double FRACTION = fFraction();
	const double DELTA    = (max - min + 1);
	 int         integer  = int(min + (FRACTION * DELTA));
	if(integer < min){
		integer = min;
	}
	if(max < integer){
		integer = max;
	}
	VGCAssert((min <= integer) && (integer <= max));
	VGCAssert(fInvariant());
	return integer;
}
