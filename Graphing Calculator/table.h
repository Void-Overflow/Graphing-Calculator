#ifndef TABLE_H 
#define TABLE_H

#include <string>

class table
{
private:
	uint8_t _inputType;
public:
	std::string function;
	float x[10], y[10];

	std::pair<int, int> slope; //rise, run ; change in y, change in x
	int yInt;

	table(uint8_t inputType);

	void generateTable();
	void showTable();

};
#endif
