#ifndef PLANE_H
#define PLANE_H

class plane {
private:
	uint16_t _inputType;
public:
	std::string function;

	plane(int inputType);
	void generatePlane();
};

#endif
