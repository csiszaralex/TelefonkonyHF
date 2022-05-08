#ifndef TELEFON_NEV_H
#define TELEFON_NEV_H
#include "string.h"

class Nev {
public:
    String vezetekNev;
    String keresztNev;
    String beceNev;

    Nev():vezetekNev(), keresztNev(), beceNev(){}
    Nev(const String& vezetek, const String& kereszt, const String& bece = ""):vezetekNev(vezetek), keresztNev(kereszt), beceNev(bece)  {}
    String get_nev() const {
        String tmp = vezetekNev + " " + keresztNev;
        if(!beceNev.compare("")) {
            tmp += " (";
            tmp+=beceNev+")";
        }
        return tmp;
    }
    virtual ~Nev() = default;
};
std::ostream& operator<<(std::ostream& os, const Nev& n) {
    os << n.get_nev();
    return os;
}

#endif //TELEFON_NEV_H
