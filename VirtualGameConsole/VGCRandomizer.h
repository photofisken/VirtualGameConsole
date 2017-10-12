#ifndef INCLUDED_VGCRANDOMIZER
#define INCLUDED_VGCRANDOMIZER



/******************************************************************************

This component implements various functions with pseudo random behavior.

*******************************************************************************/



struct VGCRandomizer{

	/* Public functions */
	static void   finalizeRandomizer();
	static void   initializeRandomizer();
	static bool   getBool(double truthProbability);
	static double getDouble(double min, double max);
	static float  getFloat(float min, float max);
	static int    getInt(int min, int max);
};

#endif