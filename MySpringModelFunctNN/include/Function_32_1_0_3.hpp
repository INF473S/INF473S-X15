#pragma once
#include "Function.hpp"

class Function_32_1_0_3 : public Function{

public:

	Function_32_1_0_3();
	~Function_32_1_0_3();

	virtual int getSize();
	virtual int getStep();
	virtual int getI();
	virtual int getJ();
	virtual double distance(double sequence[]);


private:

};