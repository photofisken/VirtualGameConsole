#ifndef INCLUDED_VGCREFERENCED
#define INCLUDED_VGCREFERENCED



/******************************************************************************

This component implements a base class for reference counted classes. (objects
cannot be deleted while reference count is >0.  The counter is initialized to 
0.)

*******************************************************************************/



class VGCReferenced{
public:

	/* Public creators */
	VGCReferenced();
	virtual ~VGCReferenced();

	/* Public manipulators */
	void decreaseReferenceCount();
	void increaseReferenceCount();

	/* Public accessors */
	int getReferenceCount() const;

protected:

	/* Protected accessors */
	bool invariant() const;

private:
	
	/* Private creators */
	VGCReferenced(const VGCReferenced &referenced);

	/* Private manipulators */
	VGCReferenced& operator=(const VGCReferenced &referenced);

	/* private data */
	int mReferenceCount;
};

#endif