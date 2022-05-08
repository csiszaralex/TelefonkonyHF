#ifndef TELEFON_NEV_H
#define TELEFON_NEV_H

class Nev {
    String vezetekNev;
    String keresztNev;
    String beceNev;
public:

    Nev():vezetekNev(), keresztNev(), beceNev()  {}
    String get_nev() const {
        String tmp = vezetekNev + " " + keresztNev;
        return tmp;
    }
    String get_fullnev() const {
        String tmp = vezetekNev + " " + keresztNev;
        if(!beceNev.compare("")) {
            tmp += " (";
            tmp+=beceNev+")";
        }
        return tmp;
    }
    void set_nev(const char* vez, const char* ker) {
        vezetekNev = vez;
        keresztNev = ker;
    }
    String get_bece() const {
        return beceNev;
    }
    String& get_bece() {
        return beceNev;
    }
    void set_bece(const char * bece) {
        beceNev= bece;
    }

    friend std::istream& operator>>(std::istream& is, Nev&);

    virtual ~Nev() = default;
};
std::ostream& operator<<(std::ostream& os, const Nev& n) {
    os << n.get_fullnev();
    return os;
}
std::istream& operator>>(std::istream& is, Nev& n) {
    is  >> n.vezetekNev >> n.keresztNev;
    return is;
}

#endif //TELEFON_NEV_H
