#ifndef TELEFON_LIST_H
#define TELEFON_LIST_H

#include <iostream>
#include "exceptions.h"

template <class T>
class List {
    T** data;
    size_t size;

    List(const List&);
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
//    T pop_back() {
//        if(size == 0) { throw IsEmptyException(); }
//        T &tmp = data[size--];
//        if(size + 7 >= capacity) uj_foglalas(-5);
//        return tmp;
//    }


    bool empty() { return (size == 0); }
    size_t get_size() { return size; }
//    bool operator==() {}
//    operator=
    T* operator[](size_t idx) {
        if(idx < 0) { throw OutOfRangeException(idx, 0); }
        if(idx >= size) { throw OutOfRangeException(idx, size); }
        return data[idx];
    }

    void clear() {
        for (size_t i = 0; i < size; ++i) {
            delete data[i];
        }
        size = 0;
    }
    virtual ~List() { clear(); }
//insert()/add()
//remove()

};

#endif //TELEFON_LIST_H
