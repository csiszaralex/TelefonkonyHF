#ifndef TELEFON_EMBER_H
#define TELEFON_EMBER_H

#include "nev.h"
#include "cim.h"
#include "mystring.h"

class Ember {
    Nev nev;
    Cim cim;
    MyString telefon;
    Cim privCim;

public:
    Ember() = default;
    MyString file() const;
    void set_nev(const char* vez, const char* ker){ nev.set_nev(vez, ker); }
    void set_bece(const char* bece) { nev.set_bece(bece); }
    void set_tel(const char* tel) { telefon = tel; }
    void set_cim(int p, const char* c, const char* a, const char* t, const char* num) { cim.set_cim(p, c, a, t, num); }
    void set_priv_cim(int p, const char* c, const char* a, const char* t, const char* num) { privCim.set_cim(p, c, a, t, num); }
    MyString get_telefon() const { return telefon; }
    MyString& get_bece() { return nev.get_bece(); }
    Cim& get_priv_cim() { return privCim; }
    bool has_bece() const { return nev.get_bece() != ""; }
    bool has_priv() const { return privCim.get_postal() != -1; }

    friend std::ostream& operator<<(std::ostream&, const Ember&);
    friend std::istream& operator>>(std::istream&, Ember&);

    virtual ~Ember() = default;
};

std::ostream& operator<<(std::ostream& os, const Ember& e);
std::istream& operator>>(std::istream& is, Ember& e);

#endif //TELEFON_EMBER_H
