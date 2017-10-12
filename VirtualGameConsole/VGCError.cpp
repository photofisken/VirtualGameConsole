#include "VGCError.h"
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




/* VGCErrorBox */
	
/* Public functions */
void VGCErrorBox::messageBox(const std::string &description, const std::string &filename, int lineNumber){
	std::string    strippedFilename = stripPathInformation(filename);
	std::strstream complexDescription;
	complexDescription << description << "\n\nFile: " << strippedFilename << "\n\nLine: " << lineNumber << '\0';
	MessageBox(NULL, complexDescription.str(), "Error", MB_OK);
}
