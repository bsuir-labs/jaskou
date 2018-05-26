#include <iostream>

using namespace std;

class BaseClass // базовый класс
{
protected:
	int* x1, *x2; // про отличие protected/private/public можешь почитать в методе, там табличка есть понятная
public:
	BaseClass(int x, int y) // конструктор, ничо сложного
	{
		x1 = new int;
		*x1 = x; // не помню, почему у меня это хранится именно в указателях
		x2 = new int; // вообще-то так делать нехорошо, но наверное, там надо по условию так
		*x2 = y; // ну по крайней мере, я так понял
	}

	~BaseClass() // деструктор
	{
		delete x1;
		delete x2;
	}

	virtual void set(int, int, int) = 0; // задаём пустые виртуальные функции
	virtual void print() = 0;

};

class ChildClass : public BaseClass // дочерний класс
{
protected:
	int *y;
public:
	ChildClass(int a, int b, int c) : BaseClass(a, b) // конструктор, который кроме прочего вызывает и конструктор родительского класса
	{
		y = new int;
		*y = c;
	}

	~ChildClass() // деструктор (остальные сами вызовутся)
	{
		delete y;
	}

	void set(int x, int y = 0, int z = 0) // определяем виртуальную функцию из родительского класса
	{
		*(this->x1) = x;
		*(this->x2) = y;
		*(this->y) = z;
	}
	
	void print() // эту тоже
	{
		cout << *x1 << " " << *x2 << " " << *y << endl;
	}

	int run() // ну тут изи
	{
		return *x1 + *x2 * *y;
	}
};

int main() {
	ChildClass *pObject; // создаём указатель на наш класс
	pObject = new ChildClass(1, 2, 3); // выделяем память
	pObject->set(12); // просто прверяю, как работает функция

	while (true) {
		cout << "Choose what to do.\nSet values\t1\n";
		cout << "Run\t\t2\nPrint\t\t3\nQuit\t\t0\n";
		cout << "Your decision: ";
		int cmd;
		cin >> cmd;
		int x, y, z;
		switch (cmd) {
		case 1: // тут задаются значения переменных
			cout << "x1 = ";
			cin >> x;
			cout << "x2 = ";
			cin >> y;
			cout << "y = ";
			cin >> z;
			pObject->set(x, y, z);
			break;
		case 2: // тут выполняется задание
			cout << "Running...\n";
			cout << "Result: " << pObject->run() << endl;
			break;
		case 3: // тут выводятся значения переменных
			cout << "Printing: ";
			pObject->print();
			break;
		case 0: // тут мы выходим
			return 0;
		default:
			cout << "Check your command...\n\n";
		}
	}
	return 0;
}
