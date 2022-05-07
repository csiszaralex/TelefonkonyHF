#ifndef TELEFON_CIM_H
#define TELEFON_CIM_H

#include <sstream>
#include "string.h"

class Cim {
    int postal;
    String city;
    String address;
public:
    Cim(): postal(-1), city(), address() {}
    Cim(String cim) {
        //TODO
    }
    String get_cim() {
        if(postal==-1) return "";
        std::stringstream ss;
        ss << address;
        String addr = ss.str().c_str();

        String tmp =  addr + " " + city + ", " + address;
        return tmp;
    }
    String get_city() {return city;}
    int get_postal() {return postal;}

    virtual ~Cim() = default;
};

#endif //TELEFON_CIM_H
