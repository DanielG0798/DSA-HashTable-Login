#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include "user.h"
#include "md5wrapper.h"

using namespace std;
class HashTable {
private:
    vector<User> table;     // Table for storing user accounts
    int tableSize;          // Size of the hash table

    int hashFunction(const string& key);        // Computes hash index for a key (similar to h%7 in class)
    int findIndex(const string& username);      // Collision detection (linear probing)

public:
    explicit HashTable(int size);
    bool insertUser(const string& username, const string& password);    // Adds user
    bool loginUser(const string& username, const string& password);     // Verifies login
};

#endif
