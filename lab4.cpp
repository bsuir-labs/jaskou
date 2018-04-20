#include <iostream>

using namespace std;

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
	~String();
};

String::String(const char *s)
{
	this->set(s);
}

void String::set(const char *s)
{
	if (this->s != nullptr) delete[] this->s;
	this->s = new char[strlen(s) + 1];
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
}

void String::print(ostream& os)
{
	int n = strlen(s);
	for (int i = 0; i < n; ++i)
		os << s[i];
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
	return is;
}

int main()
{
	String s, b;
	cin >> s;
	b = s;
	cout << b << endl;
	system("pause");
	return 0;
}