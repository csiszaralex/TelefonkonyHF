#include <fstream>
#include "memtrace.h"
#include "list.h"
#include "ember.h"

//#define CPORTA
#ifdef CPORTA
    #include "gtest_lite.h"
#endif

void readFile(List<Ember>* emberek, const char* fileName) {
    std::ifstream file;
    file.open(fileName);
    if(!file.good()) {
        std::ofstream output(fileName);
        file.open(fileName);
    }
    if(file.is_open()) {
        int db;
        while(file >> db) {
            auto tmp = new Ember();
            if(db < 8 || db > 14 || (db > 9 && db < 14)) {
                emberek->clear();
                delete tmp;
                throw FileError("Hibas db szam");
            }
            if(db >= 8)file >> *tmp;
            if(db >= 9) file >> tmp->get_bece();
            if(db >= 14) file >> tmp->get_priv_cim();

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
        if((*emberek)[i].has_bece()) meret++;
        if((*emberek)[i].has_priv()) meret+=5;

        os << meret << " " << (*emberek)[i].file();
        os << "\n";
    }
    os.close();
    }
    else throw FileError(fileName);
}
void show(List<Ember>* emberek) {
    if(emberek->get_size() == 0)
        std::cout << "\tA telefonkonyv meg ures" << std::endl;
    for (size_t i = 0; i < emberek->get_size(); ++i) {
        std::cout << "    " <<(*emberek)[i] << std::endl;
    }
}
void remove(List<Ember>* emberek, const char* telo) {
    int id = -1;
    for (size_t i = 0; i < emberek->get_size(); ++i) {
        if((*emberek)[i].get_telefon() == telo) {id = (int)i;break;}
    }
    if(id == -1) throw NoPhoneNumber(telo);
    emberek->remove(id);
}
void help() {
    std::cout << "Kerem valasszon a kovetkezo pciok kozul:" << std::endl;
    std::cout << "\texit \t\t- Kilepes a programbol" << std::endl;
    std::cout << "\thelp \t\t- Segito menu" << std::endl;
    std::cout << "\tshow \t\t- Elmentett adatok listazasa" << std::endl;
    std::cout << "\tadd <VezN> <KerN> <Cim> <TelSz> [BeceN] [PrivCim] - Uj adat felvetele" << std::endl;
    std::cout << "\tremove <telefonszam> \t\t- Meglevo adat torlese telefonszam alapjan" << std::endl;

}

int releaseMain() {
    MyString datFilePath = "./adatok.dat";
    List<Ember> emberek;
    try {
        readFile(&emberek, datFilePath.c_str());
    } catch (FileError& e) {
        std::cout << "\t\tHiba a fajl megniytasakor" << std::endl;
        abort();
    }

    MyString line;
    line.set_separator('\n');
    std::cout << ">>>";
    while(std::cin >> line) {
        MyString adat;
        line.kivesz(adat);
        if(adat == "exit") break;
        else if(adat == "help") help();
        else if(adat == "show") show(&emberek);
        else if(adat == "save") writeFile(&emberek, datFilePath.c_str());
        else if(adat == "remove") {
            try {
                if (line.empty()) throw KevesAdat(2);
                line.kivesz(adat);
                remove(&emberek, adat.c_str());
            } catch (KevesAdat& e) {
                std::cout<< "\tKeves Adat!" << std::endl;
            } catch (NoPhoneNumber& e) {
                std::cout << "\tNem letezo telefonszam" << std::endl;
            }
        }
        else if(adat == "add"){
            auto tmp = new Ember;
            MyString vez, ker;
            line.kivesz(vez);
            line.kivesz(ker);
            tmp->set_nev(vez.c_str(), ker.c_str());
            MyString p, c, a, t, num;
            line.kivesz(p);
            line.kivesz(c);
            line.kivesz(a);
            line.kivesz(t);
            line.kivesz(num);
            tmp->set_cim(p.toInt(), c.c_str(), a.c_str(), t.c_str(), num.c_str());
            MyString tel;
            line.kivesz(tel);
            tmp->set_tel(tel.c_str());
            if(!line.empty()) {
                MyString bec;
                line.kivesz(bec);
                tmp->set_bece(bec.c_str());
            }
            if(!line.empty()) {
                line.kivesz(p);
                line.kivesz(c);
                line.kivesz(a);
                line.kivesz(t);
                line.kivesz(num);
                tmp->set_priv_cim(p.toInt(), c.c_str(), a.c_str(), t.c_str(), num.c_str());
            }
            emberek.push_back(tmp);
        }
        else std::cout << "\tHIBAS PARANCS!" << std::endl;
        std::cout << ">>>";
    }
    writeFile(&emberek, datFilePath.c_str());
    return 0;
}
#ifdef CPORTA
int testMain() {
    List<Ember> emberek;
    TEST(telefonkony,readFile) {
            EXPECT_NO_THROW(readFile(&emberek, "nincs.dat"));
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
    TEST(telefonkonyv, show) {
            show(&emberek);
    } END
    TEST(telefonkonyv, help) {
            help();
    } END
    TEST(telefonkonyv, add) {
            int count = emberek.get_size();
            auto tmp = new Ember;
            tmp->set_nev("Teszt", "Elek");
            tmp->set_cim(1111, "Budapest", "Kis", "utca", "13");
            tmp->set_tel("+36701234568");
            tmp->set_bece("Teszti");
            tmp->set_priv_cim(123, "Kiskunfelegyhaza", "Szabo", "utca", "72");
            emberek.push_back(tmp);
            EXPECT_EQ(count+1, emberek.get_size());
    } END
    TEST(telefonkonyv, << operators) {
        std::stringstream ss;
        ss << emberek[0];
    } END
    TEST(String, OutOfRange) {
        MyString m = "asd";
        EXPECT_THROW(m[5], OutOfRangeException);
     } END
    TEST(String, Kivesz) {
     MyString line = "teszt adat";
             EXPECT_STREQ("teszt adat", line.c_str());
             MyString szo;
             line.kivesz(szo);
             EXPECT_STREQ("teszt", szo.c_str());
             EXPECT_STREQ("adat", line.c_str());
             line.kivesz(szo);
            EXPECT_STREQ("adat", szo.c_str());
            EXPECT_EQ(true, line.empty());
    } END
    TEST(String, Szamma) {
        MyString tmp = "523";
            EXPECT_EQ(526, tmp.toInt()+3);
    } END
    TEST(String, Egyeb) {
        MyString tmp1, tmp2;
        char c = 'a';
        tmp1 = tmp1 + tmp2;
        tmp1 = tmp1 + c;
        tmp1 = c + tmp1;
            EXPECT_EQ('a', tmp1[0]);
    } END

    return 0;
}
#endif

int main() {
#if defined(CPORTA)
    return testMain();
#else
    return releaseMain();
#endif
}
