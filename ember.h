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
    Ember(const Ember& e){
        nev = e.nev;
        cim = e.cim;
        telefon = e.telefon;
        privCim = e.privCim;
    }
    String get_nev() {
        return nev.get_nev();
    }

    virtual ~Ember() = default;
};

//beolvas és kiir soronént egyből emberek

#endif //TELEFON_EMBER_H
