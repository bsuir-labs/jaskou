#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

enum Type {UNDEFINED, INT, DOUBLE, CHAR}; // перечисление для удобства


class Base // базовый класс
{
public:
	virtual void set(vector<int>)    {}; // парочка виртуальных функций
	virtual void set(vector<double>) {};
	virtual void set(vector<char>)   {};
	virtual void print() {};
};

template<class T> // после такой строки у нас везде в функции какбы заменится Т на какой-то тип, который нам передадут
class Multiplyer : public Base // создадим класс мультиплайер (умножитель)
{
	vector<T> list; // тут будет уже готовый плюсовский вектор
public:
	Multiplyer() {} // пустой конструктор
	Multiplyer(vector<T>); // конструктор от вектора
	void set(vector<T>); 
	void print();

	T& operator[] (int);// обращение по скобкам
};

template <class T> 
Multiplyer<T>::Multiplyer(vector<T> v)// конструктор
{
	set(v);
}

template <class T>
void Multiplyer<T>::set(vector<T> v) // функция сет
{
	int n = v.size();
	list.resize(n - 1);
	for (int i = 0; i < n - 1; ++i)
		list[i] = v[i] * v[i + 1];
}

template <class T>
void Multiplyer<T>::print() // вывод нашего класса, всё как и раньше было
{
	int n = list.size();
	for (int i = 0; i < n; ++i)
		cout << list[i] << " ";
	cout << endl;
}

template <class T>
T& Multiplyer<T>::operator[](int index) // ну и обращение по скобкам - вернём нужный элемент
{
	return list[index];
}

template <class T>
vector<T> get(int n) // функция чтения массива
{
	vector<T> temp(n);
	for (int i = 0; i < n; ++i)
		cin >> temp[i];
	return temp;
}

int main()
{
	cout << "N = ";
	int n; // число элементов
	cin >> n;
	
	Type type = UNDEFINED; // перечисление выберем. пока что стоит вариант "не выбрано"
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

	Base *multiplyer; // так в методе надо

	cout << "Input your array: ";

	
	switch (type)
	{
	case INT:
		multiplyer = new Multiplyer<int>(get<int>(n)); // читаем нужный нам массив, нужного типа
		break;
	case DOUBLE:
		
		multiplyer = new Multiplyer<double>(get<double>(n)); // вот эти все шаблоны вот так в угловых скобках задаются
		break;
	case CHAR:
		multiplyer = new Multiplyer<char>(get<char>(n));
		break;
	default:
		multiplyer = NULL;
	}

	cout << "Result:\n";
	multiplyer->print(); // выводим ответ
	
	system("pause");
	return 0;
}