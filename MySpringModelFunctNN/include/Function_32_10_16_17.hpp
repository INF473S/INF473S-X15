#pragma once
#include "Function.hpp"

class Function_32_10_16_17 : public Function{

public:

	Function_32_10_16_17();
	~Function_32_10_16_17();

	virtual int getSize();
	virtual int getStep();
	virtual int getI();
	virtual int getJ();
	virtual double distance(double sequence[]);


private:

};