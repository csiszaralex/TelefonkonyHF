#include "nev.h"

MyString Nev::get_fullnev() const {
    MyString tmp = vezetekNev + " " + keresztNev;
    if(!beceNev.compare("")) {
        tmp += " (";
        tmp+=beceNev+")";
    }
    return tmp;
}

void Nev::set_nev(const char* vez, const char* ker) {
    vezetekNev = vez;
    keresztNev = ker;
}

std::ostream& operator<<(std::ostream& os, const Nev& n) {
    os << n.get_fullnev();
    return os;
}
std::istream& operator>>(std::istream& is, Nev& n) {
    is  >> n.vezetekNev >> n.keresztNev;
    return is;
}