#include "VGCVectorTest.h"
#include "VGCAssert.h"
#include "VGCVector.h"


/* VGCVectorTest */

/* Public functions */
void VGCVectorTest::run(){
	VGCVector v0;
	VGCAssert(0 == v0.getX());
	VGCAssert(0 == v0.getY());
	v0.setX(1);
	VGCAssert(1 == v0.getX());
	v0.setY(2);
	VGCAssert(2 == v0.getY());

	VGCVector v1(1, 2);
	VGCAssert(1 == v1.getX());
	VGCAssert(2 == v1.getY());

	VGCVector v2(v1);
	VGCAssert(1 == v2.getX());
	VGCAssert(2 == v2.getY());

	VGCVector v3;
	v3 = v2;
	VGCAssert(1 == v3.getX());
	VGCAssert(2 == v3.getY());

	VGCVector va0(0, 0);
	VGCVector va1(0, 0);
	VGCVector vb0(0, 1);
	VGCVector vb1(0, 1);
	VGCVector vc0(1, 0);
	VGCVector vc1(1, 0);
	VGCVector vd0(1, 1);
	VGCVector vd1(1, 1);
	VGCAssert(va0 == va1);
	VGCAssert(vb0 == vb1);
	VGCAssert(vc0 == vc1);
	VGCAssert(vd0 == vd1);
	VGCAssert(va0 != vb0);
	VGCAssert(va0 != vc0);
	VGCAssert(va0 != vd0);

	v0 = VGCVector(1, 2);
	v0 += VGCVector(3, 4);
	VGCAssert(v0 == VGCVector(4, 6));

	v0 = VGCVector(1, 1);
	v0 -= VGCVector(3, 4);
	VGCAssert(v0 == VGCVector(-2, -3));

	v0 = VGCVector(1, 2);
	v0 *= 2;
	VGCAssert(v0 == VGCVector(2, 4));

	VGCAssert(VGCVector(2, 4) == VGCVector(1, 2) + VGCVector(1, 2));
	VGCAssert(VGCVector(0, 1) == VGCVector(1, 3) - VGCVector(1, 2));
	VGCAssert(11 == VGCVector(1, 2) * VGCVector(3, 4));
	VGCAssert(VGCVector(2, 4) == VGCVector(1, 2) * 2);
	VGCAssert(VGCVector(2, 4) == 2 * VGCVector(1, 2));
}


