#include <sstream>
#include "mystring.h"

MyString::MyString(char charter) {
    len = 1;
    data = new char[len+1];
    data[0] = charter;
    data[1] = '\0';
}
MyString::MyString(const char *p) {
    len = strlen(p);
    data = new char[len+1];
    strcpy(data, p);
}
MyString::MyString(const MyString& string) {
    len = string.len;
    if(string.data == nullptr){
        data = nullptr;
        return;
    }
    data = new char[len+1];
    strcpy(data, string.data);
}

bool MyString::compare(MyString& str) const {
    if(len != str.len) return false;
    for(size_t i = 0; i<len;i++) {
        if(data[i] != str.data[i]) return false;
    }
    return true;
}
bool MyString::compare(const char* c)const  {
    MyString tmp(c);
    bool all = compare(tmp);
    return all;
}

MyString &MyString::operator=(const MyString &rhs) {
    if(this == &rhs) return *this;
    delete[] data;
    len = rhs.len;
    if(rhs.data == nullptr) {
        data = nullptr;
        return *this;
    }
    data = new char[len+1];
    strcpy(data, rhs.data);
    return *this;
}

MyString MyString::operator+(const MyString &rhs) const {
    MyString tmp;
    tmp.len = len + rhs.len;
    delete[] tmp.data;
    if(tmp.len == 0) {
        tmp.data = nullptr;
        return tmp;
    }
    tmp.data = new char[tmp.len+1];
    if(data == nullptr) tmp.data[0] = '\0';
    else strcpy(tmp.data, data);
    if(rhs.data != nullptr) strcat(tmp.data, rhs.data);
    return tmp;
}

MyString MyString::operator+(char rhs) const {
    return *this + MyString(rhs);
}

MyString &MyString::operator+=(const MyString &rhs) {
    *this = *this + rhs;
    return *this;
}

bool MyString::operator==(const char *c) const {
    return compare(c);
}

bool MyString::operator!=(const char *c) const {
    return !compare(c);
}

char &MyString::operator[](size_t idx) {
    if(idx < 0) { throw OutOfRangeException((int)idx, 0); }
    if(idx >= len) throw OutOfRangeException((int)idx, (int)len);
    return data[idx];
}

const char &MyString::operator[](size_t idx) const {
    if(idx < 0) { throw OutOfRangeException((int)idx, 0); }
    if(idx >= len) throw OutOfRangeException((int)idx, (int)len);
    return data[idx];
}
MyString::~MyString() { delete[] data; }

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os <<str.c_str();
    return os;
}
std::istream& operator>>(std::istream& is, MyString& str) {
    char c;
    str = MyString();
    std::ios_base::fmtflags flags = is.flags();
    is.setf(std::ios_base::skipws);
    while(is >> c) {
        is.unsetf(std::ios_base::skipws);
        if(c == str.separator || c == '\n') {
            is.putback(c);
            break;
        } else {
            str += c;
        }
    }
    is.setf(flags);
    return is;
}

void MyString::kivesz(MyString& tmp) {
    bool tobbszo = false;
    for(size_t i = 0; i < len; ++i) {
        if(isspace(data[i])) {
            tobbszo = true;
            break;
        }
    }
    std::stringstream ss;
    for (size_t i = 0; i < len; ++i) {
        ss << data[i];
    }
    ss >> tmp;

    if(tobbszo) {
        MyString tor;
        tor.set_separator('\n');
        ss >> tor;
        len = tor.len;
        delete[] data;
        data = new char[len+1];
        strcpy(data, tor.data);
    } else {
        delete[] data;
        data = nullptr;
        len = 0;
    }
}
int MyString::toInt() const{
    int tmp = 0;
    for (size_t i = 0; i < len; ++i) {
        tmp += (data[i]-48)* pow(10,len-i-1);
    }
    return tmp;
}

MyString operator+(char ch, const MyString& str) { return MyString(ch) + str; }
MyString operator+(char *ch, const MyString& str) { return MyString(ch) + str; }
