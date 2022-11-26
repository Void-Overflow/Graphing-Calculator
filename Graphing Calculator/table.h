#ifndef TABLE_H 
#define TABLE_H

#include <string>

class table
{
private:
	uint8_t _inputType;
public:
	std::string function = "";
	std::string functionType = "";

	std::string fileName = "";
	bool createFile(std::string fileName);

	float x[10], y[10];

	std::pair<int, int> slope; //rise, run ; change in y, change in x
	int yInt;
	int a = 1, b = 0, c = 0, vertex[2] = { 0, 0 };
	std::string xInts[2] = { "N/A", "N/A"};

	table(uint8_t inputType);

	bool generateTable();
	void showTable();

};
#endif
