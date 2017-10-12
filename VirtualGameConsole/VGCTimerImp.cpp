#include "VGCTimerImp.h"
#include "VGCAssert.h"
#include <windows.h>



/* File scope data */
static int    fInitializeMinusFinalizeCount = 0;
static double fTicksPerSecond               = 0.0;
static double fOrigo                        = 0.0;


/* File scope functions */
static bool fInvariant(){
	return 
		(0 < fInitializeMinusFinalizeCount) &&
		(0.0 < fTicksPerSecond);
}

static double fGetTime(){
	VGCAssert(0.0 < fTicksPerSecond);

	LARGE_INTEGER tickCount;
	BOOL          result = QueryPerformanceCounter(&tickCount);
	VGCAssert(result && "Win32 performance counter read successfully.");
	const double  TIME   = ((double(tickCount.QuadPart) / fTicksPerSecond) - fOrigo);
	VGCAssert(0.0 < TIME);
	return TIME;
}

static void fWait(double time){
	if(0.0 < time){
		const double CURRENT_TIME               = fGetTime();
		const double WAKEUP_TIME                = (CURRENT_TIME + time);
		const int    SLEEP_TIME_IN_MILLISECONDS = int(time * 1000.0);
		if(0 < SLEEP_TIME_IN_MILLISECONDS){
			Sleep(DWORD(SLEEP_TIME_IN_MILLISECONDS)); /* Avoid 0 for argument -> give up rest of timeslice...*/
		}
		while(fGetTime() < WAKEUP_TIME);  /* Busy wait possible remaining time */
	}
}


/* VGCTimerImp */
	
/* Public creators */
VGCTimerImp::VGCTimerImp(double timeout) :
	mOrigo(0.0),
	mTimeout(timeout){
	
	VGCAssert(fInvariant());
	VGCAssert(0.0 <= timeout);

	mOrigo = fGetTime();

	VGCAssert(invariant());
}

VGCTimerImp::~VGCTimerImp(){
	VGCAssert(invariant());

	mTimeout = -1.0;

	VGCAssert(!invariant());
}

/* Public manipulators */
void VGCTimerImp::reset(){
	VGCAssert(invariant());

	mOrigo = fGetTime();

	VGCAssert(invariant());
}

void VGCTimerImp::setTimeout(double timeout){
	VGCAssert(invariant());
	VGCAssert(0.0 <= timeout);

	mTimeout = timeout;

	VGCAssert(invariant());
}

/* Public accessors */
double VGCTimerImp::getTime() const{
	VGCAssert(invariant());

	const double TIME = (fGetTime() - mOrigo);
	VGCAssert(0.0 <= TIME);
	return TIME;
}

double VGCTimerImp::getTimeout() const{
	VGCAssert(invariant());

	return mTimeout;
}

bool VGCTimerImp::isExpired() const{
	VGCAssert(invariant());

	const bool isExpired =
		(0.0 == mTimeout) ?
		(true) :
		((mOrigo + mTimeout) <= fGetTime());
	return isExpired;
}

void VGCTimerImp::wait() const{
	VGCAssert(invariant());

	const double WAIT_TIME = ((mOrigo + mTimeout) - fGetTime());
	fWait(WAIT_TIME);
}

/* Public functions */
void VGCTimerImp::finalizeTimerImp(){
	VGCAssert(fInvariant());

	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		fTicksPerSecond = 0.0;
		fOrigo          = 0.0;
	}
}

double VGCTimerImp::getGlobalTime(){
	VGCAssert(fInvariant());

	return fGetTime();
}

void VGCTimerImp::initializeTimerImp(){
	if(0 == fInitializeMinusFinalizeCount){
		LARGE_INTEGER ticksPerSecond;
		BOOL result     = QueryPerformanceFrequency(&ticksPerSecond);
		VGCAssert(result && "System has a high performance counter.");
		fTicksPerSecond = double(ticksPerSecond.QuadPart);
	
		LARGE_INTEGER tickCount;
		result = QueryPerformanceCounter(&tickCount);
		VGCAssert(result && "Win32 performance counter read successfully.");
		fOrigo = (double(tickCount.QuadPart) / fTicksPerSecond);		
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

void VGCTimerImp::wait(double time){
	VGCAssert(fInvariant());

	fWait(time);

	VGCAssert(fInvariant());
}


/* Private accessors */
bool VGCTimerImp::invariant() const{
	return
		(fInvariant()) &&
		(0.0 <= mOrigo) &&
		(0.0 <= mTimeout);
}
