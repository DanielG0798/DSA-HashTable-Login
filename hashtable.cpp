#include "hashtable.h"
#include <iostream>

using namespace std;

// Constructor - initializes hash table with a given size
HashTable::HashTable(int size) : tableSize(size) {
    table.resize(tableSize);
}

// Hash function using polynomial rolling hash
int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % tableSize;
    }
    return hash;
}

// Finds index for an existing username using linear probing
int HashTable::findIndex(const string& username) {
    int index = hashFunction(username);
    int originalIndex = index;

    // Linear probing process
    // While table isn't empty or we haven't found the username, continue on.
    while (!table[index].isEmpty && table[index].username != username) {
        index = (index + 1) % tableSize;  // Linear probing formula
        if (index == originalIndex) {
            return -1;  // Table is full or user not found
        }
    }
    return index;
}

// Registers new user with MD5 encrypted password
bool HashTable::insertUser(const string& username, const string& password) {
    int index = findIndex(username);
    if (index == -1 || !table[index].isEmpty) {
        cout << "User already exists or table is full.\n";
        return false;
    }

    // Here, we hash the password
    md5wrapper md5;
    string hashedPassword = md5.getHashFromString(password);

    // Then store the data
    table[index].username = username;
    table[index].passwordHash = hashedPassword;
    table[index].isEmpty = false;

    cout << "User registered successfully.\n";
    return true;
}

// Authenticates user by comparing MD5 hashes
bool HashTable::loginUser(const string& username, const string& password) {
    int index = findIndex(username);
    if (index == -1 || table[index].isEmpty) {
        cout << "User not found.\n";
        return false;
    }

    // Hash provided password for comparison later
    md5wrapper md5;
    string hashedPassword = md5.getHashFromString(password);

    // Verify hashing
    cout << "Hashed password for " << username << ": " << hashedPassword << endl;

    // Compare stored hash with computed hash. If they're the same, successful. If not, not.
    if (table[index].passwordHash == hashedPassword) {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Incorrect password.\n";
        return false;
    }
}
