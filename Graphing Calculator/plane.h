#ifndef PLANE_H
#define PLANE_H

#include <windows.h>
#include <string>

class plane{
private:
	HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _pos;
public:
	std::string function;
	float x[10], y[10];

	void generatePoints();
	void displayPlane();
};

#endif
