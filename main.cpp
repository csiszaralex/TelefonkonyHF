#include <fstream>
#include "gtest_lite.h"
#include "memtrace.h"
#include "list.h"
#include "ember.h"

//#define CPORTA

void readFile(List<Ember>* emberek, const char* fileName) {
    std::ifstream file;
    file.open(fileName);
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

std::string kivesz(std::string& line){
    std::string buffer;
    bool tobbszo = false;
    for (char i : line) {
        if (isspace(i)){
            tobbszo = true;
            break;
        }
    }
    std::stringstream ss;
    ss << line;
    getline(ss, buffer, ' ');
    if (tobbszo){
        getline(ss, line);
    } else {
        line = "";
    }
    return buffer;
}

int releaseMain() {

    List<Ember> emberek;
    readFile(&emberek, "../adatok.dat");

    MyString line;
    line.set_separator('\n');
    std::cout << ">>>";
    while(std::cin >> line) {
        MyString adat;
        line.kivesz(adat);
        if(adat == "exit") break;
        else if(adat == "help") help();
        else if(adat == "show") show(&emberek);
        else if(adat == "remove") {
            if(line.empty()) throw KevesAdat(2);
            line.kivesz(adat);
            remove(&emberek, adat.c_str());
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
        else throw CommandError();
        std::cout << ">>>";
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

int main() {
#if defined(CPORTA)
    return testMain();
#else
    return releaseMain();
#endif
}
