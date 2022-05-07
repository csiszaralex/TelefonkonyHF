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
    virtual ~Exception() throw() {}

    virtual const char* what() const throw() { return err_msg.c_str(); }
    virtual int getErrorNumber() const throw() { return err_num; }
};

class OutOfRangeException: public Exception {
public:
    OutOfRangeException(int elerniKivantIndex, int maxIndex): Exception("Tulindexeles", 1) {}
};
class FileError: public Exception {
public:
    FileError(const char* file): Exception("File hiba", -6) {}
};
class ArgumentCountError: public Exception {
public:
    ArgumentCountError(int db): Exception("Nem megfelelő argumentum szam", -3) {}
};

#endif //TELEFON_EXCEPTION_H
