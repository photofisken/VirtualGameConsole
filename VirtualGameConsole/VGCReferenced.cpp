#include "VGCReferenced.h"
#include "VGCAssert.h"



/* VGCReferenced */

/* Public creators */
VGCReferenced::VGCReferenced() : 
	mReferenceCount(0){

	VGCAssert(invariant());	
}

VGCReferenced::~VGCReferenced(){
	VGCAssert(invariant());	
	VGCAssert(0 == mReferenceCount);

	mReferenceCount = -1;

	VGCAssert(!invariant());	
}

/* Public manipulators */
void VGCReferenced::decreaseReferenceCount(){
	VGCAssert(invariant());	
	VGCAssert(0 < mReferenceCount);
	
	mReferenceCount--;

	VGCAssert(invariant());	
}

void VGCReferenced::increaseReferenceCount(){
	VGCAssert(invariant());	

	mReferenceCount++;

	VGCAssert(invariant());	
}

/* Public accessors */
int VGCReferenced::getReferenceCount() const{
	VGCAssert(invariant());	

	return mReferenceCount;
}

/* Protected accessors */
bool VGCReferenced::invariant() const{
	return (0 <= mReferenceCount);
}

