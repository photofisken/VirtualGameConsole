#ifndef INCLUDED_VGCTIMERIMP
#define INCLUDED_VGCTIMERIMP



/******************************************************************************

This component implements a timer type used to measure time (either since 
creation or a previous reset). Further, this type provides a function for
retrieving the global time (time since initialization).

*******************************************************************************/



class VGCTimerImp{
public:
	
	/* Public creators */
	VGCTimerImp(double timeout);
	~VGCTimerImp();

	/* Public manipulators */
	void reset();
	void setTimeout(double timeout);

	/* Public accessors */
	double getTime()    const;
	double getTimeout() const;
	bool   isExpired()  const;
	void   wait()       const;

	/* Public functions */
	static void   finalizeTimerImp();
	static double getGlobalTime();
	static void   initializeTimerImp();
	static void   wait(double time);

private:

	/* Private creators */
	VGCTimerImp(const VGCTimerImp &timerImp);

	/* Private manipulators */
	VGCTimerImp& operator=(const VGCTimerImp &timerImp);

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	double mOrigo;
	double mTimeout;
};

#endif