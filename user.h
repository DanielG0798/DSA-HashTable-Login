// user.h
#ifndef USER_H
#define USER_H

#include <string>

using namespace std;
class User {
public:
    string username;
    string passwordHash;
    bool isEmpty;

    User() : isEmpty(true) {}  // Constructor initializes isEmpty to true
    User(const string& u, const string& h) : username(u), passwordHash(h), isEmpty(false) {}

    void clear() {
        username = "";
        passwordHash = "";
        isEmpty = true;  // Reset to empty state
    }
};

#endif
