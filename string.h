#ifndef TELEFON_STRING_H
#define TELEFON_STRING_H

#include <iostream>
#include "exceptions.h"

class String {
    char* data;
    size_t len;
public:
    String(): data(0), len(0) {}
    String(char charter) {
        len = 1;
        data = new char[len+1];
        data[0] = charter;
        data[1] = '\0';
    }
    String(const char *p) {
        len = strlen(p);
        data = new char[len+1];
        strcpy(data, p);
    }
    String(const String& string) {
        len = string.len;
        if(string.data == NULL){
            data = NULL;
            return;
        }
        data = new char[len+1];
        strcpy(data, string.data);
    }

    size_t size() const { return len; }
    const char* c_str() const {
        if(data == NULL) return "";
        return data;
    }
    bool compare(String& str) {
        if(len != str.len) return false;
        for(size_t i = 0; i<len;i++) {
            if(data[i] != str.data[i]) return false;
        }
        return true;
    }
    bool compare(const char* c) {
        String tmp(c);
        bool all = compare(tmp);
        return all;
    }

    String& operator=(const String& rhs) {
        if(this == &rhs) return *this;
        delete[] data;
        len = rhs.len;
        if(rhs.data == NULL) {
            data = NULL;
            return *this;
        }
        data = new char[len+1];
        strcpy(data, rhs.data);
        return *this;
    }
    String operator+(const String& rhs) const {
        String tmp;
        tmp.len = len + rhs.len;
        delete[] tmp.data;
        if(tmp.len == 0) {
            tmp.data = NULL;
            return tmp;
        }
        tmp.data = new char[tmp.len+1];
        if(data == NULL) tmp.data[0] = '\0';
        else strcpy(tmp.data, data);
        if(rhs.data != NULL) strcat(tmp.data, rhs.data);
        return tmp;
    }
    String operator+(char rhs) const {
        return *this + String(rhs);
    }
    String& operator+=(const String& rhs) {
        *this = *this + rhs;
        return *this;
    }
    bool operator==(const char* c) {
        return compare(c);
    }
    bool operator!=(const char* c) {
        return !compare(c);
    }
    char& operator[](size_t idx){
        if(idx < 0) { throw OutOfRangeException(idx, 0); }
        if(idx >= len) throw OutOfRangeException(idx, len);
        return data[idx];
    }
    const char& operator[](size_t idx)const {
        if(idx < 0) { throw OutOfRangeException(idx, 0); }
        if(idx >= len) throw OutOfRangeException(idx, len);
        return data[idx];
    }

    ~String() { delete[] data; }
};

std::ostream& operator<<(std::ostream& os, const String& str) {
    os <<str.c_str();
    return os;
}
std::istream& operator>>(std::istream& is, String& str) {
    unsigned char c;
    str = String();
    std::ios_base::fmtflags flags = is.flags();
    is.setf(std::ios_base::skipws);
    while(is >> c) {
        is.unsetf(std::ios_base::skipws);
        if(c == ' ' || c == '\n') {
            is.putback(c);
            break;
        } else {
            str += c;
        }
    }
    is.setf(flags);
    return is;
}
String operator+(char ch, const String& str) {
    return String(ch)+str;
}
String operator+(char *ch, const String& str) {
    return String(ch)+str;
}


#endif //TELEFON_STRING_H
