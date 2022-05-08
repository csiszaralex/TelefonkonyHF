#ifndef TELEFON_CIM_H
#define TELEFON_CIM_H

#include <sstream>

class Cim {
    int postal;
    String city;
    String address;
    String type;
    String number;
public:

    Cim(): postal(-1), city(), address(), type(), number() {}
    String get_cim() const {
        if(postal==-1) return "";
        std::stringstream ss;
        ss << postal;
        String tmp = ss.str().c_str();
        tmp += " ";
        tmp += city + " " + address + " "+type + " " + number;
        return tmp;
    }
    void set_cim(int p, const char *c, const char * a,const  char * t,const char * num) {
        postal = p;
        city  = c;
        address = a;
        type = t;
        number = num;
    }
    int get_postal() const { return postal; }

    friend std::ostream& operator<<(std::ostream& os, const Cim&);
    friend std::istream& operator>>(std::istream& is, Cim&);

    virtual ~Cim() = default;
};
std::ostream& operator<<(std::ostream& os, const Cim& c) {
    if(c.postal != -1)
        os << c.postal << " " << c.city << ", " << c.address << " " << c.type << " " << c.number << ".";
    return os;
}
std::istream& operator>>(std::istream& is, Cim& c) {
    is  >> c.postal >> c.city >> c.address >> c.type >> c.number;
    return is;
}

#endif //TELEFON_CIM_H
