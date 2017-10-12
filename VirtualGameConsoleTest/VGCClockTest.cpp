#include "VGCClockTest.h"
#include "VGCAssert.h"
#include "VGCClock.h"



static bool fEqual(double d0, double d1){
	const double TOLERANCE = 0.01;
	const double DELTA     = (d0 < d1) ? (d1 - d0) : (d0 - d1);
	return (DELTA < TOLERANCE);
}



/* VGCClockTest */

/* Public functions */
void VGCClockTest::run(){
	VGCClock::initializeClock();
	VGCClock::initializeClock();
	
	VGCAssert((0.0 < VGCClock::getTime()) && (VGCClock::getTime() < 0.5));
	VGCClock::wait(2.0);

	VGCTimer timer = VGCClock::openTimer(2.0);
	VGCAssert(0.0 < VGCClock::getTime(timer));
	VGCAssert(VGCClock::getTime(timer) < 0.5);
	VGCClock::setTimeout(timer, 2.0);
	VGCClock::reset(timer);
	VGCClock::wait(timer);

	VGCClock::closeTimer(timer);


	VGCClock::finalizeClock();
	VGCClock::finalizeClock();

	VGCClock::initializeClock();
	VGCClock::finalizeClock();
}

