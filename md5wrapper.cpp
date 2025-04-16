#include "md5wrapper.h"
#include "md5.h"

std::string md5wrapper::getHashFromString(const std::string& text) {
    return md5(text); // to md5.cpp
}
