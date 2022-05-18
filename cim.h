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
    /**
     * Konstruktor, ami mindennek alapértéket ad
     */
    Cim(): postal(-1), city(), address(), type(), number() {}
    /**
     * Lekérhető ezzel a cim szépen kiírva
     * @return A cím kiírható formátumban
     */
    MyString get_cim() const;
    /**
     * Beállítható a cím
     * @param p Irányítószám
     * @param c Város
     * @param a Cím
     * @param t Típus
     * @param num Házszám
     */
    void set_cim(int p, const char *c, const char * a,const  char * t,const char * num);
    /**
     * Lekérhető az irányítószám
     * @return Irányítószám
     */
    int get_postal() const { return postal; }

    friend std::ostream& operator<<(std::ostream& os, const Cim&);
    friend std::istream& operator>>(std::istream& is, Cim&);

    virtual ~Cim() = default;
};
std::ostream& operator<<(std::ostream& os, const Cim& c);
std::istream& operator>>(std::istream& is, Cim& c);

#endif //TELEFON_CIM_H
