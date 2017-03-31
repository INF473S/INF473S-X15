#pragma once
#include "Function.hpp"

class Function_16_1_8_15 : public Function{

public:

	Function_16_1_8_15();
	~Function_16_1_8_15();

	virtual int getSize();
	virtual int getStep();
	virtual int getI();
	virtual int getJ();
	virtual double distance(double sequence[]);


private:

};