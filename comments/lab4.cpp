#include <iostream>
#include <string> // delete this
#include <fstream>

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

class String
{
private:
	char *s = nullptr;
public:
	String() {}
	String(const char *s);
	void set(const char *s);
	void set(const String&);
	void print();
	void print(ostream&);
	String& operator=(const String&);
	String& operator=(const char*);
	char& operator[](int x);
	int size();
	~String();
};

String::String(const char *s)
{
	this->set(s);
}

void String::set(const char *s)
{
	if (this->s != nullptr) { 
		delete[] this->s; 
		//logger("this->s deleted;", MEMCLE);
	}
	this->s = new char[strlen(s) + 1];
	//logger("set(const char *s)\tthis->s = new char[strlen(s) + 1];", MEMALL);
	strcpy(this->s, s);
}

void String::set(const String& s)
{
	this->set(s.s);
}

void String::print()
{
	int n = strlen(s);
	for (int i = 0; i < n; ++i)
		cout << s[i];
}

String::~String()
{
	delete[] s;
	//logger("~String()\tthis->s deleted;", MEMCLE);
}

void String::print(ostream& os)
{
	int n = strlen(s);
	for (int i = 0; i < n; ++i)
		os << s[i];
}

int String::size()
{
	return strlen(s);
}

String& String::operator=(const String &value)
{
	if (this != &value) {
		this->set(value);
	}
	return *this;
}

String& String::operator=(const char* s)
{
	this->set(s);
	return *this;
}

char& String::operator[](int x)
{
	if (x > strlen(s) || x < 0) throw new exception();
	return s[x];
}

ostream& operator<<(ostream& os, String& s)
{
	s.print(os);
	return os;
}

istream& operator>>(istream& is, String& s)
{
	int bufsize = 20;
	int size = 0;
	char *temp = new char[bufsize];
	//logger("operator>>\ttemp=new char[bufsize];", MEMALL);
	char c;
	bool readed = false;
	while (!(is.get(c).eof())) {
		if (c == ' ' || c == '\n') {
			if (readed) break;
			continue;
		}
		readed = true;
		temp[size++] = c;
		if (size >= bufsize - 1) {
			bufsize <<= 1;
			temp = (char*)realloc(temp, bufsize * sizeof(char));
		}
	}
	temp[size] = '\0';
	s.set(temp);
	delete[] temp;
	//logger("operator>>\ttemp deleted;", MEMCLE);
	return is;
}

void laboratoryTask(String& s)
{
	if (s.size() % 4 != 0) return;
	int n = s.size();
	for (int i = 0; i < n / 2; ++i)
		swap(s[i], s[i + n / 2]);
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