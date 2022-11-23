#include "table.h"

#include <iostream>
#include <fstream>
#include <filesystem>

table::table(uint8_t inputType) {
	_inputType = inputType;
}

bool table::generateTable()
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
		if (_inputType == 1) { // from sprdsheet file
			std::ifstream sprdsheet;

			std::filesystem::path cwd = std::filesystem::current_path();
			sprdsheet.open(cwd.string() + "\\Spreadsheet Input\\" + fileName);

			if (sprdsheet.fail()) {
				sprdsheet.close();
				return true;
			}

			std::string str; 
			std::getline(sprdsheet, str);
			for (int row = 0; row < 10; row++) {
				std::getline(sprdsheet, str);

				uint8_t pos1 = str.find(",");
				uint8_t pos2 = str.find(",") + 1;

				x[row] = std::stoi(str.substr(0, pos1));
				y[row] = std::stoi(str.substr(pos2, str.length()));
			}
			sprdsheet.close();

			if ((y[2] - y[1]) / (x[2] - x[1]) == (y[4] - y[3]) / (x[4] - x[3])) { // slope is consistent - linear
				slope.first = y[2] - y[1];
				slope.second = x[2] - x[1];
				yInt = ((y[2] / (slope.first / slope.second)) - x[2]) * -2;
				functionType = "Linear";
				function = "y=" + std::to_string(slope.first) + "/" + std::to_string(slope.second) + "x+(" + std::to_string(yInt) + ")";
			}
		}
	}
	return false;
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

bool table::createFile(std::string fileName)
{
	std::filesystem::path cwd = std::filesystem::current_path();
	std::ofstream file(cwd.string() + "\\Spreadsheet Output\\" + fileName + ".csv");

	if (!file.is_open()) {
		file.close();
		return true;
	}

	file << "X,Y\n";
	for (int i = 0; i < 10; i++) 
		file << x[i] << "," << y[i] << '\n';

	file.close();
	return false;
}