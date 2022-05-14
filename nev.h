#ifndef TELEFON_NEV_H
#define TELEFON_NEV_H

#include "string.cpp"

class Nev {
    String vezetekNev;
    String keresztNev;
    String beceNev;
public:
    Nev():vezetekNev(), keresztNev(), beceNev()  {}
    String get_nev() const { return vezetekNev + " " + keresztNev; }
    String get_fullnev() const;
    void set_nev(const char* vez, const char* ker);
    String get_bece() const { return beceNev; }
    String& get_bece() { return beceNev; }
    void set_bece(const char * bece) { beceNev = bece; }

    friend std::istream& operator>>(std::istream& is, Nev&);

    virtual ~Nev() = default;
};
std::ostream& operator<<(std::ostream& os, const Nev& n);
std::istream& operator>>(std::istream& is, Nev& n);

#endif //TELEFON_NEV_H
