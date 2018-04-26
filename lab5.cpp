#include <iostream>

using namespace std;

class BaseClass
{
protected:
	int* x1, *x2;
public:
	BaseClass(int x, int y)
	{
		x1 = new int;
		*x1 = x;
		x2 = new int;
		*x2 = y;
	}

	~BaseClass() 
	{
		delete x1;
		delete x2;
	}

	virtual void set(int, int, int) = 0;
	virtual void print() = 0;

};

class ChildClass : public BaseClass
{
protected:
	int *y;
public:
	ChildClass(int a, int b, int c) : BaseClass(a, b)
	{
		y = new int;
		*y = c;
	}

	~ChildClass()
	{
		delete y;
	}

	void set(int x, int y = 0, int z = 0)
	{
		*(this->x1) = x;
		*(this->x2) = y;
		*(this->y) = z;
	}
	
	void print()
	{
		cout << *x1 << " " << *x2 << " " << *y << endl;
	}

	int run()
	{
		return *x1 + *x2 * *y;
	}
};

int main() {
	ChildClass *pObject;
	pObject = new ChildClass(1, 2, 3); // ???
	pObject->set(12);

	while (true) {
		cout << "Choose what to do.\nSet values\t1\n";
		cout << "Run\t\t2\nPrint\t\t3\nQuit\t\t0\n";
		cout << "Your decision: ";
		int cmd;
		cin >> cmd;
		int x, y, z;
		switch (cmd) {
		case 1:
			cout << "x1 = ";
			cin >> x;
			cout << "x2 = ";
			cin >> y;
			cout << "y = ";
			cin >> z;
			pObject->set(x, y, z);
			break;
		case 2:
			cout << "Running...\n";
			cout << "Result: " << pObject->run() << endl;
			break;
		case 3:
			cout << "Printing: ";
			pObject->print();
			break;
		case 0:
			return 0;
		default:
			cout << "Check your command...\n\n";
		}
	}
	return 0;
}
