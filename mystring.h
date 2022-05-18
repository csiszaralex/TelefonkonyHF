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
    /**
     * Alap konstruktor, ami üresen hoz létre minden
     */
    MyString(): data(nullptr), len(0) {}
    /**
     * Konstruktor, mely egy karaterből állítja elő a Stirnget
     * @param charter Egy karakter
     */
    MyString(char charter);
    /**
     * Konstruktor, amely egy karakter tömbből állít elő stringet
     * @param p Karakter tömb
     */
    MyString(const char *p);
    /**
     * Másoló konstruktor
     * @param string Egy másik String osztály
     */
    MyString(const MyString& string);
    /**
     * Beolvasáskor mikor törjön
     * @param sep Törési karakter
     */
    void set_separator(char sep) { separator = sep; }
    /**
     * Visszatér a String hosszával
     * @return String hossza
     */
    size_t size() const { return len; }
    /**
     * Visszatér C stringgel
     * @return C string
     */
    const char* c_str() const {return data == nullptr ? "" : data; }
    /**
     * Összehasonlít 2 Stringet
     * @param str egy másik String
     * @return A 2 String egyezik e
     */
    bool compare(MyString& str) const;
    /**
     * Összehasonlítja a Stringet egy karakter tömbbel
     * @param c Karakter tömb
     * @return A 2 adat egyezik e
     */
    bool compare(const char* c)const;
    /**
     * Megállapíthatjuk vele, hogy a Stirng üres e
     * @return Üres e a String
     */
    bool empty() const { return len == 0; }

    /**
     * Egyenlőségadás operátor
     * @param rhs Másik String
     * @return Az új String
     */
    MyString& operator=(const MyString& rhs);
    /**
     * Egymáshoz fűz 2 Stringet
     * @param rhs Egy másik String
     * @return A 2 String összefűzve
     */
    MyString operator+(const MyString& rhs) const;
    /**
     * Hozzáfűz a Stringhez egy karaktert
     * @param rhs Egy karakter
     * @return A String, hozzáfzve a karakter
     */
    MyString operator+(char rhs) const;
    /**
     * Hozzáfűz egy Stringet
     * @param rhs Egy másik String
     * @return Az új String
     */
    MyString& operator+=(const MyString& rhs);
    /**
     * Összehasonlítja a Stringet egy karakter tömbbel
     * @param c Egy karater tömb
     * @return A 2 egyezik e
     */
    bool operator==(const char* c) const;
    /**
     * Megnézi, hogy a String eltér e egy karakter tömbtől
     * @param c Egy karakter tömb
     * @return A 2 eltér e
     */
    bool operator!=(const char* c) const;
    /**
     * Lekérdezehtő a String bizonyos sorszámadik eleme
     * @param idx Index
     * @return A szöveg Indexedik eleme
     */
    char& operator[](size_t idx);
    /**
     * Lekérdezehtő a String bizonyos sorszámadik eleme
     * @param idx Index
     * @return A szöveg Indexedik eleme
     */
    const char& operator[](size_t idx)const;
    /**
     * Kivesz egy szót a Stringből és azt a tmp-be rakja
     * @param tmp Amiben a szöveg elején lévő szó kerül
     */
    void kivesz(MyString& tmp);
    /**
     * Átkonvertálja a szöveget számmá
     * @return A String számként
     */
    int toInt() const;

    friend std::istream& operator>>(std::istream& is, MyString& str);

    ~MyString();
};

std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);
MyString operator+(char ch, const MyString& str);
MyString operator+(char *ch, const MyString& str);


#endif //TELEFON_MYSTRING_H
