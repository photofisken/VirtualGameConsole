#include "VGCReferencedTest.h"
#include "VGCAssert.h"
#include "VGCReferenced.h"



class Test : public VGCReferenced{
};



/* VGCReferenced */

/* Public functions */
void VGCReferencedTest::run(){
	Test *t0 = new Test;
	VGCAssert(0 == t0->getReferenceCount());
	t0->increaseReferenceCount();
	VGCAssert(1 == t0->getReferenceCount());
	t0->decreaseReferenceCount();
	VGCAssert(0 == t0->getReferenceCount());
	delete t0;
}

