#ifndef TELEFON_NEV_H
#define TELEFON_NEV_H

#include "mystring.h"

class Nev {
    MyString vezetekNev;
    MyString keresztNev;
    MyString beceNev;
public:
    Nev():vezetekNev(), keresztNev(), beceNev()  {}
    MyString get_nev() const { return vezetekNev + " " + keresztNev; }
    MyString get_fullnev() const;
    void set_nev(const char* vez, const char* ker);
    MyString get_bece() const { return beceNev; }
    MyString& get_bece() { return beceNev; }
    void set_bece(const char * bece) { beceNev = MyString(bece); }

    friend std::istream& operator>>(std::istream& is, Nev&);

    virtual ~Nev() = default;
};
std::ostream& operator<<(std::ostream& os, const Nev& n);
std::istream& operator>>(std::istream& is, Nev& n);

#endif //TELEFON_NEV_H
