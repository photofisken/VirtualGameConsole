#include "VGCTimerImpTest.h"
#include "VGCAssert.h"
#include "VGCTimerImp.h"

#include <iostream>


static bool fEqual(double d0, double d1){
	const double TOLERANCE = 0.01;
	const double DELTA     = (d0 < d1) ? (d1 - d0) : (d0 - d1);
	return (DELTA < TOLERANCE);
}



/* VGCTimerImpTest */

/* Public functions */
void VGCTimerImpTest::run(){
	VGCTimerImp::initializeTimerImp();
	VGCTimerImp::initializeTimerImp();

	VGCAssert((0.0 < VGCTimerImp::getGlobalTime()) && (VGCTimerImp::getGlobalTime() < 0.5));
	VGCTimerImp::wait(1.0);

	VGCTimerImp *timerImp = new VGCTimerImp(0.0);
	VGCAssert((0.0 < timerImp->getTime()) && (timerImp->getTime() < 0.5));
	VGCAssert(timerImp->isExpired());
	VGCAssert(0.0 == timerImp->getTimeout());
	timerImp->setTimeout(5.0);
	VGCAssert(5.0 == timerImp->getTimeout());
	VGCAssert(!timerImp->isExpired());

	const double TIMEOUT = 2.0;
	timerImp->setTimeout(TIMEOUT);
	const double START_TIME = VGCTimerImp::getGlobalTime();
	timerImp->reset();
	timerImp->wait();
	const double END_TIME         = VGCTimerImp::getGlobalTime();
	const double DELTA            = (END_TIME - START_TIME);
	const double ERROR_DIFFERENCE = (DELTA - TIMEOUT);
	VGCAssert(0.0 < DELTA);
	VGCAssert(TIMEOUT <= DELTA);
	VGCAssert(ERROR_DIFFERENCE < 0.1);

	VGCTimerImp::finalizeTimerImp();
	VGCTimerImp::finalizeTimerImp();

	VGCTimerImp::initializeTimerImp();
	VGCTimerImp::finalizeTimerImp();
}

