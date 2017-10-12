#include "VGCColorTest.h"
#include "VGCAssert.h"
#include "VGCColor.h"



/* VGCColorTest */

/* Public functions */
void VGCColorTest::run(){
	VGCColor color0;
	VGCAssert(0 == color0.getAlpha());
	VGCAssert(0 == color0.getRed());
	VGCAssert(0 == color0.getGreen());
	VGCAssert(0 == color0.getBlue());

	VGCColor color1(1, 2, 3, 4);
	VGCAssert(1 == color1.getAlpha());
	VGCAssert(2 == color1.getRed());
	VGCAssert(3 == color1.getGreen());
	VGCAssert(4 == color1.getBlue());

	VGCColor color2(color1);
	VGCAssert(1 == color2.getAlpha());
	VGCAssert(2 == color2.getRed());
	VGCAssert(3 == color2.getGreen());
	VGCAssert(4 == color2.getBlue());

	VGCColor color3;
	color3 = color2;
	VGCAssert(1 == color3.getAlpha());
	VGCAssert(2 == color3.getRed());
	VGCAssert(3 == color3.getGreen());
	VGCAssert(4 == color3.getBlue());
	
	VGCColor color4;
	color4.setAlpha(1);
	color4.setRed(2);
	color4.setGreen(3);
	color4.setBlue(4);
	VGCAssert(1 == color4.getAlpha());
	VGCAssert(2 == color4.getRed());
	VGCAssert(3 == color4.getGreen());
	VGCAssert(4 == color4.getBlue());

	VGCColor c00(0, 0, 0, 1);
	VGCColor c01(0, 0, 1, 0);
	VGCColor c02(0, 1, 0, 0);
	VGCColor c03(1, 0, 0, 0);
	VGCColor c10(0, 0, 0, 1);
	VGCColor c11(0, 0, 1, 0);
	VGCColor c12(0, 1, 0, 0);
	VGCColor c13(1, 0, 0, 0);
	VGCAssert(c00 == c10);
	VGCAssert(c01 == c11);
	VGCAssert(c02 == c12);
	VGCAssert(c03 == c13);
	VGCAssert(c00 != c01);
	VGCAssert(c00 != c02);
	VGCAssert(c00 != c03);
}

