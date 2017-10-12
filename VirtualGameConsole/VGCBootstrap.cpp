#include "VGCBootstrap.h"
#include <windows.h>
#include <tchar.h>
#include <string>
#include <string>
#include <vector>
#include <strstream>


/* Declaration of the VGCmain() function */
extern int VGCMain(const VGCStringVector &arguments);



int APIENTRY _tWinMain(HINSTANCE i, HINSTANCE, LPTSTR commandLine, int){
	try{
		VGCStringVector arguments;
		std::istrstream stream(commandLine);
		while(stream){
			std::string argument;
			stream >> argument;
			if("" != argument){
				arguments.push_back(argument);
			}
		}
		return VGCMain(arguments);
	}
	catch(const std::exception &exception){
		MessageBox(NULL, exception.what(), "Exception", MB_OK);
		return -1;
	}
	catch(...){
		MessageBox(NULL, "Unknown exception.", "Exception", MB_OK);		
		return -1;
	}
	return 0;
}
