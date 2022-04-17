#include "gtest_lite.h"
#include "memtrace.h"

#include "string.h"

using std::endl;

int main() {
    TEST(String, ctor + size + c_str)
        {
            String ures;
            String charbol('a');
            String szovegbol("valami");
            String stringbol(charbol);
            const String konstans("test");

            EXPECT_EQ((size_t) 0, ures.size()) << "Hibas hossz: ures" << endl;
            EXPECT_EQ((size_t) 1, charbol.size()) << "Hibas hossz: charbol" << endl;
            EXPECT_EQ((size_t) 6, szovegbol.size()) << "Hibas hossz: szovegbol" << endl;
            EXPECT_EQ((size_t) 1, stringbol.size()) << "Hibas hossz: String-bol" << endl;
            EXPECT_EQ((size_t) 4, konstans.size()) << "Hibas hossz: konstans" << endl;
            EXPECT_STREQ("", ures.c_str()) << "Hibas kiiras: ures" << endl;
            EXPECT_STREQ("a", charbol.c_str()) << "Hibas kiiras: charbol" << endl;
            EXPECT_STREQ("valami", szovegbol.c_str()) << "Hibas kiiras: szovegbol" << endl;
            EXPECT_STREQ("a", stringbol.c_str()) << "Hibas kiiras: Strinbol" << endl;
            EXPECT_STREQ("test", konstans.c_str()) << "Hibas kiiras: konstans" << endl;
        }
            END
    TEST(String, operatorok)
        {
            String ures;
            String egyik("ABC");
            String masik("123");
            const String konst("teszt");

            String egyenlo = egyik;
            String osszeg = egyik + masik;
            String osszegbu = ures + egyik;
            String osszegju = egyik + ures;
            String osszegchar = egyik + 'a';
            String osszegchar2 = egyik + "cica";
            //char baloldalra nem mehet
            ures += egyik;
            egyik += 'a';
            masik += "asd";

            EXPECT_STREQ("ABC", egyenlo.c_str()) << "Hibas: = Str" << endl;
            EXPECT_STREQ("ABC123", osszeg.c_str()) << "Hibas: Str + Str" << endl;
            EXPECT_STREQ("ABC", osszegbu.c_str()) << "Hibas: Ures + Str" << endl;
            EXPECT_STREQ("ABC", osszegju.c_str()) << "Hibas: Str + Ures" << endl;
            EXPECT_STREQ("ABCa", osszegchar.c_str()) << "Hibas: Str + char" << endl;
            EXPECT_STREQ("ABCcica", osszegchar2.c_str()) << "Hibas: Str + char*" << endl;
            EXPECT_STREQ("ABC", ures.c_str()) << "Hibas: += Str" << endl;
            EXPECT_STREQ("ABCa", egyik.c_str()) << "Hibas: += char" << endl;
            EXPECT_STREQ("123asd", masik.c_str()) << "Hibas: += char*" << endl;

            EXPECT_NO_THROW(egyik[0]) << "Hibas: char[i]" << endl;
            EXPECT_THROW(egyik[4], OutOfRangeException) << "Hibas: char[i] error" << endl;
            egyik[2] = 'C';
            EXPECT_EQ('C', egyik[2]) << "Hibas: char[i] értékadás" << endl;
        }
            END
    TEST(String, I/O) {
        String s("Test   szöveg \n Kacsa");
        std::stringstream ss;
        ss << s;
        EXPECT_STREQ(s.c_str(), ss.str().c_str());

        ///A string szóköztől szóközig olvas!!!
        String in1, in2, in3;
        ss >> in1 >> in2 >> in3;
        EXPECT_STREQ("Test", in1.c_str());
        EXPECT_STREQ("szöveg", in2.c_str());
        EXPECT_STREQ("Kacsa", in3.c_str());

    }END
}

