#include "VGCClock.h"
#include "VGCAssert.h"
#include "VGCError.h"
#include "VGCTimerImp.h"
#include <set>
#include <strstream>



/* File scope data */
static int                   fInitializeMinusFinalizeCount = 0;
static VGCClock::TimerImpSet fOpenTimerImpSet              = VGCClock::TimerImpSet();



/* File scope functions */
static bool fInvariant(){
	return (0 < fInitializeMinusFinalizeCount);
}

static bool fTimerImpIsOpen(VGCTimerImp *timerImp){
	return (fOpenTimerImpSet.find(timerImp) != fOpenTimerImpSet.end());
}


/* VGCClock */

/* Public functions */
void VGCClock::closeTimer(const VGCTimer &timer){
	VGCAssert(fInvariant());
	VGCAssert(fTimerImpIsOpen(timer.getTimerImp()));
	
	VGCTimerImp *timerImp = timer.getTimerImp();
	fOpenTimerImpSet.erase(timerImp);
	delete timerImp;

	VGCAssert(!fTimerImpIsOpen(timerImp));
	VGCAssert(fInvariant());
}

void VGCClock::finalizeClock(){
	VGCAssert(fInvariant());

	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		if(!fOpenTimerImpSet.empty()){
			std::ostrstream description;
			description << "Could not finalize VGCClock. There are still ";
			description << int(fOpenTimerImpSet.size()) << " open timers.";
			description << '\0';
			VGCError(description.str());
		}
		
		VGCTimerImp::finalizeTimerImp();
	}
}

double VGCClock::getTime(){
	VGCAssert(fInvariant());

	return VGCTimerImp::getGlobalTime();
}

double VGCClock::getTime(const VGCTimer &timer){
	VGCAssert(fInvariant());
	VGCAssert(fTimerImpIsOpen(timer.getTimerImp()));
	
	VGCTimerImp *timerImp = timer.getTimerImp();
	return timerImp->getTime();
}

double VGCClock::getTimeout(const VGCTimer &timer){
	VGCAssert(fInvariant());
	VGCAssert(fTimerImpIsOpen(timer.getTimerImp()));

	VGCTimerImp *timerImp = timer.getTimerImp();
	return timerImp->getTimeout();
}

void VGCClock::initializeClock(){
	if(0 == fInitializeMinusFinalizeCount){
		VGCTimerImp::initializeTimerImp();
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

bool VGCClock::isExpired(const VGCTimer &timer){
	VGCAssert(fInvariant());
	VGCAssert(fTimerImpIsOpen(timer.getTimerImp()));

	VGCTimerImp *timerImp = timer.getTimerImp();
	return timerImp->isExpired();
}

VGCTimer VGCClock::openTimer(double timeout){
	VGCAssert(fInvariant());

	VGCTimerImp *timerImp = new VGCTimerImp(timeout);
	VGCAssert(timerImp);
	fOpenTimerImpSet.insert(timerImp);
	VGCTimer    timer(timerImp);
	VGCAssert(fTimerImpIsOpen(timer.getTimerImp()));

	return timer;
}

void VGCClock::reset(const VGCTimer &timer){
	VGCAssert(fInvariant());
	VGCAssert(fTimerImpIsOpen(timer.getTimerImp()));

	VGCTimerImp *timerImp = timer.getTimerImp();
	timerImp->reset();

	VGCAssert(fInvariant());
}

void VGCClock::setTimeout(const VGCTimer &timer, double timeout){
	VGCAssert(fInvariant());
	VGCAssert(fTimerImpIsOpen(timer.getTimerImp()));
	VGCAssert(0.0 <= timeout);

	VGCTimerImp *timerImp = timer.getTimerImp();
	timerImp->setTimeout(timeout);

	VGCAssert(fInvariant());
}

void VGCClock::wait(double timeout){
	VGCAssert(fInvariant());

	VGCTimerImp::wait(timeout);

	VGCAssert(fInvariant());
}

void VGCClock::wait(const VGCTimer &timer){
	VGCAssert(fInvariant());
	VGCAssert(fTimerImpIsOpen(timer.getTimerImp()));

	VGCTimerImp *timerImp = timer.getTimerImp();
	timerImp->wait();

	VGCAssert(fInvariant());
}
