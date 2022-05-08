#ifndef TELEFON_EMBER_H
#define TELEFON_EMBER_H

#include "nev.h"
#include "cim.h"

class Ember {
public:
    Nev nev;
    Cim cim;
    String telefon;
    Cim privCim;

    Ember() = default;
    String file() const {
        String tmp;
        tmp += nev.get_nev() + " ";
        tmp += cim.get_cim()+" "+telefon+" "+nev.get_bece();
        if(privCim.get_postal() != -1) {
            tmp+=" ";
            tmp+=privCim.get_cim();
        }
        return tmp;
    }

    virtual ~Ember() = default;
};

std::ostream& operator<<(std::ostream& os, const Ember& e) {
    os << e.nev << " " << e.telefon << " " << e.cim << " " << e.privCim;
    return os;
}

#endif //TELEFON_EMBER_H
