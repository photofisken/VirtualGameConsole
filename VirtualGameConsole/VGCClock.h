#ifndef INCLUDED_VGCCLOCK
#define INCLUDED_VGCCLOCK



/******************************************************************************

This component implements clock and timer functions. The clock measures the 
time (in seconds) that has passed since the component was initialized.

*******************************************************************************/



#include <set>



class VGCTimerImp;



class VGCTimer{
public:

	/* Friends */
	friend struct VGCClock;
	friend bool operator==(const VGCTimer &timer0, const VGCTimer &timer1);
	friend bool operator!=(const VGCTimer &timer0, const VGCTimer &timer1);

	/* Public creators */
	VGCTimer() :
		mTimerImp(0){
	}

	VGCTimer(const VGCTimer &timer) :
		mTimerImp(timer.mTimerImp){
	}	

	~VGCTimer(){
		mTimerImp = 0;
	}

	/* Public manipulators */
	VGCTimer& operator=(const VGCTimer &timer){
		mTimerImp = timer.mTimerImp;
		return *this;
	}

private:
	
	/* Private creators */
	VGCTimer(VGCTimerImp *timerImp) :
	   mTimerImp(timerImp){
	}

	/* Private manipulators */
	void setTimerImp(VGCTimerImp *timerImp){
		mTimerImp = timerImp;
	}

	/* Private accessors */
	VGCTimerImp* getTimerImp() const{
		return mTimerImp;
	}

	/* Private data */
	VGCTimerImp *mTimerImp;
};

inline bool operator==(const VGCTimer &timer0, const VGCTimer &timer1){
	return (timer0.getTimerImp() == timer1.getTimerImp());
}

inline bool operator!=(const VGCTimer &timer0, const VGCTimer &timer1){
	return (timer0.getTimerImp() != timer1.getTimerImp());
}



struct VGCClock{

	/* Public types */
	typedef std::set<VGCTimerImp*> TimerImpSet;

	/* Public functions */
	static void     closeTimer(const VGCTimer &timer);
	static void     finalizeClock();
	static double   getTime();
	static double   getTime(const VGCTimer &timer);
	static double   getTimeout(const VGCTimer &timer);
	static void     initializeClock();
	static bool     isExpired(const VGCTimer &timer);
	static VGCTimer openTimer(double timeout);
	static void     reset(const VGCTimer &timer);
	static void     setTimeout(const VGCTimer &timer, double timeout);
	static void     wait(double timeout);
	static void     wait(const VGCTimer &timer);
};


#endif