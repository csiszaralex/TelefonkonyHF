#include "cim.h"

String Cim::get_cim() const {
    if(postal==-1) return "";
    std::stringstream ss;
    ss << postal;
    String tmp = ss.str().c_str();
    tmp += " ";
    tmp += city + " " + address + " "+type + " " + number;
    return tmp;
}

void Cim::set_cim(int p, const char *c, const char *a, const char *t, const char *num) {
    postal = p;
    city  = c;
    address = a;
    type = t;
    number = num;
}

std::ostream& operator<<(std::ostream& os, const Cim& c) {
    if(c.postal != -1)
        os << c.postal << " " << c.city << ", " << c.address << " " << c.type << " " << c.number << ".";
    return os;
}
std::istream& operator>>(std::istream& is, Cim& c) {
    is  >> c.postal >> c.city >> c.address >> c.type >> c.number;
    return is;
}