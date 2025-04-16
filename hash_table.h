#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include "user.h"
#include "md5_wrapper.h"

using namespace std;
class HashTable {
private:
    vector<User> table;
    int tableSize;

    int hashFunction(const string& key);
    int findIndex(const string& username);

public:
    explicit HashTable(int size);
    bool insertUser(const string& username, const string& password);
    bool loginUser(const string& username, const string& password);
};

#endif
