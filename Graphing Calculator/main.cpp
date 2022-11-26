#include <iostream>
#include <string>

#include "plane.h"
#include "table.h"

int main() {
	while (true) {
		MENU:
		int inputType, outputType;
		system("cls");
		std::cout << "\n   Welcome to Graphing Calculator!\n";
		std::cout << "	Made by Comyar Dehlavi\n";
		std::cout << "---------------------------------------\n\n\nInput Method:\n";
		std::cout << "1) Spread Sheet\n\n";
		std::cout << "2) Linear Function\n";
		std::cout << "3) Quadratic Function\n";
		std::cout << "5) Exponential Function\n\n";
		std::cin >> inputType;

		switch (inputType) { // Changes options based on input type
		case 1:
			system("cls");
			std::cout << "\n	Graphing Calculator\n";
			std::cout << "---------------------------------------\n\n\nOutput Method:\n";
			std::cout << "1) Function\n";
			std::cout << "2) Graph\n";
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
			std::cout << outputType;
			if (outputType == 9) 
				goto MENU;
			
			if (outputType == 4) {
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
		system("cls");
		if (inputType != 1) {
			std::cout << "Please enter your function: ";

			std::string functionIn;
			std::cin.ignore();
			std::getline(std::cin, functionIn);

			std::string::iterator end_pos = std::remove(functionIn.begin(), functionIn.end(), ' ');
			functionIn.erase(end_pos, functionIn.end()); // removes all spaces from string

			table tbl(inputType);
			tbl.function = functionIn;
			tbl.generateTable();

			system("cls");
			if (outputType == 6) {
				if (inputType == 2) // Linear
					std::cout << "Function : " << tbl.function << '\n' << "Slope : " << tbl.slope.first << "/" << tbl.slope.second << '\n' << "y-int " << ": " << tbl.yInt << std::endl;
				else if (inputType == 3) //Quadratic
					std::cout << "Function : " << tbl.function << '\n'
					<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n'
					<< "Vertex : " << tbl.vertex[0] << ", " << tbl.vertex[1] << '\n' << "X-Ints(Solutions based on table) : " << tbl.xInts[0] << ", " << tbl.xInts[1] << std::endl;
				else if (inputType == 5) //Exponential
					std::cout << "Function : " << tbl.function << '\n'
					<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n';
				tbl.showTable();
			}
			else if (outputType == 2) {
				plane coordPlane;

				for (int i = 0; i < 10; i++) {
					coordPlane.x[i] = tbl.x[i];
					coordPlane.y[i] = tbl.y[i];
				}

				coordPlane.displayPlane();
				coordPlane.generatePoints();

				for(int i = 0; i < 30; i++)
					std::cout << std::endl;

				if (inputType == 2) // Linear
					std::cout << "Function : " << tbl.function << '\n' << "Slope : " << tbl.slope.first << "/" << tbl.slope.second << '\n' << "y-int " << ": " << tbl.yInt << std::endl;
				else if (inputType == 3) //Quadratic
					std::cout << "Function : " << tbl.function << '\n'
					<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n'
					<< "Vertex : " << tbl.vertex[0] << ", " << tbl.vertex[1] << '\n' << "X-Ints(Solutions based on table) : " << tbl.xInts[0] << ", " << tbl.xInts[1] << std::endl;
				else if (inputType == 5) //Exponential
					std::cout << "Function : " << tbl.function << '\n'
					<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n';
				tbl.showTable();
			}
			else if (outputType == 5) {
				std::cout << "Please enter the output file name: ";
				std::string file;
				std::getline(std::cin, file);

				tbl.createFile(file);
				std::cout << std::endl << std::endl << "A file has successfully been created under \\Graphing Calculator\\Graphing Calculator\\" + file + ".csv\n\n"
					+ "File Information \n--------------------------------------- \n\n\n";
				if (tbl.functionType == "Linear") // Linear
					std::cout << "Function : " << tbl.function << '\n' << "Slope : " << tbl.slope.first << "/" << tbl.slope.second << '\n' << "y-int " << ": " << tbl.yInt << std::endl;
				else if (tbl.functionType == "Quadratic") //Quadratic
					std::cout << "Function : " << tbl.function << '\n'
					<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n'
					<< "Vertex : " << tbl.vertex[0] << ", " << tbl.vertex[1] << '\n' << "X-Ints(Solutions based on table) : " << tbl.xInts[0] << ", " << tbl.xInts[1] << std::endl;
				else if (tbl.functionType == "Exponential") //Exponential
					std::cout << "Function : " << tbl.function << '\n'
					<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n';
				tbl.showTable();
			}
		}

		else if (inputType == 1) {
			std::cin.ignore();
			FILEINPUT:
			std::cout << "Please enter the file name: ";

			std::string file;
			std::getline(std::cin, file);

			table tbl(inputType);
			tbl.fileName = file;
			
			if (tbl.generateTable()) {
				std::cout << "Couldn't the file, " << file << ", under the \"\\Graphing Calculator\\Graphing Calculator\\Spreadsheet Input\\\" Folder \n";

				std::string continueStr;
				std::cin.ignore();
				std::getline(std::cin, continueStr);

				system("cls");
				goto FILEINPUT;
			}
			else {
				system("cls");
				if (outputType == 1) {
					if (tbl.functionType == "Linear") // Linear
						std::cout << "Function : " << tbl.function << '\n' << '\n' << "Function Type : " << tbl.functionType << '\n' <<
						"Slope : " << tbl.slope.first << "/" << tbl.slope.second << '\n' << "y-int " << ": " << tbl.yInt << std::endl;
					else if (tbl.functionType == "Quadratic") //Quadratic
						std::cout << "Function : " << tbl.function << '\n'
						<< "Function Type : " << tbl.functionType << '\n'
						<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n'
						<< "Vertex : " << tbl.vertex[0] << ", " << tbl.vertex[1] << '\n' << "X-Ints(Solutions based on table) : " << tbl.xInts[0] << ", " << tbl.xInts[1] << std::endl;
					else if (tbl.functionType == "Exponential") //Exponential
						std::cout << "Function : " << tbl.function << '\n'
						<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n';
				}
				else if (outputType == 2) {
					plane coordPlane;

					for (int i = 0; i < 10; i++) {
						coordPlane.x[i] = tbl.x[i];
						coordPlane.y[i] = tbl.y[i];
					}

					coordPlane.displayPlane();
					coordPlane.generatePoints();

					for (int i = 0; i < 30; i++)
						std::cout << std::endl;

					if (tbl.functionType == "Linear") // Linear
						std::cout << "Function : " << tbl.function << '\n' <<'\n' << "Function Type : " << tbl.functionType << '\n' <<
						"Slope : " << tbl.slope.first << "/" << tbl.slope.second << '\n' << "y-int " << ": " << tbl.yInt << std::endl;
					else if (tbl.functionType == "Quadratic") //Quadratic
						std::cout << "Function : " << tbl.function << '\n'
						<< "Function Type : " << tbl.functionType << '\n' 
						<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n'
						<< "Vertex : " << tbl.vertex[0] << ", " << tbl.vertex[1] << '\n' << "X-Ints(Solutions based on table) : " << tbl.xInts[0] << ", " << tbl.xInts[1] << std::endl;
					else if (tbl.functionType == "Exponential") //Exponential
						std::cout << "Function : " << tbl.function << '\n'
						<< "A : " << tbl.a << "; B : " << tbl.b << "; C : " << tbl.c << '\n';
					tbl.showTable();
				}
			}
		}

		std::string continueStr;
		std::cin.ignore();
		std::getline(std::cin, continueStr);
	}

	return 0;
}  