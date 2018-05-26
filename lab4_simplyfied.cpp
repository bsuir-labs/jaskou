#include <iostream>
#include <fstream>
#include <string.h>
// #include <stdio.h>
#include <cstdio>

//#define LOCAL

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
    String& operator=(const String&);
    String& operator=(const char*);
    int size();
    ~String();

    friend void laboratoryTask(String&);
};

String::String(const char *s)
{
    this->set(s);
}

void String::set(const char *s)
{
    if (this->s != nullptr) {
        delete[] this->s;
    }
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

void laboratoryTask(String& s)
{
    if (s.size() % 4 != 0) return;
    int n = s.size();
    for (int i = 0; i < n / 2; ++i)
        swap(s.s[i], s.s[i + n / 2]);
}

void readString(String& s)
{
    char line[256];
    // gets_s(line, 256);
    gets(line); // TODO: replace with gets_s
    s = line;
}

int main()
{
    String L;


    ofstream outputfile("output.txt");
    outputfile << "source string: ";
    L.print();
    laboratoryTask(L);
    outputfile << "output string: ";
    L.print();

    return 0;
}
