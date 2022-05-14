#include "string.h"



//bool String::compare(String& str) const {
//    if(len != str.len) return false;
//    for(size_t i = 0; i<len;i++) {
//        if(data[i] != str.data[i]) return false;
//    }
//    return true;
//}
//bool String::compare(const char* c)const  {
//    String tmp(c);
//    bool all = compare(tmp);
//    return all;
//}


//std::istream& operator>>(std::istream& is, String& str) {
//    char c;
//    str = String();
//    std::ios_base::fmtflags flags = is.flags();
//    is.setf(std::ios_base::skipws);
//    while(is >> c) {
//        is.unsetf(std::ios_base::skipws);
//        if(c == ' ' || c == '\n') {
//            is.putback(c);
//            break;
//        } else {
//            str += c;
//        }
//    }
//    is.setf(flags);
//    return is;
//}
