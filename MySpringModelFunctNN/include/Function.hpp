#pragma once

class Function{

public:

	Function();
	~Function();

	virtual int getSize();
	virtual int getStep();
	virtual int getI();
	virtual int getJ();
	virtual double distance(double sequence[]);

private:

};