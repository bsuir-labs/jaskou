#include <iostream>

using namespace std;

class Y;

class X
{
private:
	double x, y;
	double result;
public:
	X(double, double);
	friend void print(X*);
	friend void run(X*, Y*);
	~X();
};

class Y
{
private:
	double z;
public:
	Y(double);
	friend void run(X*, Y*);
	~Y();
};

X::X(double x, double y)
{
	this->x = x;
	this->y = y;
}

X::~X() // !!! PAY ATTENTION !!!
{
	/*
		Since I have nothing to destroy in destructor, 
		I have no idea what to write here, so there's 
		just printing information to know when destructor
		is called. If you have some other ideas about this function,
		just replace the cout or share your ideas with me (https://t.me/Kickoman)

		(Similarly with the destructor of Y class -- ~Y())
	*/
	cout << "X has been destroyed.\n";
}

Y::Y(double z)
{
	this->z = z;
}

Y::~Y()
{
	cout << "Y has been destroyed.\n";
}

void run(X* xclass, Y* yclass)
{
	double x = xclass->x,
		   y = xclass->y,
		   z = yclass->z;

	double numerator = exp(abs(x - y)) * pow(abs(x - y), x + y);
	double denominator = atan(x) + atan(z);
	double radical = cbrt(pow(x, 6) + pow(log(y), 2));
	xclass->result = numerator / denominator + radical;
}

void print(X* xclass)
{
	cout << "phi = " << xclass->result << endl;
}

int main()
{
	X *x = new X(-2.235 * 0.01, 2.23);
	Y *y = new Y(15.221);
	run(x, y);
	print(x);
	system("pause");
	return 0;
}