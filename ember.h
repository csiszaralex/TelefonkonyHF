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
    /**
     * Az ember Stringként fájlba való kiíráshoz
     * @return adatok szóközzel elválasztva fájlhoz
     */
    MyString file() const;
    /**
     * Név beállítása
     * @param vez Vezetéknév
     * @param ker Keresztnév
     */
    void set_nev(const char* vez, const char* ker){ nev.set_nev(vez, ker); }
    /**
     * Becenév beállítása
     * @param bece Becenév
     */
    void set_bece(const char* bece) { nev.set_bece(bece); }
    /**
     * Telefonszám beállítása
     * @param tel Telefonszám
     */
    void set_tel(const char* tel) { telefon = tel; }
    /**
     * Cím beállítása
     * @param p Irányítószám
     * @param c Város
     * @param a Cím
     * @param t Típus
     * @param num Házszám
     */
    void set_cim(int p, const char* c, const char* a, const char* t, const char* num) { cim.set_cim(p, c, a, t, num); }
    /**
     * Privát cím beállítása
     * @param p Irányítószám
     * @param c Város
     * @param a Cím
     * @param t Típus
     * @param num Házszám
     */
    void set_priv_cim(int p, const char* c, const char* a, const char* t, const char* num) { privCim.set_cim(p, c, a, t, num); }
    /**
     * Telefonszám lekérdezése
     * @return Telefonszám
     */
    MyString get_telefon() const { return telefon; }
    /**
     * Becenév lekérdezése
     * @return Becenév
     */
    MyString& get_bece() { return nev.get_bece(); }
    /**
     * Provát cím lekérése
     * @return Privát cím
     */
    Cim& get_priv_cim() { return privCim; }
    /**
     * Segítségével lekérdezhető, hogy be van e állítva becenév
     * @return Van e becenév
     */
    bool has_bece() const { return nev.get_bece() != ""; }
    /**
     * Segítségével lekérdezető, hogy be van e állítva privát cím
     * @return Van e privát cím
     */
    bool has_priv() const { return privCim.get_postal() != -1; }

    friend std::ostream& operator<<(std::ostream&, const Ember&);
    friend std::istream& operator>>(std::istream&, Ember&);

    virtual ~Ember() = default;
};

std::ostream& operator<<(std::ostream& os, const Ember& e);
std::istream& operator>>(std::istream& is, Ember& e);

#endif //TELEFON_EMBER_H
