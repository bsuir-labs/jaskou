#include <iostream>
#include <string>

using namespace std;

class Base
{
public:
	Base() {}
	virtual ~Base() {}
	virtual void print() = 0;
	friend void run();
};

/* PRODUCT */
class Product
{
protected:
	char* name;
	int quantity;
public:
	Product();
	Product(char*, int);
	Product(string, int);
	void setCount(int);
	void setName(char*);
	/*
		Todo:
		overload comparison operators, so you can use something from STL
	*/
	virtual ~Product();
};

Product::Product()
{
	name = nullptr;
	quantity = 0;
}

Product::Product(char* name, int quantity)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->quantity = quantity;
}

Product::Product(string name, int quantity)
{
	Product(name.c_str(), quantity);
}

void Product::setCount(int quantity)
{
	this->quantity = quantity;
}

void Product::setName(char* name)
{
	if (this->name != nullptr)
		delete this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

Product::~Product()
{
	delete this->name;
}

/* END OF PRODUCT */

class Factory : public Base
{
	
public:
	Factory();
	~Factory();
	void print();
};

Factory::Factory()
{

}

Factory::~Factory()
{

}

void run()
{

}

int main()
{
	
	return 0;
}