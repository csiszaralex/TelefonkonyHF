#ifndef TELEFON_CIM_H
#define TELEFON_CIM_H

#include <sstream>
#include "string.cpp"

class Cim {
    int postal;
    String city;
    String address;
    String type;
    String number;
public:

    Cim(): postal(-1), city(), address(), type(), number() {}
    String get_cim() const;
    void set_cim(int p, const char *c, const char * a,const  char * t,const char * num);
    int get_postal() const { return postal; }

    friend std::ostream& operator<<(std::ostream& os, const Cim&);
    friend std::istream& operator>>(std::istream& is, Cim&);

    virtual ~Cim() = default;
};
std::ostream& operator<<(std::ostream& os, const Cim& c);
std::istream& operator>>(std::istream& is, Cim& c);

#endif //TELEFON_CIM_H
