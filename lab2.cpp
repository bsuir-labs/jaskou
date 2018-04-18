#include <iostream>

using namespace std;

/*
	Comments :)
	I couldn't understand the exact task, 
	but I think it would be easy to edit 
	this code for your purposes
*/

class myFun
{
private:
	double x, y, z;
	double result;
public:
	void set(double, double, double);
	void print();
	void run();
};

void myFun::set(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void myFun::print()
{
	cout << "phi = " << result << endl;
}

void myFun::run()
{
	double numerator = exp(abs(x - y)) * pow(abs(x - y), x + y);
	double denominator = atan(x) + atan(z);
	double radical = cbrt(pow(x, 6) + pow(log(y), 2));
	result = numerator / denominator + radical;
}

int main()
{
	cout << "\t\t *** Direct ***\n\n"; 
	myFun straight;
	straight.set(-2.235 * 0.01, 2.23, 15.221);
	straight.run();
	straight.print();
	cout << "\n\n";

	cout << "\t\t*** Indirect ***\n\n";
	myFun *indirect = new myFun;
	indirect->set(-2.235 * 0.01, 2.23, 15.221);
	indirect->run();
	indirect->print();
	delete indirect;
	system("pause");
	return 0;
}