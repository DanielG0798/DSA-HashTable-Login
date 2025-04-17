#include <iostream>
#include "hash_table.h"
using namespace std;

HashTable::HashTable(int size) : tableSize(size) {
    table.resize(tableSize);
}

int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % tableSize;
    }
    return hash;
}

int HashTable::findIndex(const string& username) {
    int index = hashFunction(username), originalIndex = index;

    while (!table[index].isEmpty && table[index].username != username) {
        index = (index + 1) % tableSize;  // Linear probing
        if (index == originalIndex) {
            return -1;  // Table is full or user not found
        }
    }
    return index;
}

bool HashTable::insertUser(const string& username, const string& password) {
    int index = findIndex(username);
    if (index == -1 || !table[index].isEmpty) {
        cout << "User already exists or table is full." << endl;
        return false;
    }

    md5wrapper md5;
    string hashedPassword = md5.getHashFromString(password);
    table[index].username = username;
    table[index].passwordHash = hashedPassword;
    table[index].isEmpty = false;

    cout << "User registered successfully." << endl;
    return true;
}

bool HashTable::loginUser(const string& username, const string& password) {
    int index = findIndex(username);
    if (index == -1 || table[index].isEmpty) {
        cout << "User not found." << endl;
        return false;
    }

    md5wrapper md5;
    string hashedPassword = md5.getHashFromString(password);
    cout << "Hashed password for " << username << ": " << hashedPassword << endl;

    if (table[index].passwordHash != hashedPassword) {
        cout << "Incorrect password." << endl;
        return false;
    }

    cout << "Login successful!" << endl;
    return true;
}
