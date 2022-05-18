#ifndef TELEFON_NEV_H
#define TELEFON_NEV_H

#include "mystring.h"

class Nev {
    MyString vezetekNev;
    MyString keresztNev;
    MyString beceNev;
public:
    /**
    * Alap konstruktor, mely mindent üresnek állít be.
    */
    Nev():vezetekNev(), keresztNev(), beceNev()  {}
    /**
     * A Név lekérése
     * @return Vezetéknév Keresztnév
     */
    MyString get_nev() const { return vezetekNev + " " + keresztNev; }
    /**
     * A Név lekérése, de ha van becenév azt is odaírja szépen
     * @return Vezetéknév Keresztnév (becenév) - ha van
     */
    MyString get_fullnev() const;
    /**
     * A Név beállítása
     * @param vez Vezetéknév string-ben
     * @param ker Keresztnév string-ben
     */
    void set_nev(const char* vez, const char* ker);
    /**
     * Becenév lekérése
     * @return Becenév constans
     */
    MyString get_bece() const { return beceNev; }
    /**
     * Becenév lekérése
     * @return Becenév
     */
    MyString& get_bece() { return beceNev; }
    /**
     * Becenév beállítása
     * @param bece Becenév string-ben
     */
    void set_bece(const char * bece) { beceNev = MyString(bece); }

    friend std::istream& operator>>(std::istream& is, Nev&);

    /**
     * Osztály destruktora
     */
    virtual ~Nev() = default;
};
std::ostream& operator<<(std::ostream& os, const Nev& n);
std::istream& operator>>(std::istream& is, Nev& n);

#endif //TELEFON_NEV_H
