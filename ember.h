#ifndef TELEFON_EMBER_H
#define TELEFON_EMBER_H

#include "string.h"
#include "nev.h"
#include "cim.h"

class Ember {
public:
    Nev nev;
    Cim cim;
    String telefon;
    Cim privCim;

    Ember() = default;
    String file() {
        String tmp;
        String post(std::to_string(cim.postal).c_str());
        tmp += nev.vezetekNev+" "+nev.keresztNev+" ";
        tmp+=post+" ";
        tmp+=cim.city+" "+cim.address+" "+cim.type+" "+cim.number+" "+telefon+" "+nev.beceNev;
        if(privCim.postal != -1) {
            tmp+=" ";
            tmp+=std::to_string(privCim.postal).c_str();
            tmp+=" "+privCim.city+" "+privCim.address+" "+privCim.type+" "+privCim.number;
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
