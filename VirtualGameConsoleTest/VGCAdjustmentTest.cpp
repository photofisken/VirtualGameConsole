#include "VGCAdjustmentTest.h"
#include "VGCAssert.h"
#include "VGCAdjustment.h"



static void testVGCFraction(){
	VGCFraction f0;
	VGCAssert(0.0 == f0.getFraction());
	f0.setFraction(0.5);
	VGCAssert(0.5 == f0.getFraction());

	VGCFraction f1(0.5);
	VGCAssert(0.5 == f1.getFraction());

	VGCFraction f2(f1);
	VGCAssert(0.5 == f2.getFraction());

	VGCFraction f3;
	f3 = f2;
	VGCAssert(0.5 == f3.getFraction());

	VGCFraction f4;
	f4.setFraction(0.00);
	VGCAssert(0 == f4.computeOffset(0));
	VGCAssert(0 == f4.computeOffset(4));
	f4.setFraction(0.24);
	VGCAssert(0 == f4.computeOffset(0));
	VGCAssert(0 == f4.computeOffset(4));
	f4.setFraction(0.26);
	VGCAssert(0 == f4.computeOffset(0));
	VGCAssert(1 == f4.computeOffset(4));
	f4.setFraction(0.49);
	VGCAssert(0 == f4.computeOffset(0));
	VGCAssert(1 == f4.computeOffset(4));
	f4.setFraction(0.51);
	VGCAssert(0 == f4.computeOffset(0));
	VGCAssert(2 == f4.computeOffset(4));
	f4.setFraction(0.74);
	VGCAssert(0 == f4.computeOffset(0));
	VGCAssert(2 == f4.computeOffset(4));
	f4.setFraction(0.76);
	VGCAssert(0 == f4.computeOffset(0));
	VGCAssert(3 == f4.computeOffset(4));
	f4.setFraction(1.0);
	VGCAssert(0 == f4.computeOffset(0));
	VGCAssert(3 == f4.computeOffset(4));

	VGCFraction fa0(0.1);
	VGCFraction fa1(0.1);
	VGCFraction fb0(0.2);
	VGCFraction fb1(0.2);
	VGCAssert(fa0 == fa1);
	VGCAssert(fb0 == fb1);
	VGCAssert(fa0 != fb0);
}

static void testVGCAdjustment(){
	VGCAdjustment a0;
	VGCAssert(VGCFraction(0.0) == a0.getXAdjustment());
	VGCAssert(VGCFraction(0.0) == a0.getYAdjustment());
	a0.setXAdjustment(VGCFraction(0.1));
	VGCAssert(VGCFraction(0.1) == a0.getXAdjustment());
	a0.setYAdjustment(VGCFraction(0.2));
	VGCAssert(VGCFraction(0.2) == a0.getYAdjustment());

	VGCAdjustment a1(a0);
	VGCAssert(VGCFraction(0.1) == a1.getXAdjustment());
	VGCAssert(VGCFraction(0.2) == a1.getYAdjustment());

	VGCAdjustment a2;
	a2 = a1;
	VGCAssert(VGCFraction(0.1) == a2.getXAdjustment());
	VGCAssert(VGCFraction(0.2) == a2.getYAdjustment());

	VGCAdjustment a00(0.0, 0.0);
	VGCAdjustment a01(0.0, 1.0);
	VGCAdjustment a10(1.0, 0.0);
	VGCAdjustment a11(1.0, 1.0);
	VGCAdjustment b00(0.0, 0.0);
	VGCAdjustment b01(0.0, 1.0);
	VGCAdjustment b10(1.0, 0.0);
	VGCAdjustment b11(1.0, 1.0);
	VGCAssert(a00 == b00);
	VGCAssert(a01 == b01);
	VGCAssert(a10 == b10);
	VGCAssert(a11 == b11);
	VGCAssert(a00 != a01);
	VGCAssert(a00 != a10);
	VGCAssert(a00 != a11);
}



/* VGCAdjustmentTest */

/* Public functions */
void VGCAdjustmentTest::run(){
	testVGCFraction();
	testVGCAdjustment();
}

