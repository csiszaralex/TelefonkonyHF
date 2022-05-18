#ifndef TELEFON_MYSTRING_H
#define TELEFON_MYSTRING_H

#include <iostream>
#include <cstring>
#include "exceptions.h"

class MyString {
    char* data;
    size_t len;
    char separator = ' ';
public:
    MyString(): data(nullptr), len(0) {}
    MyString(char charter);
    MyString(const char *p);
    MyString(const MyString& string);

    void set_separator(char sep) { separator = sep; }
    size_t size() const { return len; }
    const char* c_str() const {return data == nullptr ? "" : data; }
    bool compare(MyString& str) const;
    bool compare(const char* c)const;
    bool empty() const { return len == 0; }

    MyString& operator=(const MyString& rhs);
    MyString operator+(const MyString& rhs) const;
    MyString operator+(char rhs) const;
    MyString& operator+=(const MyString& rhs);
    bool operator==(const char* c) const;
    bool operator!=(const char* c) const;
    char& operator[](size_t idx);
    const char& operator[](size_t idx)const;
    void kivesz(MyString& tmp);
    int toInt() const;

    friend std::istream& operator>>(std::istream& is, MyString& str);

    ~MyString();
};

std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);
MyString operator+(char ch, const MyString& str);
MyString operator+(char *ch, const MyString& str);


#endif //TELEFON_MYSTRING_H
