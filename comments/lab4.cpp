#include <iostream>
// #include <string> // delete this
#include <fstream>
#include <string.h>

//#define LOCAL

using namespace std;

//enum LogType { MEMALL, MEMCLE, OTHER };
//void logger(string text, LogType logType) {
//#ifdef LOCAL
//	static int level = 0;
//	for (int i = 0; i < level; ++i)
//		cerr << " ";
//	cerr << text << endl;
//	level += (logType == MEMALL ? 1 : -1);
//#endif // LOCAL
//}

class String // наш класс строки
{
private:
	char *s = nullptr; // на основе сишной строки, то есть массива чаров
public:
	String() {} // пустой конструктор
	String(const char *s); // конструктор из массива символов
	void set(const char *s); // метод, чтобы явно задать строке значение равное массиву символов (вместо а = б, можно писать а.сет(б))
	void set(const String&); // то же самое, только для другой строки нашего типа.
	void print(); // метод вывода в stdin
	void print(ostream&); // метод вывода в заданный поток, например в файл
	String& operator=(const String&); // перегрузка оператора =
	String& operator=(const char*); // то же самое, но для массива символов, чтоб можно было писать а = "кекмем"
	char& operator[](int x); // перегрузка оператора [], чтоб можно было обращаться к элементам нашей строки, как к обычному массиву
	int size(); // метод, возвращает размер строки
	~String(); // деструктор
};

String::String(const char *s) 
{
	this->set(s); // в конструкторе от массива символов можем просто вызвать функцию "сет"
}

void String::set(const char *s) // вот и функция сет задаётся
{
	if (this->s != nullptr) { 
		delete[] this->s; // если у нас чёт было уже, мы это удаляем
		//logger("this->s deleted;", MEMCLE);
	}
	this->s = new char[strlen(s) + 1]; // создаём новое
	//logger("set(const char *s)\tthis->s = new char[strlen(s) + 1];", MEMALL);
	strcpy(this->s, s); // и копируем туда нашу строку
}

void String::set(const String& s)
{
	this->set(s.s); // грубо говоря, приводим тип String к типу char*
}

void String::print() // обычный вывод
{
	int n = strlen(s);
	for (int i = 0; i < n; ++i)
		cout << s[i];
}

String::~String() // деструктор - удаляем указатель наш да и хватит
{
	delete[] s;
	//logger("~String()\tthis->s deleted;", MEMCLE);
}

void String::print(ostream& os) // вывод в нужный поток. Ничего сложного, просто cout заменён на переменную
{
	int n = strlen(s);
	for (int i = 0; i < n; ++i)
		os << s[i];
}

int String::size()
{
	return strlen(s);
}

String& String::operator=(const String &value) // перегрузка = 
{
	if (this != &value) { // если не в сами себя присваиваем, то просто функцию сет вызываем
		this->set(value);
	}
	return *this;
}

String& String::operator=(const char* s) // аналогично
{
	this->set(s); 
	return *this;
}

char& String::operator[](int x) // обращаемся по скобочкам
{
	if (x > strlen(s) || x < 0) throw new exception(); // если за границами массива, выкинем исключение
	return s[x]; // а иначе норм вернём ссылку на такой элемент
}

ostream& operator<<(ostream& os, String& s) // тут стоит повнимательнее
{
	s.print(os); // эта функция - перегрузка операции << для потоков вывода (например cout),  чтобы мы могли выводить в cout свои типы
	return os; // когда мы напишем String kek("kek"); cout << kek << endl;, у нас вызовется эта ф-ция и всё норм выведется
}

istream& operator>>(istream& is, String& s) // аналогичная перегрузка для ввода
{
	int bufsize = 20; // буфер
	int size = 0; // текущий размер
	char *temp = new char[bufsize]; // буфер для символов
	//logger("operator>>\ttemp=new char[bufsize];", MEMALL);
	char c; // символ, который читаем
	bool readed = false; // означает, что чтение состоялось)
	while (!(is.get(c).eof())) { // пока не конец файла, читаем символ с из потока "ис"
		if (c == ' ' || c == '\n') { // если пробел или перевод строки
			if (readed) break; // если уже читали, то вылетаем
			continue; // иначе, пропускаем итерацию, читаем следующий
		}
		readed = true; // раз дошли до сюда, помечаем, что чтение состоялось
		temp[size++] = c; // в буфер символов докладываем символ с
		if (size >= bufsize - 1) { // проверим, вдруг мы подбираемся к границе размера буфера
			bufsize <<= 1; // если так, то мы увеличим размер в два раза
			temp = (char*)realloc(temp, bufsize * sizeof(char)); // и добавим памяти на буфер
		}
	}
	temp[size] = '\0'; // закрываем строку нуль терминатором
	s.set(temp); // и задаём нашей строке значение этого массива символов
	delete[] temp; // удаляем временные переменные
	//logger("operator>>\ttemp deleted;", MEMCLE);
	return is; // вернём поток обратно
}

void laboratoryTask(String& s) // ну вот твоя лаба, тут изи
{
	if (s.size() % 4 != 0) return;
	int n = s.size();
	for (int i = 0; i < n / 2; ++i)
		swap(s[i], s[i + n / 2]); // просто свапаем местами две части слова
}

int main()
{
	//freopen("logs.log", "w", stderr); // deleteme

	String L;
	cin >> L;

	ofstream outputfile("output.txt");
	outputfile << "source string: " << L << endl; 
	laboratoryTask(L);
	outputfile << "output string: " << L << endl;

	return 0;
}