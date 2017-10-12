#include "VGCRandomizerTest.h"
#include "VGCAssert.h"
#include "VGCRandomizer.h"



static const int SAMPLE_COUNT = 1000000;



static bool fEqual(double d0, double d1){
	const double TOLERANCE = 0.01;
	const double DELTA     = (d0 < d1) ? (d1 - d0) : (d0 - d1);
	return (DELTA < TOLERANCE);
}

static void testGetBool(){
	const double PROBABILITY = 0.7;
	int          trueCount   = 0;
	for(int i = 0; i < SAMPLE_COUNT; i++){
		bool boolean = VGCRandomizer::getBool(PROBABILITY);
		if(boolean){
			trueCount++;
		}
	}
	const double ACTUAL_PROBABILITY = double(trueCount) / double(SAMPLE_COUNT);
	VGCAssert(fEqual(PROBABILITY, ACTUAL_PROBABILITY));
}

static void testGetDouble(){
	const double MIN = -2.0;
	const double MAX = 4.0;
	double       sum = 0.0;
	for(int i = 0; i < SAMPLE_COUNT; i++){
		sum += VGCRandomizer::getDouble(MIN, MAX);
	}
	const double AVERAGE = (sum / SAMPLE_COUNT);
	VGCAssert(fEqual(1.0, AVERAGE));
}

static void testGetFloat(){
	const float MIN = -2.0f;
	const float MAX = 4.0f;
	float       sum = 0.0f;
	for(int i = 0; i < SAMPLE_COUNT; i++){
		sum += VGCRandomizer::getFloat(MIN, MAX);
	}
	const double AVERAGE = (sum / SAMPLE_COUNT);
	VGCAssert(fEqual(1.0, AVERAGE));
}

static void testGetInteger(){
	const int MIN = -2;
	const int MAX = 4;
	int       sum = 0;
	for(int i = 0; i < SAMPLE_COUNT; i++){
		sum += VGCRandomizer::getInt(MIN, MAX);
	}
	const double AVERAGE = (sum / SAMPLE_COUNT);
	VGCAssert(fEqual(1.0, AVERAGE));
}



/* VGCRandomizerTest */

/* Public functions */
void VGCRandomizerTest::run(){
	VGCRandomizer::initializeRandomizer();
	VGCRandomizer::initializeRandomizer();
	
	testGetBool();
	testGetDouble();
	testGetFloat();
	testGetInteger();

	VGCRandomizer::finalizeRandomizer();
	VGCRandomizer::finalizeRandomizer();

	VGCRandomizer::initializeRandomizer();
	VGCRandomizer::finalizeRandomizer();
}


