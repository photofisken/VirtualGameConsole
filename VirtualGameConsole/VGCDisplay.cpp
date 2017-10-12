#include "VGCDisplay.h"
#include "VGCAssert.h"
#include "VGCError.h"
#include "VGCVector.h"
#include "VGCRectangle.h"
#include "VGCColor.h"
#include "VGCAdjustment.h"
#include "VGCGDIPlus.h"
#include "VGCWindow.h"
#include "VGCImageImp.h"
#include "VGCFontImp.h"
#include <windows.h>
#include <gdiplus.h>
#include <fstream>
#include <strstream>
#include <string>
#include <set>



using namespace Gdiplus;



/* File scope data */
static int                     fInitializeMinusFinalizeCount = 0;
static int                     fBeginMinusEndCount           = 0;
static VGCDisplay::ImageImpSet fOpenImageImpSet              = VGCDisplay::ImageImpSet();
static VGCDisplay::FontImpSet  fOpenFontImpSet               = VGCDisplay::FontImpSet();
static VGCRectangle            fClipRectangle                = VGCRectangle();
static Graphics                *fWindowGraphics              = 0;
static Bitmap                  *fBackbuffer                  = 0;
static Graphics                *fBackbufferGraphics          = 0;
static SolidBrush              *fBrush                       = 0;
static Pen                     *fPen                         = 0;


/* File scope functions */
static bool fFileFound(const std::string &filename){
	std::ifstream inputStream(filename.c_str());
	return inputStream.is_open();
}

static bool fFontImpIsOpen(VGCFontImp *fontImp){
	return (fOpenFontImpSet.find(fontImp) != fOpenFontImpSet.end());
}

static bool fImageImpIsOpen(VGCImageImp *imageImp){
	return (fOpenImageImpSet.find(imageImp) != fOpenImageImpSet.end());
}

static bool fInvariant(){
	return 
		(0 < fInitializeMinusFinalizeCount) &&
		(0 != fWindowGraphics) &&
		(0 != fBackbuffer) &&
		(0 != fBackbufferGraphics) &&
		(0 != fBrush) &&
		(0 != fPen);
}

static bool fIsRendering(){
	return (0 < fBeginMinusEndCount);
}

static void fUpdateClipRectangle(){
	VGCAssert(fBackbufferGraphics);

	Rect rectangle = VGCGDIPlus::translateRectangle(fClipRectangle);
	Status status = fBackbufferGraphics->SetClip(rectangle, CombineModeReplace);
	if(Ok != status){
		VGCError("Could not set backbuffer clip rectangle. " + VGCGDIPlus::getStatusDescription(status));
	}
}


/* VGCDisplay */


/* Public functions */
bool VGCDisplay::beginFrame(){
	VGCAssert(fInvariant());

	const bool windowIsOpen = VGCWindow::windowIsOpen();
	if(windowIsOpen){
		fBeginMinusEndCount++;		
	}

	VGCAssert(fInvariant());
	return windowIsOpen;
}

void VGCDisplay::clear(const VGCColor &color){
	VGCAssert(fInvariant());
	VGCAssert(fIsRendering());

	Status status = fBackbufferGraphics->Clear(VGCGDIPlus::translateColor(color));
	if(Ok != status){
		VGCError("Could not clear backbuffer. " + VGCGDIPlus::getStatusDescription(status));
	}

	VGCAssert(fInvariant());
}

void VGCDisplay::closeFont(const VGCFont &font){
	VGCAssert(fInvariant());
	VGCAssert(fFontImpIsOpen(font.getFontImp()));


	VGCFontImp *fontImp = font.getFontImp();
	fOpenFontImpSet.erase(fontImp);
	delete fontImp;

	VGCAssert(!fFontImpIsOpen(font.getFontImp()));
	VGCAssert(fInvariant());
}

void VGCDisplay::closeImage(const VGCImage &image){
	VGCAssert(fInvariant());
	VGCAssert(fImageImpIsOpen(image.getImageImp()));

	VGCImageImp *imageImp = image.getImageImp();
	fOpenImageImpSet.erase(imageImp);
	delete imageImp;

	VGCAssert(!fImageImpIsOpen(image.getImageImp()));
	VGCAssert(fInvariant());
}

void VGCDisplay::endFrame(){
	VGCAssert(fInvariant());
	VGCAssert(fIsRendering());

	fBeginMinusEndCount--;
	if(0 == fBeginMinusEndCount){
		const int X      = 0;
		const int Y      = 0;
		const int WIDTH  = fBackbuffer->GetWidth();
		const int HEIGHT = fBackbuffer->GetHeight();
		Status status = fWindowGraphics->DrawImage(fBackbuffer, X, Y, WIDTH, HEIGHT);
		if(Ok != status){
			VGCError("Could not draw backbuffer to window. " + VGCGDIPlus::getStatusDescription(status));
		}
		VGCAssert(!fIsRendering());
	}

	VGCAssert(fInvariant());
}

void VGCDisplay::finalizeDisplay(){
	VGCAssert(fInvariant());
	VGCAssert(!fIsRendering());

	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		if(!fOpenImageImpSet.empty()){
			std::ostrstream description;
			description << "Could not finalize VGCDisplay. There are still ";
			description << int(fOpenImageImpSet.size()) << " open images.";
			description << '\0';
			VGCError(description.str());
		}

		if(!fOpenFontImpSet.empty()){
			std::ostrstream description;
			description << "Could not finalize VGCDisplay. There are still ";
			description << int(fOpenFontImpSet.size()) << " open fonts.";
			description << '\0';
			VGCError(description.str());
		}

		delete fPen;
		delete fBrush;
		delete fBackbufferGraphics;
		delete fBackbuffer;
		delete fWindowGraphics;
		fPen                = 0;
		fBrush              = 0;
		fBackbufferGraphics = 0;
		fBackbuffer         = 0;
		fWindowGraphics     = 0;

		VGCWindow::finalizeWindow();
		VGCFontImp::finalizeFontImp();
		VGCImageImp::finalizeImageImp();
	}
}

const VGCRectangle& VGCDisplay::getClipRectangle(){
	VGCAssert(fInvariant());

	return fClipRectangle;
}

int VGCDisplay::getHeight(){
	VGCAssert(fInvariant());

	return VGCWindow::getHeight();
}

int VGCDisplay::getHeight(const VGCImage &image){
	VGCAssert(fInvariant());
	VGCAssert(fImageImpIsOpen(image.getImageImp()));

	VGCImageImp *imageImp = image.getImageImp();
	return imageImp->getHeight();
}

int VGCDisplay::getWidth(){
	VGCAssert(fInvariant());

	return VGCWindow::getWidth();
}

int VGCDisplay::getWidth(const VGCImage &image){
	VGCAssert(fInvariant());
	VGCAssert(fImageImpIsOpen(image.getImageImp()));

	VGCImageImp *imageImp = image.getImageImp();
	return imageImp->getWidth();
}

void VGCDisplay::initializeDisplay(const std::string &applicationName, int displayWidth, int displayHeight){
	VGCAssert(0 <= displayWidth);	
	VGCAssert(0 <= displayHeight);	

	if(0 == fInitializeMinusFinalizeCount){
		VGCImageImp::initializeImageImp();		
		VGCFontImp::initializeFontImp();
		VGCWindow::initializeWindow(applicationName, displayWidth, displayHeight);

		Status status;

		fWindowGraphics = new Graphics(VGCWindow::getHandle(), FALSE);
		status = fWindowGraphics->GetLastStatus();
		if(Ok != status){
			VGCError("Could not create window graphics. " + VGCGDIPlus::getStatusDescription(status));
		}		
		

		const int BACKBUFFER_WIDTH  = VGCWindow::getWidth();
		const int BACKBUFFER_HEIGHT = VGCWindow::getHeight();
		fBackbuffer = new Bitmap(BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT, fWindowGraphics);
		VGCAssert(fBackbuffer);
		status = fBackbuffer->GetLastStatus();
		if(Ok != status){
			VGCError("Could not create backbuffer. " + VGCGDIPlus::getStatusDescription(status));
		}

		fBackbufferGraphics = new Graphics(fBackbuffer);
		status = fBackbufferGraphics->GetLastStatus();
		if(Ok != status){
			VGCError("Could not create backbuffer graphics. " + VGCGDIPlus::getStatusDescription(status));
		}		
		fClipRectangle = VGCRectangle(VGCVector(0, 0), BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);
		fUpdateClipRectangle();

		fBrush = new SolidBrush(Color(255, 255, 255, 255));
		status = fBrush->GetLastStatus();
		if(Ok != status){
			VGCError("Could not create brush. " + VGCGDIPlus::getStatusDescription(status));
		}		

		fPen = new Pen(Color(255, 255, 255, 255), 1.0f);
		status = fPen->GetLastStatus();
		if(Ok != status){
			VGCError("Could not create pen. " + VGCGDIPlus::getStatusDescription(status));
		}		
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

VGCFont VGCDisplay::openFont(const std::string &name, int size){
	VGCAssert(fInvariant());
	VGCAssert("" != name);
	VGCAssert(0 <= size);
	
	VGCFontImp *fontImp = new VGCFontImp(fBackbufferGraphics, name, size);
	VGCAssert(fontImp);
	fOpenFontImpSet.insert(fontImp);
	VGCAssert(fFontImpIsOpen(fontImp));
	VGCFont font(fontImp);

	VGCAssert(fInvariant());
	return font;
}

VGCImage VGCDisplay::openImage(const std::string &filename, int xFrameCount, int yFrameCount){
	VGCAssert(fInvariant());
	VGCAssert("" != filename);
	VGCAssert(0 < xFrameCount);
	VGCAssert(0 < yFrameCount);
	
	if(!fFileFound(filename)){
		std::ostrstream description;
		description << "File (" << filename << ") not found." << '\0';
		VGCError(description.str());
	}
	VGCImageImp *imageImp = 0;
	if((1 == xFrameCount) && (1 == yFrameCount)){
		imageImp = new VGCSimpleImageImp(fBackbufferGraphics, filename);
	}
	else{
		imageImp = new VGCComplexImageImp(fBackbufferGraphics, filename, xFrameCount, yFrameCount);
	}
	VGCAssert(imageImp);
	fOpenImageImpSet.insert(imageImp);
	VGCAssert(fImageImpIsOpen(imageImp));
	VGCImage image(imageImp);

	VGCAssert(fInvariant());
	return image;
}

void VGCDisplay::renderEllipse(const VGCRectangle &rectangle, 
                               const VGCColor &color, 
                               const VGCAdjustment &adjustment, 
                               bool fill){
	VGCAssert(fInvariant());
	VGCAssert(fIsRendering());

	const VGCVector &position = rectangle.getPosition(); 
	const int       WIDTH     = rectangle.getWidth();
	const int       HEIGHT    = rectangle.getHeight();
	if((0 < WIDTH) && (0 < HEIGHT)){
		const int       X         = (position.getX() - adjustment.getXAdjustment().computeOffset(WIDTH)); 
		const int       Y         = (position.getY() - adjustment.getYAdjustment().computeOffset(HEIGHT)); 
		if(fill){
			Status status;		
			const Rect rect = Rect(X, Y, WIDTH, HEIGHT); //-1 due to insane rect semantics
			status = fBrush->SetColor(VGCGDIPlus::translateColor(color));
			if(Ok != status){
				VGCError("Could not set brush color. " + VGCGDIPlus::getStatusDescription(status));
			}
			status = fBackbufferGraphics->FillEllipse(fBrush, rect);
			if(Ok != status){
				VGCError("Could not render filled ellipse. " + VGCGDIPlus::getStatusDescription(status));
			}
		}
		else{
			Status status;		
			const Rect rect = Rect(X, Y, WIDTH - 1, HEIGHT - 1); //-1 due to insane rect semantics
			status = fPen->SetColor(VGCGDIPlus::translateColor(color));
			if(Ok != status){
				VGCError("Could not set pen color. " + VGCGDIPlus::getStatusDescription(status));
			}	
			status = fBackbufferGraphics->DrawEllipse(fPen, rect);
			if(Ok != status){
				VGCError("Could not render ellipse. " + VGCGDIPlus::getStatusDescription(status));
			}	
		}
	}

	VGCAssert(fInvariant());
}

void VGCDisplay::renderImage(const VGCImage &image,
		                     const VGCVector &frameIndex,
                             const VGCVector &position,
                             const VGCAdjustment &adjustment){
	VGCAssert(fInvariant());
	VGCAssert(fIsRendering());
	VGCAssert(fImageImpIsOpen(image.getImageImp()));						

	VGCImageImp *imageImp =image.getImageImp();
	imageImp->render(frameIndex, position, adjustment);

	VGCAssert(fInvariant());
}

void VGCDisplay::renderLine(const VGCColor &color, const VGCVector &from, const VGCVector &to){
	VGCAssert(fInvariant());
	VGCAssert(fIsRendering());

	Status status;
	status = fPen->SetColor(VGCGDIPlus::translateColor(color));
	if(Ok != status){
		VGCError("Could not set pen color. " + VGCGDIPlus::getStatusDescription(status));
	}
	const int X1 = from.getX();
	const int Y1 = from.getY();
	const int X2 = to.getX();
	const int Y2 = to.getY();
	status = fBackbufferGraphics->DrawLine(fPen, X1, Y1, X2, Y2);
	if(Ok != status){
		VGCError("Could not render line. " + VGCGDIPlus::getStatusDescription(status));
	}

	VGCAssert(fInvariant());
}

void VGCDisplay::renderPoint(const VGCColor &color, const VGCVector &position){
	VGCAssert(fInvariant());
	VGCAssert(fIsRendering());

	if(fClipRectangle.isInside(position)){
		Color     targetColor; 
		const int X             = position.getX(); 
		const int Y             = position.getY(); 
		Status    status        = fBackbuffer->GetPixel(X, Y, &targetColor);
		if(Ok != status){
			VGCError("Could not read backbuffer pixel. " + VGCGDIPlus::getStatusDescription(status));
		}
		int    ALPHA        = color.getAlpha();
		int    SOURCE_RED   = color.getRed();
		int    SOURCE_GREEN = color.getGreen();
		int    SOURCE_BLUE  = color.getBlue();
		int    TARGET_RED   = targetColor.GetRed();
		int    TARGET_GREEN = targetColor.GetGreen();
		int    TARGET_BLUE  = targetColor.GetBlue();
		BYTE   NEW_ALPHA    = 0xff;
		BYTE   NEW_RED      = BYTE(((ALPHA * SOURCE_RED) + ((255 - ALPHA) * TARGET_RED)) >> 8);
		BYTE   NEW_GREEN    = BYTE(((ALPHA * SOURCE_GREEN) + ((255 - ALPHA) * TARGET_GREEN)) >> 8);
		BYTE   NEW_BLUE     = BYTE(((ALPHA * SOURCE_BLUE) + ((255 - ALPHA) * TARGET_BLUE)) >> 8);
		Color  newColor     = Color(NEW_ALPHA, NEW_RED, NEW_GREEN, NEW_BLUE);
		status              = fBackbuffer->SetPixel(X, Y, newColor);
		if(Ok != status){
			VGCError("Could not write backbuffer pixel. " + VGCGDIPlus::getStatusDescription(status));
		}
	}

	VGCAssert(fInvariant());
}

void VGCDisplay::renderRectangle(const VGCRectangle &rectangle, 
                                 const VGCColor &color, 
                                 const VGCAdjustment &adjustment, 
			             		 bool fill){
	VGCAssert(fInvariant());
	VGCAssert(fIsRendering());

	const VGCVector &position  = rectangle.getPosition(); 
	const int       WIDTH      = rectangle.getWidth();
	const int       HEIGHT     = rectangle.getHeight();
	if((0 < WIDTH ) && (0 < HEIGHT)){
		const int       X          = (position.getX() - adjustment.getXAdjustment().computeOffset(WIDTH)); 
		const int       Y          = (position.getY() - adjustment.getYAdjustment().computeOffset(HEIGHT)); 
		if(fill){
			Status status;		
			const Rect rect = Rect(X, Y, WIDTH, HEIGHT);
			status = fBrush->SetColor(VGCGDIPlus::translateColor(color));
			if(Ok != status){
				VGCError("Could not set brush color. " + VGCGDIPlus::getStatusDescription(status));			
			}
			status = fBackbufferGraphics->FillRectangle(fBrush, rect);
			if(Ok != status){
				VGCError("Could not render filled rectangle. " + VGCGDIPlus::getStatusDescription(status));
			}
		}
		else{
			Status status;		
			const Rect rect = Rect(X, Y, WIDTH - 1, HEIGHT - 1);	//-1 due to insane Rect semantics
			status = fPen->SetColor(VGCGDIPlus::translateColor(color));
			if(Ok != status){
				VGCError("Could not set pen color. " + VGCGDIPlus::getStatusDescription(status));
			}
			status = fBackbufferGraphics->DrawRectangle(fPen, rect);
			if(Ok != status){
				VGCError("Could not render rectangle. " + VGCGDIPlus::getStatusDescription(status));
			}	
		}
	}

	VGCAssert(fInvariant());
}

void VGCDisplay::renderString(const VGCFont &font,
                              const std::string &string, 
                              const VGCColor &color, 
                              const VGCVector &position, 
                              const VGCAdjustment &adjustment){
	VGCAssert(fInvariant());
	VGCAssert(fIsRendering());
	VGCAssert(fFontImpIsOpen(font.getFontImp()));


	VGCFontImp *fontImp = font.getFontImp();
	fontImp->render(string, color, position, adjustment);

	VGCAssert(fInvariant());
}
							  
void VGCDisplay::setClipRectangle(const VGCRectangle &clipRectangle){
	VGCAssert(fInvariant());

	fClipRectangle = clipRectangle;
	if(fIsRendering()){
		fUpdateClipRectangle();
	}

	VGCAssert(fInvariant());
}
