#ifndef PLANE_H
#define PLANE_H

#include "table.h"

class plane{
private:
	uint8_t _inputType;
	//table _func;
public:
	std::string function;
	float x[10], y[10];

	plane(int inputType);

	void generatePlane();
	void displayPlane();
};

#endif
