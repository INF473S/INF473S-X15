#pragma once
#include "Function.hpp"

class Function_32_1_16_18 : public Function{

public:

	Function_32_1_16_18();
	~Function_32_1_16_18();

	virtual int getSize();
	virtual int getStep();
	virtual int getI();
	virtual int getJ();
	virtual double distance(double sequence[]);


private:

};