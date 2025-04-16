#ifndef MD5WRAPPER_H
#define MD5WRAPPER_H

#include <string>

using namespace std;
class md5wrapper {
public:
    string getHashFromString(const string& text);
};

#endif
