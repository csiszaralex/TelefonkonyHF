#ifndef TELEFON_CIM_H
#define TELEFON_CIM_H

#include <sstream>
#include "mystring.h"

class Cim {
    int postal;
    MyString city;
    MyString address;
    MyString type;
    MyString number;
public:

    Cim(): postal(-1), city(), address(), type(), number() {}
    MyString get_cim() const;
    void set_cim(int p, const char *c, const char * a,const  char * t,const char * num);
    int get_postal() const { return postal; }

    friend std::ostream& operator<<(std::ostream& os, const Cim&);
    friend std::istream& operator>>(std::istream& is, Cim&);

    virtual ~Cim() = default;
};
std::ostream& operator<<(std::ostream& os, const Cim& c);
std::istream& operator>>(std::istream& is, Cim& c);

#endif //TELEFON_CIM_H
