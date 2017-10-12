#include "VGCAssert.h"
#include <windows.h>
#include <string>
#include <strstream>



/* File scope functions */
static std::string stripPathInformation(const std::string &filename){
	std::string            strippedFilename(filename);
	std::string::size_type indexOfLastBackslash = strippedFilename.find_last_of('\\');
	if(std::string::npos != indexOfLastBackslash){
		strippedFilename.erase(0, indexOfLastBackslash + 1);
	}
	return strippedFilename;
}



/* VGCAssertBox */
	
/* Public functions */
void VGCAssertBox::messageBox(const std::string &expression, const std::string &filename, int lineNumber){
	std::string strippedFilename = stripPathInformation(filename);
	std::strstream description;
	description << expression << "\n\nFile: " << strippedFilename << "\n\nLine: " << lineNumber << '\0';
	MessageBox(NULL, description.str(), "Assertion failure", MB_OK);
}

