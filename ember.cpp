#include "ember.h"

MyString Ember::file() const {
    MyString tmp;
    tmp += nev.get_nev() + " ";
    tmp += cim.get_cim()+" "+telefon+" "+nev.get_bece();
    if(privCim.get_postal() != -1) {
        tmp += " ";
        tmp+=privCim.get_cim();
    }
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const Ember& e) {
    os << e.nev << " " << e.telefon << " " << e.cim << " " << e.privCim;
    return os;
}
std::istream& operator>>(std::istream& is, Ember& e) {
    is >> e.nev >> e.cim >> e.telefon;
    return is;
}