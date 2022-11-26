#include "table.h"

#include <iostream>
#include <fstream>
#include <filesystem>

int gcd(int a, int b)
{
	if (a == 0)
		return b;
	return gcd(b % a, a);
}

int findGCD(int arr[], int n)
{
	int result = arr[0];
	for (int i = 1; i < n; i++)
	{
		result = gcd(arr[i], result);

		if (result == 1)
		{
			return 1;
		}
	}
	return result;
}

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
				slope.first = std::stoi(function.substr(function.find("=") + 1 , function.find("/")));
				slope.second = std::stoi(function.substr(function.find("/") + 1, function.find("x")));
			}
			else {
				slope.first = std::stoi(function.substr(function.find("=") + 1, function.find("x")));
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
		case 3: { // Quadratic
			try {
				a = std::stoi(function.substr(0, function.find("^") - 1));
			}
			catch (std::invalid_argument) {
				a = 1;
			}
			std::string* BtoC = new std::string(function.substr(function.find("^") + 2, function.length()));
			b = std::stoi(BtoC->substr(0, BtoC->find("x")));
			c = std::stoi(BtoC->substr(BtoC->find("x") + 1, BtoC->length()));
			delete BtoC;

			int* Arr = new int[3]{a, b, c};
			int gcf = findGCD(Arr, sizeof(Arr) / sizeof(Arr[0]));
			delete[] Arr;
	
			a /= gcf;
			b /= gcf;
			c /= gcf;
			function = "(" + std::to_string(a) + ")x^2+(" + std::to_string(b) + ")x+(" + std::to_string(c) + ")";

			float counter = -5.0f;
			for (int i = 0; i < 10; i++) {
				x[i] = counter;
				y[i] = pow(a * x[i], 2) + b * x[i] + c;

				if(y[i] == 0)
					xInts[(xInts[0] == "N/A") ? 0 : 1] = std::to_string(x[i]);
				counter++;
			}

			vertex[0] = -b / (2 * a);
			vertex[1] = pow(a * vertex[0], 2) + b * vertex[0] + c;
		}
			break;
		case 5: // Exponential
			a = std::stoi(function.substr(0, function.find("(")));
			b = std::stoi(function.substr(function.find("(") + 1, function.find("^")));
			c = std::stoi(function.substr(function.find(")") + 1, function.length()));

			float counter = -5.0f;
			for (int i = 0; i < 10; i++) {
				x[i] = counter;
				y[i] = a * (pow(b, x[i])) + c;

				counter++;
			}
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

				x[row] = (float)std::stoi(str.substr(0, str.find(",")));
				y[row] = (float)std::stoi(str.substr(str.find(",") + 1, str.length()));
			}
			sprdsheet.close();

			if (y[2] - y[1] == y[8] - y[7]) { // slope is consistent - linear
				slope.first = y[2] - y[1];
				slope.second = x[2] - x[1];
				yInt = ((y[2] / (slope.first / slope.second)) - x[2]) * -2;
				functionType = "Linear";
				function = "y=" + std::to_string(slope.first) + "/" + std::to_string(slope.second) + "x+(" + std::to_string(yInt) + ")";
			}
			else if ((y[3] - y[2]) - (y[1] - y[0]) == (y[6] - y[5]) - (y[4] - y[3])) { // difference between differences is consistent - quadratic
				functionType = "Quadratic";
				for (int i = 0; i < 10; i++) {
					if (y[i] == 0)
						xInts[(xInts[0] == "N/A") ? 0 : 1] = std::to_string(x[i]);
					if (x[i] == 0) {
						c = y[i];
						b = y[i + 1] - y[i] - 1;
					}
				}
				a = (-b * x[1] - c + y[1]) / pow(x[1], 2);
				function = "(" + std::to_string(a) + ")x^2+(" + std::to_string(b) + ")x+(" + std::to_string(c) + ")";
				vertex[0] = -b / (2 * a);
				vertex[1] = pow(a * vertex[0], 2) + b * vertex[0] + c;
			}
			else if (y[3] / y[2] == y[1] / y[0]) { // quotient between each index is consistent - exponential
				b = y[3] / y[2];
				c = (int)x[0];
				for (int i = 0; i < 10; i++) {
					if (y[i] == 0)
						a = x[i] - c;
				}
				function = std::to_string(a) + "(" + std::to_string(b) + "^x)+(" + std::to_string(c) + ")";
				functionType = "Exponential";
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