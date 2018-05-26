#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <string.h>
#include <exception>

using namespace std;

class Base // базовый класс 
{
public:
	Base() {}
	virtual ~Base() {}
	virtual void print(ostream&) = 0; // виртуальное всё, абстрактное
};

/* PRODUCT */
class Product // класс продукта
{
protected:
	char* name; // у него есть имя
	int quantity; // и количество
public:
	Product(); // пустой конструктор
	Product(const char*, int); // конструктор с именем и кол-вом
	Product(string, int); // то же самое, только для класса стринг
	Product(const Product&); // конструктор копирования
	void setCount(int); // задать новое кол-во
	void setName(const char*); // задать новое имя
	char* getName() const { // получить имя
		return this->name;
	}
	int getCount() const { // получить кол-во
		return this->quantity;
	}

	// перегрузка операторов для сравнени продуктов
	inline friend bool operator<  (const Product& lhs, const Product& rhs);
	inline friend bool operator>  (const Product& lhs, const Product& rhs);
	inline friend bool operator== (const Product& lhs, const Product& rhs);
	inline friend bool operator<= (const Product& lhs, const Product& rhs);
	inline friend bool operator>= (const Product& lhs, const Product& rhs);
	inline friend bool operator!= (const Product& lhs, const Product& rhs);
	Product& operator=            (const Product& ref);
	virtual ~Product(); // деструктор
};

Product::Product()
{ // всё описываем
	name = nullptr;
	quantity = 0;
}
Product::Product(const Product& ref)
{
	*this = ref;
}
// в принципе, тут нечего пояснять. Основные штуки такие  же, как и раньше
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

// в перегрузке операторов, если оператор это Х, то выражение выглядит lhs X rhs. то есть у нас 
// в функциях тут лхс - левое значение, а рхс - правое
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
class Factory : public Base // класс фабрики
{
	set<Product> products; // множество продуктов
	int number; // и их количество
public:
	Factory() {}
	~Factory() {}
	void add(const Product&);
	void add(const char* name, int quantity);
	void print(ostream&);
	friend void run(int, vector<Factory>&, ofstream&); // дружественная функция выполнения идз
};

void Factory::add(const Product& product) // добавляем в фабрику продукт
{
	products.insert(product); // то есть, суём его в множество
}

void Factory::add(const char* name, int quantity) // или добавляем продукт по имени и кол-ву
{
	products.insert(Product(name, quantity));
}

void Factory::print(ostream& stream)
{
	// волшебное колдунство. используем тип итератора из класса множества set. 
	// причем итератора не простого, а золотого, обратного итератора. 
	// суть в том, что если в множестве мы будем идти от начала до конца, это будет расположено
	// по возрастанию элементов.

	// так как у нас итератор reverse, то мы пойдём с конца в начало - по убыванию элементов
	for (set<Product>::reverse_iterator it = products.rbegin(); it != products.rend(); it++)
		stream << it->getName() << " " << it->getCount() << endl;
}

void run(int factoryNumber, vector<Factory> &factories, ofstream& stream) // выполняем идз
{
	if (factoryNumber < 0 || factoryNumber >= factories.size())
		throw exception(); // если промахнулись с фабрикой, кидаем исключение

	if (factories[factoryNumber].products.empty()) // если фабрика ничего не производит, так и скажем
	{
		cout << "Factory #" << factoryNumber << " does not produce anything." << endl;
		return;
	}
	stream << "List of factory #" << factoryNumber << " products:" << endl;
	factories[factoryNumber].print(stream); // иначе выведем ответ
}

int main()
{
	vector<Factory> factories; // list of factories

	string outputFileName;
	cout << "Input output file name: ";
	cin >> outputFileName;

	ofstream file;
	try {
		file.open(outputFileName); // пытаемся открыть файл
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
		cout << "Enter number of factory or -1 to exit: ";
		int x;
		cin >> x;

		if (x == -1) break;

		try {
			run(x, factories, file);
		}
		catch (exception &e) {
			cout << "Some error" << endl;
		}
	}
	file.close();
	system("pause");
	return 0;
}