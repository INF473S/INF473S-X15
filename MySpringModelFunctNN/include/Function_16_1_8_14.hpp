#pragma once
#include "Function.hpp"

class Function_16_1_8_14 : public Function{

public:

	Function_16_1_8_14();
	~Function_16_1_8_14();

	virtual int getSize();
	virtual int getStep();
	virtual int getI();
	virtual int getJ();
	virtual double distance(double sequence[]);


private:

};