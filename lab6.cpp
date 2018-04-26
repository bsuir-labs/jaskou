#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

enum Type {UNDEFINED, INT, DOUBLE, CHAR};


class Base 
{
public:
	virtual void set(vector<int>)    {};
	virtual void set(vector<double>) {};
	virtual void set(vector<char>)   {};
	virtual void print() {};
};

template<class T>
class Multiplyer : public Base
{
	vector<T> list;
public:
	Multiplyer() {}
	Multiplyer(vector<T>);
	void set(vector<T>);
	void print();

	T& operator[] (int);
};

template <class T>
Multiplyer<T>::Multiplyer(vector<T> v)
{
	set(v);
}

template <class T>
void Multiplyer<T>::set(vector<T> v)
{
	int n = v.size();
	list.resize(n - 1);
	for (int i = 0; i < n - 1; ++i)
		list[i] = v[i] * v[i + 1];
}

template <class T>
void Multiplyer<T>::print()
{
	int n = list.size();
	for (int i = 0; i < n; ++i)
		cout << list[i] << " ";
	cout << endl;
}

template <class T>
T& Multiplyer<T>::operator[](int index)
{
	return list[index];
}

template <class T>
vector<T> get(int n)
{
	vector<T> temp(n);
	for (int i = 0; i < n; ++i)
		cin >> temp[i];
	return temp;
}

int main()
{
	cout << "N = ";
	int n;
	cin >> n;
	
	Type type = UNDEFINED;
	do {
		cout << "Choose your type: 1 (int), 2 (double), 3 (char)\nYour decision: ";
		int cmd;
		cin >> cmd;
		switch (cmd) {
		case 1:
			type = INT;
			break;
		case 2:
			type = DOUBLE;
			break;
		case 3:
			type = CHAR;
			break;
		default:
			cout << "It seems, you have mistaken. Try once more.\n";
		}
	} while (type == UNDEFINED);

	Base *multiplyer;

	cout << "Input your array: ";

	
	switch (type)
	{
	case INT:
		multiplyer = new Multiplyer<int>(get<int>(n));
		break;
	case DOUBLE:
		
		multiplyer = new Multiplyer<double>(get<double>(n));
		break;
	case CHAR:
		multiplyer = new Multiplyer<char>(get<char>(n));
		break;
	default:
		multiplyer = NULL;
	}

	cout << "Result:\n";
	multiplyer->print();
	
	system("pause");
	return 0;
}