#include "table.h"

#include <iostream>

table::table(uint8_t inputType) {
	_inputType = inputType;
}

void table::generateTable()
{
	if (function != "") { // if input type if from a function -- generate table
		switch (_inputType) {
		default:
		case 2: { // linear
			if (function.find("/") != std::string::npos) { // slope isn't a whole number
				uint8_t pos1 = function.find("=") + 1;
				uint8_t pos2 = function.find("/");

				uint8_t pos3 = function.find("/") + 1;
				uint8_t pos4 = function.find("x");

				slope.first = std::stoi(function.substr(pos1, pos2));
				slope.second = std::stoi(function.substr(pos3, pos4));
			}
			else {
				uint8_t pos1 = function.find("=") + 1;
				uint8_t pos2 = function.find("x");

				slope.first = std::stoi(function.substr(pos1, pos2));
				slope.second = 1;
			}

			uint8_t pos3 = function.find("x") + 1;
			yInt = std::stoi(function.substr(pos3, function.length() - pos3));

			y[4] = yInt;
			x[4] = 0;

			
			for (int i = 5; i < 10; i++) 
				y[i] = (float)(slope.first) + (float)(y[i - 1]);
			for (int i = 3; i >= 0; i--)
				y[i] =  (float)(y[i + 1]) - (float)(slope.first);

			for (int i = 5; i < 10; i++)
				x[i] = (float)(slope.second) + (float)(x[i - 1]);
			for (int i = 3; i >= 0; i--)
				x[i] = (float)(x[i + 1]) - (float)(slope.second);

			break;
		}
		case 3: // Quadratic
			break;
		case 4: // Cubic
			break;
		case 5: // Exponential
			break;
		}
	}
	else { // if type is from table -- generate function

	}
}

void table::showTable()
{
	std::cout << "-----------------------------\n";
	std::cout << "Y    |   X\n";
	std::cout << "-----------------------------\n";
	for (int i = 0; i < 10; i++) {
		std::cout << y[i] << " | " << x[i] << '\n';
	}

	std::cout << "-----------------------------\n";
}
