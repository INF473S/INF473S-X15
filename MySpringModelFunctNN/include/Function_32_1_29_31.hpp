#pragma once
#include "Function.hpp"

class Function_32_1_29_31 : public Function{

public:

	Function_32_1_29_31();
	~Function_32_1_29_31();

	virtual int getSize();
	virtual int getStep();
	virtual int getI();
	virtual int getJ();
	virtual double distance(double sequence[]);


private:

};