#include "plane.h"
#include <iostream>

plane::plane(int inputType)
{
	_inputType = inputType;
}

void plane::generatePlane()
{
	if (_inputType != 1) { //from functions
		//_func.function = function;
		switch (_inputType) {
		default:
		case 2: // linear

			break;
		case 3: // Quadratic
			break;
		case 4: // Cubic
			break;
		case 5: // Exponential
			break;
		}
	}
}

void plane::displayPlane()
{
	std::cout <<
				"		     | \n"
				"		     6 \n"
				"		     | \n"
				"		     5 \n"
				"		     | \n"
				"		     4 \n"
				"		     | \n"
				"		     3 \n"
				"		     | \n"
				"		     2 \n"
				"		     | \n"
				"		     1 \n"
	   			"		     | \n"
	   "10-9-8-7-6-5-4-3-2-1-+-1-2-3-4-5-6-7-8-9-10 \n"
				"		     | \n"
				"		     1 \n"
				"		     | \n"
				"		     2 \n"
				"		     | \n"
				"		     3 \n"
				"		     | \n"
				"		     4 \n"
				"		     | \n"
				"		     5 \n"
				"		     | \n"
				"		     6 " << std::endl;
}
