#include <iostream>
#include "hash_table.h"

using namespace std;

HashTable::HashTable(int size) : tableSize(size) {
    table.resize(tableSize);
}
// Hash Table insertion formula
int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for (char c : key) {                    // Looping through each letter in the given username (key)
        hash = (hash * 31 + c) % tableSize; // Prime number helps with distribution
    }
    return hash; // Final index in the table
}
// Helper function for finding users and collision handling
int HashTable::findIndex(const string& username) {
    int index = hashFunction(username), originalIndex = index;

    while (!table[index].isEmpty && table[index].username != username) {
        index = (index + 1) % tableSize;  // Linear probing collision handling
        if (index == originalIndex) {
            return -1;  // Table is full or user not found
        }
    }
    return index;
}
// Add user to table
bool HashTable::insertUser(const string& username, const string& password) {
    int index = findIndex(username);
    if (index == -1 || !table[index].isEmpty) {
        cout << "User already exists or table is full." << endl;
        return false;
    }
    // Password hashing function (MD5)
    md5wrapper md5;
    string hashedPassword = md5.getHashFromString(password);
    cout << "Hashed password for " << username << ": " << hashedPassword << endl;

    table[index].username = username;
    table[index].passwordHash = hashedPassword;
    table[index].isEmpty = false;

    cout << "User registered successfully." << endl;
    return true;
}
// User login
bool HashTable::loginUser(const string& username, const string& password) {
    int index = findIndex(username);
    if (index == -1 || table[index].isEmpty) {
        cout << "User not found, try again." << endl;
        return false;
    }
    // Check if account is locked due to too many failed attempts
    if (table[index].loginAttempts >= 3) {
        cout << false;
    }

    md5wrapper md5;
    string hashedPassword = md5.getHashFromString(password);

    if (table[index].passwordHash != hashedPassword) {
        table[index].loginAttempts++;
        cout << "Incorrect password. Attempt " << table[index].loginAttempts << "/3." << endl;
        return false;
    }
    // Successful login
    table[index].loginAttempts = 0; // Reset attempts on success
    cout << "Login successful!" << endl;
    return true;
}

// Change password
bool HashTable::changePassword(const std::string& username, const std::string& oldPassword,
                               const std::string& newPassword) {
    int index = findIndex(username);

    if (index == -1 || table[index].isEmpty) {
        std::cout << "User not found." << endl;
        return false;
    }

    md5wrapper md5;
    std::string hashedOldPassword = md5.getHashFromString(oldPassword);

    // Check if the old password matches the one in the table
    if (table[index].passwordHash == hashedOldPassword) {
        std::string hashedNewPassword = md5.getHashFromString(newPassword);
        table[index].passwordHash = hashedNewPassword;
        std::cout << "Password changed successfully." << endl;
        return true;
    } else {
        std::cout << "Incorrect old password." << endl;
        return false;
    }
}

// Delete user
bool HashTable::deleteUser(const std::string& username, const std::string& password) {
    int index = findIndex(username);

    if (index == -1 || table[index].isEmpty) {
        std::cout << "User not found." << endl;
        return false;
    }

    md5wrapper md5;
    std::string hashedPassword = md5.getHashFromString(password);

    // Check if the password matches the one in the table
    if (table[index].passwordHash == hashedPassword) {
        table[index].isEmpty = true;
        std::cout << "Account deleted successfully." << endl;
        return true;
    } else {
        std::cout << "Incorrect password." << endl;
        return false;
    }
}