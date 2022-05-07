#ifndef TELEFON_LIST_H
#define TELEFON_LIST_H

#include <iostream>
#include "exceptions.h"

template <class T>
class List {
    T** data;
    size_t size;


    List& operator=(const List&);
public:
    List(): data(NULL), size(0) {}

    void push_back(T* uj) {
        T** tmp = new T*[size+1];
        for (size_t i = 0; i < size; ++i) {
            tmp[i] = data[i];
        }
        tmp[size++] = uj;
        delete[] data;
        data = tmp;
    }


    bool empty() { return (size == 0); }
    size_t get_size() { return size; }
    T operator[](size_t idx) {
        if(idx < 0) { throw OutOfRangeException(idx, 0); }
        if(idx >= size) { throw OutOfRangeException(idx, size); }
        return *data[idx];
    }

    void clear() {
        for (size_t i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;
        size = 0;
    }
    virtual ~List() { clear(); }

};

#endif //TELEFON_LIST_H
