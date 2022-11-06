#include "plane.h"

#include <iostream>

void plane::generatePoints()
{
	SetConsoleTextAttribute(_hConsole, 12);
	for (int i = 0; i < 10; i++) {
		int _x = 0, _y = 0;

		if (x[i] < 0) {
			if (x[i] == -10)
				_x = 0;
			else if (x[i] >= -10)
				_x = 1 + 2 * (abs(x[i]) - (abs(x[i]) - (10 - abs(x[i]))));
		}
		else if (x[i] == 0) 
			_x = 21;
		else if (x[i] > 0) {
			if (x[i] == 1)
				_x = 23;
			else if (x[i] <= 10)
				_x = 21 + 2 * x[i];
		}
		
		if (y[i] < 0) {
			if (y[i] == -1)
				_y = 15;
			else if (y[i] >= -6)
				_y = 13 + 2 * abs(y[i]);
		}
		else if (y[i] == 0)
			_y = 13;
		else if (y[i] > 0 && y[i] <= 6)
			_y = (6 - y[i] + 1) * 2 - 1;

		if ((x[i] >= -10 && x[i] <= 10) && (y[i] >= -6 && y[i] <= 6)) {
			COORD pos = { _x, _y };
			SetConsoleCursorPosition(_hConsole, pos);
			WriteConsole(_hConsole, "*", 5, NULL, NULL);
		}
	}
	SetConsoleTextAttribute(_hConsole, 15);

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
