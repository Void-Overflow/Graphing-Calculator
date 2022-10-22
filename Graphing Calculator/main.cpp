#include <iostream>

#include "plane.h"

int main() {

	while (true) {
		MENU:
		uint16_t inputType, outputType;
		system("cls");
		std::cout << "\n   Welcome to Graphing Calculator!\n";
		std::cout << "	Made by Comyar Dehlavi\n";
		std::cout << "---------------------------------------\n\n\nInput Method:\n";
		std::cout << "1) Spread Sheet\n\n";
		std::cout << "2) Linear Function\n";
		std::cout << "3) Quadratic Function\n";
		std::cout << "4) Cubic Function\n";
		std::cout << "5) Exponential Function\n\n";
		std::cin >> inputType;

		switch (inputType) { // Changes options based on input type
		case 1:
			system("cls");
			std::cout << "\n	Graphing Calculator\n";
			std::cout << "---------------------------------------\n\n\nOutput Method:\n";
			std::cout << "1) Function\n";
			std::cout << "2) Graph\n";
			std::cout << "3) Both\n\n";
			std::cout << "9) Back to Previous Page\n\n";

			std::cin >> outputType;
			if (outputType == 9) 
				goto MENU;
			break;
		default: // Gets output type
		GETOUTPUTTYPE:
			system("cls");
			std::cout << "\n	Graphing Calculator\n";
			std::cout << "---------------------------------------\n\n\nOutput TYPE:\n";
			std::cout << "4) Table\n";
			std::cout << "2) Graph\n\n";
			std::cout << "9) Back to Previous Page\n\n";

			std::cin >> outputType;
			if (outputType == 9) 
				goto MENU;
			
			else if (outputType == 4) {
				system("cls");
				std::cout << "\n	Graphing Calculator\n";
				std::cout << "---------------------------------------\n\n\nTable Type:\n";
				std::cout << "5) Spreadsheet File\n";
				std::cout << "6) Table in Current Window\n\n";
				std::cout << "9) Back to Previous Page\n\n";
				std::cin >> outputType;
				if (outputType == 9) {
					outputType = 0;
					goto GETOUTPUTTYPE;
				}
			}
			break;
		}


	}

	return 0;
}  