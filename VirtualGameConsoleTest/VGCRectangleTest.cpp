#include "VGCRectangleTest.h"
#include "VGCAssert.h"
#include "VGCRectangle.h"



/* VGCRectangleTest */

/* Public functions */
void VGCRectangleTest::run(){
	VGCRectangle r0;
	VGCAssert(VGCVector(0, 0) == r0.getPosition());
	VGCAssert(0 == r0.getWidth());
	VGCAssert(0 == r0.getHeight());

	r0.setPosition(VGCVector(1, 2));
	VGCAssert(VGCVector(1, 2) == r0.getPosition());
	r0.setWidth(1);
	VGCAssert(1 == r0.getWidth());
	r0.setHeight(2);
	VGCAssert(2 == r0.getHeight());

	VGCRectangle r1(VGCVector(1, 2), 1, 2);
	VGCAssert(VGCVector(1, 2) == r1.getPosition());
	VGCAssert(1 == r1.getWidth());
	VGCAssert(2 == r1.getHeight());

	VGCRectangle r2(r1);
	VGCAssert(VGCVector(1, 2) == r2.getPosition());
	VGCAssert(1 == r2.getWidth());
	VGCAssert(2 == r2.getHeight());

	VGCRectangle r3;
	r3 = r2;
	VGCAssert(VGCVector(1, 2) == r3.getPosition());
	VGCAssert(1 == r3.getWidth());
	VGCAssert(2 == r3.getHeight());

	VGCRectangle r4(VGCVector(1, 2), 2, 3);
	VGCAssert(r4.isInside(VGCVector(1, 2)));
	VGCAssert(r4.isInside(VGCVector(2, 2)));
	VGCAssert(r4.isInside(VGCVector(1, 3)));
	VGCAssert(r4.isInside(VGCVector(2, 3)));
	VGCAssert(r4.isInside(VGCVector(1, 4)));
	VGCAssert(r4.isInside(VGCVector(2, 4)));
	VGCAssert(!r4.isInside(VGCVector(0, 3)));
	VGCAssert(!r4.isInside(VGCVector(2, 5)));


	VGCRectangle a0(VGCVector(0, 0), 0, 0);
	VGCRectangle a1(VGCVector(0, 0), 0, 1);
	VGCRectangle a2(VGCVector(0, 0), 1, 0);
	VGCRectangle a3(VGCVector(0, 1), 0, 0);
	VGCRectangle b0(VGCVector(0, 0), 0, 0);
	VGCRectangle b1(VGCVector(0, 0), 0, 1);
	VGCRectangle b2(VGCVector(0, 0), 1, 0);
	VGCRectangle b3(VGCVector(0, 1), 0, 0);
	VGCAssert(a0 == b0);
	VGCAssert(a1 == b1);
	VGCAssert(a2 == b2);
	VGCAssert(a3 == b3);
	VGCAssert(a0 != a1);
	VGCAssert(a0 != a2);
	VGCAssert(a0 != a3);
}

