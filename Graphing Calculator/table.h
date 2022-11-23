#ifndef TABLE_H 
#define TABLE_H

#include <string>

class table
{
private:
	uint8_t _inputType;
public:
	std::string function;
	std::string functionType;

	std::string fileName;
	bool createFile(std::string fileName);

	float x[10], y[10];

	std::pair<int, int> slope; //rise, run ; change in y, change in x
	int yInt;
	int a, b, c, vertex, xInts[2];

	table(uint8_t inputType);

	bool generateTable();
	void showTable();

};
#endif
