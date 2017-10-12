#include "VGCVirtualGameConsole.h"
#include "complex.h"
#include <string>



int VGCMain(const VGCStringVector &arguments){
	const std::string applicationName = "Mandelbrot";
	const int         DISPLAY_WIDTH   = 600;
	const int         DISPLAY_HEIGHT  = 600;
	VGCVirtualGameConsole::initialize(applicationName, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	const int    ITERATION_COUNT = 64;

	const double MIN_REAL   = -2.0;
	const double MIN_IMAG   = -1.5;
	const double DELTA_REAL = +3.0;
	const double DELTA_IMAG = +3.0;

	for(int x = 0; x < DISPLAY_WIDTH; x++){
		VGCDisplay::beginFrame();
		for(int y = 0; y < DISPLAY_HEIGHT; y++){
			const double  X_FRACTION = (double(x) / double(DISPLAY_WIDTH - 1)); 
			const double  Y_FRACTION = (double(y) / double(DISPLAY_HEIGHT - 1)); 
			const double  REAL       = (MIN_REAL + (X_FRACTION * DELTA_REAL)); 
			const double  IMAG       = (MIN_IMAG + (Y_FRACTION * DELTA_IMAG)); 
			const Complex complex    = Complex(REAL, IMAG);
			Complex       sum        = complex;
			int           i          = 0;
			for(i = 0; (i < ITERATION_COUNT) && (abs(sum) <= 2.0); i++){
				sum = ((sum * sum) + complex);
			}			
 			const VGCVector position = VGCVector(x, DISPLAY_HEIGHT - y - 1);
			if(i < ITERATION_COUNT){
				const double        COLOR_FRACTION  = (double(i) / double(ITERATION_COUNT - 1));
				const unsigned char COLOR_INTENSITY = (unsigned char)(255.0 - 255.0 * COLOR_FRACTION);
				const VGCColor      color           = VGCColor(255, COLOR_INTENSITY, COLOR_INTENSITY, COLOR_INTENSITY);
				VGCDisplay::renderPoint(color, position);
			}
			else{
				const VGCColor black(255, 0, 0, 0);
				VGCDisplay::renderPoint(black, position);			
			}
		}	
		VGCDisplay::endFrame();
	}

	while(VGCVirtualGameConsole::beginLoop()){
		VGCDisplay::beginFrame();	
		VGCDisplay::endFrame();	
		VGCVirtualGameConsole::endLoop();
	}

	VGCVirtualGameConsole::finalize();
	return 0;
}