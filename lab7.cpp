#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

class Base
{
public:
	Base() {}
	virtual ~Base() {}
	virtual void print(ostream&) = 0;
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
	Product(const char*, int);
	Product(string, int);
	Product(const Product&);
	void setCount(int);
	void setName(const char*);
	char* getName() const {
		return this->name;
	}
	int getCount() const {
		return this->quantity;
	}
	inline friend bool operator<  (const Product& lhs, const Product& rhs);
	inline friend bool operator>  (const Product& lhs, const Product& rhs);
	inline friend bool operator== (const Product& lhs, const Product& rhs);
	inline friend bool operator<= (const Product& lhs, const Product& rhs);
	inline friend bool operator>= (const Product& lhs, const Product& rhs);
	inline friend bool operator!= (const Product& lhs, const Product& rhs);
	Product& operator=            (const Product& ref);
	virtual ~Product();
};

Product::Product()
{
	name = nullptr;
	quantity = 0;
}
Product::Product(const Product& ref)
{
	*this = ref;
}

Product::Product(const char* name, int quantity)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->quantity = quantity;
}

Product::Product(string name, int quantity)
{
	char* tmpName = new char[(int)name.size() + 1];
	strcpy(tmpName, name.c_str());
	Product(tmpName, quantity);
}

void Product::setCount(int quantity)
{
	this->quantity = quantity;
}

void Product::setName(const char* name)
{
	if (!this->name)
		delete this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
inline bool operator< (const Product& lhs, const Product& rhs)
{
	return lhs.quantity < rhs.quantity;
}
inline bool operator> (const Product& lhs, const Product& rhs)
{
	return lhs.quantity > rhs.quantity;
}
inline bool operator<=(const Product& lhs, const Product& rhs)
{
	return !(lhs > rhs);
}
inline bool operator>=(const Product& lhs, const Product& rhs)
{
	return !(lhs < rhs);
}
inline bool operator==(const Product& lhs, const Product& rhs)
{
	return lhs.quantity == rhs.quantity;
}
inline bool operator!=(const Product& lhs, const Product& rhs)
{
	return !(lhs == rhs);
}
Product& Product::operator=(const Product& ref)
{
	this->setName(ref.name);
	this->setCount(ref.quantity);
	return *this;
}

Product::~Product()
{
	delete this->name;
}

/* END OF PRODUCT */
class Factory : public Base
{
	set<Product> products;
	int number;
public:
	Factory() {}
	~Factory() {}
	void add(const Product&);
	void add(const char* name, int quantity);
	void print(ostream&);
	friend void run(int, vector<Factory>&, ofstream&);
};

void Factory::add(const Product& product)
{
	products.insert(product);
}

void Factory::add(const char* name, int quantity)
{
	products.insert(Product(name, quantity));
}

void Factory::print(ostream& stream)
{
	for (set<Product>::reverse_iterator it = products.rbegin(); it != products.rend(); it++)
		stream << it->getName() << " " << it->getCount() << endl;
}

void run(int factoryNumber, vector<Factory> &factories, ofstream& stream)
{
	if (factoryNumber < 0 || factoryNumber >= factories.size())
		throw exception("Array index is out of range!");

	if (factories[factoryNumber].products.empty())
	{
		cout << "Factory #" << factoryNumber << " does not produce anything." << endl;
		return;
	}
	stream << "List of factory #" << factoryNumber << " products:" << endl;
	factories[factoryNumber].print(stream);
}

int main()
{
	vector<Factory> factories; // list of factories

	string outputFileName;
	cout << "Input output file name: ";
	cin >> outputFileName;

	ofstream file;
	try {
		file.open(outputFileName);
	}
	catch (...) {
		cout << "It seems, we could not open the file.\nTerminating";
		return 0;
	}

	cout << "How many factories do we have: ";
	int n;
	cin >> n;
	if (n < 1) {
		cout << "It can only be a positive number of factories." << endl;
		n = (n == 0 ? 1 : -n);
		cout << "Automatic set number of factories to " << n << endl;
	}

	factories.resize(n);
	for (int i = 0; i < n; ++i)
	{
		cout << "Let us know what does factory #" << i << " produce.\n";
		cout << "How many different products do you want here: ";
		int m;
		cin >> m;
		for (int j = 0; j < m; ++j)
		{
			cout << "Product " << i << "." << j << "\n";
			cout << "\tName: ";
			char name[255];
			cin >> name;
			fflush(stdin);
			cout << "\tQuantity: ";
			int quantity;
			cin >> quantity;
			fflush(stdin);
			factories[i].add(name, quantity);
		}
	}

	while (true) {
		cout << "Enter number of factory: ";
		int x;
		cin >> x;
		try {
			run(x, factories, file);
		}
		catch (exception &e) {
			cout << e.what() << endl;
		}
	}

	system("pause");
	return 0;
}