#include <fstream>

#include "list.h"
#include "ember.h"

int main() {
    List<Ember> emberek;

    //region File
    std::ifstream file;
    file.open("../adatok.dat");
    if(file.is_open()) {
        std::string sor;
        int db;
        while(file >> db) {
            Ember* tmp = new Ember();
            if(db < 8 || db > 14 || (db > 9 && db < 14)) throw FileError("Hibas db szam");
            if(db >= 8)file >> tmp->nev.vezetekNev >> tmp->nev.keresztNev >> tmp->cim.postal >> tmp->cim.city >> tmp->cim.address >> tmp->cim.type >> tmp->cim.address >> tmp->telefon;
            if(db >= 9) file >> tmp->nev.beceNev;
            if(db >= 14) file >> tmp->privCim.postal >> tmp->privCim.city >> tmp->privCim.address >> tmp->privCim.type >> tmp->privCim.address;

            emberek.push_back(tmp);
        }

        file.close();
    }
    else throw FileError("../adatok.dat");
    //endregion

}
