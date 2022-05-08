#include <fstream>

#include "list.h"
#include "string.h"
#include "ember.h"

int main(int argc, char *argv[]) {
    if(argc < 2) throw ArgumentCountError(argc);
    if(strcmp(argv[1], "show") != 0 && strcmp(argv[1], "add") != 0 && strcmp(argv[1], "remove") != 0) throw CommandError();

    List<Ember> emberek;
    //region File read
    std::ifstream file;
    file.open("../adatok.dat");
    if(file.is_open()) {
        int db;
        while(file >> db) {
            Ember* tmp = new Ember();
            if(db < 8 || db > 14 || (db > 9 && db < 14)) throw FileError("Hibas db szam");
            if(db >= 8)file >> tmp->nev >> tmp->cim >> tmp->telefon;
            if(db >= 9) file >> tmp->nev.get_bece();
            if(db >= 14) file >> tmp->privCim;

            emberek.push_back(tmp);
        }

        file.close();
    }
    else throw FileError("../adatok.dat");
    //endregion

    if(strcmp(argv[1], "show") == 0) {
        if(emberek.get_size() == 0)
            std::cout << "A telefonkonyv meg ures" << std::endl;
        for (size_t i = 0; i < emberek.get_size(); ++i) {
            std::cout << emberek[i] << std::endl;
        }
    }
    if(strcmp(argv[1], "remove") == 0) {
        if(argc < 3) throw ArgumentCountError(argc);
        int id = -1;
        for (int i = 0; i < emberek.get_size(); ++i) {
            if(emberek[i].telefon == argv[2]) {id = i;break;}
        }
        if(id == -1) throw NoPhoneNumber(argv[2]);
        emberek.remove(id);
    }
    if(strcmp(argv[1], "add") == 0) {
        if(argc < 10 || argc > 16 || (argc > 11 && argc < 16)) throw ArgumentCountError(argc);

        Ember* tmp = new Ember();
        if(argc >= 10) {
            tmp->nev.set_nev(argv[2], argv[3]);
            tmp->cim.set_cim(std::stoi(argv[4]), argv[5], argv[6], argv[7], argv[8]);
            tmp->telefon = argv[9];
        }
        if(argc >= 11)
            tmp->nev.set_bece(argv[10]);
        if(argc >= 16)
        {
            tmp->privCim.set_cim(std::stoi(argv[11]), argv[12], argv[13], argv[14], argv[15]);
        }
        int id = -1;
        for (int i = 0; i < emberek.get_size(); ++i) {
            if(emberek[i].telefon == argv[9]) {id = i;break;}
        }
        if(id != -1) throw AlreadyExits();
        emberek.push_back(tmp);
    }

    //#region File write
    std::ofstream os;
    os.open("../adatok.dat");
    for (size_t i = 0; i < emberek.get_size(); ++i) {
        int meret = 8;
        if(emberek[i].nev.get_bece() != "") meret++;
        if(emberek[i].privCim.get_postal() != -1) meret+=5;

        os << meret << " " << emberek[i].file();
        os << "\n";
    }
    os.close();
    //#endregion
}
