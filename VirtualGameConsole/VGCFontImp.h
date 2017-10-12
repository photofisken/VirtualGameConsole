#ifndef INCLUDED_VGCFONTIMP
#define INCLUDED_VGCFONTIMP



/******************************************************************************

This component implements a font type that defines the appearance and size of
text.

*******************************************************************************/



#include "VGCReferenced.h"
#include "VGCVector.h"
#include "VGCColor.h"
#include "VGCAdjustment.h"
#include <string>
#include <windows.h>
#include <gdiplus.h>



class VGCFontImp : public VGCReferenced{
public:

	/* Public creators */
	VGCFontImp(Gdiplus::Graphics *graphics, const std::string &name, int size);
	virtual ~VGCFontImp();

	/* Public manipulators */
	void setName(const std::string &name);
	void setSize(int size);

	/* Public accessors */
	Gdiplus::Graphics* getGraphics()                           const;
	int                getLineHeight()                         const;
	int                getLineWidth(const std::string &string) const;
	const std::string& getName()                               const;
	int                getSize()                               const;
	void               render(const std::string &string,
                              const VGCColor &color,
                              const VGCVector &position,
                              const VGCAdjustment &adjustment) const;

	/* Public functions */
	static void finalizeFontImp();
	static void initializeFontImp();

private:

	/* Private creators */
	VGCFontImp(const VGCFontImp &fontImp);

	/* Private manipulators */
	VGCFontImp& operator=(const VGCFontImp &fontImp);
	void        update();

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	Gdiplus::Graphics *mGraphics;
	std::string       mName;
	int               mSize;
	Gdiplus::Font     *mFont;
};

#endif