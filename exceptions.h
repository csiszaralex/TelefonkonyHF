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
    Exception(const std::string msg, int num, int offset): err_msg(msg), err_num(num), err_offset(offset) {}
    virtual ~Exception() throw() {}

    virtual const char* what() const throw() {
        return err_msg.c_str();
    }
    virtual int getErrorNumber() const throw() {
        return err_num;
    }
    virtual int getErrorOffset() const throw() {
        return err_offset;
    }
};

class OutOfRangeException: public Exception {
public:
    OutOfRangeException(): Exception("Tulindexeles", 1, 5) {}
};

#endif //TELEFON_EXCEPTION_H
