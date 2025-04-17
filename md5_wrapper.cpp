#include "md5.h"
#include "md5_wrapper.h"
using namespace std;

string md5wrapper::getHashFromString(const string& text) {
    return md5(text);
}
