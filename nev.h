#ifndef TELEFON_NEV_H
#define TELEFON_NEV_H
#include "string.h"

class Nev {
    String vezetekNev;
    String keresztNev;
    String beceNev;
public:
    Nev():vezetekNev(), keresztNev(), beceNev(){}
    Nev(const String& vezetek, const String& kereszt, const String& bece = ""):vezetekNev(vezetek), keresztNev(kereszt), beceNev(bece)  {}
    String get_nev() {
        String tmp = vezetekNev + " " + keresztNev;
        if(!beceNev.compare("")) {
            tmp += " (";
            tmp+=beceNev+")";
        }
        return tmp;
    }
    virtual ~Nev() = default;
};

#endif //TELEFON_NEV_H
