#ifndef TELEFON_EXCEPTION_H
#define TELEFON_EXCEPTION_H

#include <exception>
#include <string>

class Exception: public std::exception {
protected:
    int err_num;
    std::string err_msg;
public:
    Exception(const std::string msg, int num): err_num(num),  err_msg(msg) {}
    ~Exception() throw() override = default;

    virtual const char* what() const throw() {
        std::string ki = "\n>>>" + err_msg + "\n\n";
        return ki.c_str();
    }
    virtual int getErrorNumber() const throw() { return err_num; }
};

class OutOfRangeException: public Exception {
public:
    OutOfRangeException(int elerniKivantIndex, int maxIndex): Exception("Tulindexeles", 1) {}
};
class FileError: public Exception {
public:
    FileError(const char* file): Exception("Hiba a file megnyitasa kozben.", 2) {}
};
class KevesAdat: public Exception {
public:
    KevesAdat(int elvart): Exception("Keves adat", 4) {}
};
class NoPhoneNumber: public Exception {
public:
    NoPhoneNumber(const char* keresett): Exception("ilyen nins", 5) {}
};
class AlreadyExits: public Exception {
public:
    AlreadyExits(): Exception("Mar van ilyen", 6) {}
};

#endif //TELEFON_EXCEPTION_H
