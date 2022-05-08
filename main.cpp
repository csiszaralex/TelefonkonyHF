#include <fstream>
#include "gtest_lite.h"
#include "memtrace.h"
#include "list.h"
#include "string.h"
#include "ember.h"

//#define CPORTA

void readFile(List<Ember>* emberek, const char* fileName) {
    std::ifstream file;
    file.open(fileName);
    if(file.is_open()) {
        int db;
        while(file >> db) {
            Ember* tmp = new Ember();
            if(db < 8 || db > 14 || (db > 9 && db < 14)) {
                emberek->clear();
                delete tmp;
                throw FileError("Hibas db szam");
            }
            if(db >= 8)file >> tmp->nev >> tmp->cim >> tmp->telefon;
            if(db >= 9) file >> tmp->nev.get_bece();
            if(db >= 14) file >> tmp->privCim;

            emberek->push_back(tmp);
        }

        file.close();
    }
    else throw FileError(fileName);
}
void writeFile(List<Ember>* emberek, const char* fileName) {
    std::ofstream os;
    os.open(fileName);
    if(os.is_open()) {
    for (size_t i = 0; i < emberek->get_size(); ++i) {
        int meret = 8;
        if((*emberek)[i].nev.get_bece() != "") meret++;
        if((*emberek)[i].privCim.get_postal() != -1) meret+=5;

        os << meret << " " << (*emberek)[i].file();
        os << "\n";
    }
    os.close();
    }
    else throw FileError(fileName);
}
void show(List<Ember>* emberek) {
    if(emberek->get_size() == 0)
        std::cout << "A telefonkonyv meg ures" << std::endl;
    for (size_t i = 0; i < emberek->get_size(); ++i) {
        std::cout << (*emberek)[i] << std::endl;
    }
}
void remove(List<Ember>* emberek, const char* telo) {
    int id = -1;
    for (size_t i = 0; i < emberek->get_size(); ++i) {
        if((*emberek)[i].telefon == telo) {id = (int)i;break;}
    }
    if(id == -1) throw NoPhoneNumber(telo);
    emberek->remove(id);
}

int releaseMain(int argc, char *argv[]) {
    if(argc < 2) throw ArgumentCountError(argc);
    if(strcmp(argv[1], "show") != 0 && strcmp(argv[1], "add") != 0 && strcmp(argv[1], "remove") != 0) throw CommandError();

    List<Ember> emberek;
    readFile(&emberek, "../adatok.dat");

    if(strcmp(argv[1], "show") == 0) { show(&emberek); }
    if(strcmp(argv[1], "remove") == 0) {
        if(argc < 3) throw ArgumentCountError(argc);
        remove(&emberek, argv[2]);
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
        for (size_t i = 0; i < emberek.get_size(); ++i) {
            if(emberek[i].telefon == argv[9]) {id = (int)i;break;}
        }
        if(id != -1) throw AlreadyExits();
        emberek.push_back(tmp);
    }

    writeFile(&emberek, "../adatok.dat");
    return 0;
}

int testMain() {
    List<Ember> emberek;
    TEST(telefonkony,readFile) {
            EXPECT_THROW(readFile(&emberek, "nincs.dat"), FileError);
            EXPECT_THROW(readFile(&emberek, "hibas.dat"), FileError);
            EXPECT_EQ(0, emberek.get_size());
            EXPECT_NO_THROW(readFile(&emberek, "ures.dat"));
            EXPECT_EQ(0, emberek.get_size());
            EXPECT_NO_THROW(readFile(&emberek, "adatok.dat"));
            EXPECT_EQ(5, emberek.get_size());
    } END
    TEST(telefonkonyv, writeFile) {
            EXPECT_EQ(5, emberek.get_size());
            EXPECT_NO_THROW(writeFile(&emberek, "ki.dat"));
    } END
    TEST(telefonkonyv, remove) {
            EXPECT_EQ(5, emberek.get_size());
            EXPECT_THROW(remove(&emberek,"ilyenSzamNincs"), NoPhoneNumber);
            EXPECT_EQ(5, emberek.get_size());
            EXPECT_NO_THROW(remove(&emberek, "0620135424"));
            EXPECT_EQ(4, emberek.get_size());
            EXPECT_NO_THROW(remove(&emberek, "123456789"));
            EXPECT_EQ(3, emberek.get_size());
        } END

    return 0;
}

int main(int argc, char** argv) {
#if defined(CPORTA)
    return testMain();
#else
    return releaseMain(argc, argv);
#endif
}
