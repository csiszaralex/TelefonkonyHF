#ifndef TELEFON_EXCEPTION_H
#define TELEFON_EXCEPTION_H

#include <exception>
#include <string>

class Exception: public std::exception {
protected:
    int err_num;
    int err_offset;
    std::string err_msg;
public:
    Exception(const std::string msg, int num, int offset): err_num(num), err_offset(offset), err_msg(msg) {}
    virtual ~Exception() throw() {}

    virtual const char* what() const throw() { return err_msg.c_str(); }
    virtual int getErrorNumber() const throw() { return err_num; }
    virtual int getErrorOffset() const throw() { return err_offset; }
};

class OutOfRangeException: public Exception {
public:
    OutOfRangeException(int elerniKivantIndex, int maxIndex): Exception("Tulindexeles", 1, 5) {}
};
class IsEmptyException: public Exception {
public:
    IsEmptyException(): Exception("Ez már üres", 2, 1) {}
};

#endif //TELEFON_EXCEPTION_H
