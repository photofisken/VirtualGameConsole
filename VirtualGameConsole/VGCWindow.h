#ifndef INCLUDED_VGCWINDOW
#define INCLUDED_VGCWINDOW



/******************************************************************************

This component implements a win32 window. Width and height refer to the client
area (as opposed to the whole window which is the case in win32 itself). 

*******************************************************************************/



#include <windows.h>
#include <tchar.h>
#include <string>


struct VGCWindow{

	/* Public functions */
	static void finalizeWindow();
	static HWND getHandle();
	static int  getHeight();
	static int  getWidth();
	static void handleMessages();
	static void initializeWindow(const std::string &title, int width, int height);
	static bool windowIsOpen();
};


#endif