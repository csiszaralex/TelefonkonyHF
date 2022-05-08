#ifndef TELEFON_CIM_H
#define TELEFON_CIM_H

#include <sstream>
#include "string.h"

class Cim {
public:
    int postal;
    String city;
    String address;
    String type;
    String number;

    Cim(): postal(-1), city(), address(), type(), number() {}
    String get_cim() const {
        if(postal==-1) return "";
        std::stringstream ss;
        ss << address;
        String addr = ss.str().c_str();

        String tmp =  addr + " " + city + ", " + address;
        return tmp;
    }
    String get_city() const {return city;}
    int get_postal() const {return postal;}

    virtual ~Cim() = default;
};
std::ostream& operator<<(std::ostream& os, const Cim& c) {
    if(c.postal != -1)
        os << c.postal << " " << c.city << ", " << c.address << " " << c.type << " " << c.number << ".";
    return os;
}

#endif //TELEFON_CIM_H
