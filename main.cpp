// main.cpp
#include <iostream>
#include "hashtable.h"

using namespace std;
int main() {

    HashTable table(10); // Hash table with size 10

    // to do: switch case menu options go here


    // Example of registering users
    table.insertUser("user1", "password123");
    table.insertUser("user2", "password456");

    // Example of login attempts
    table.loginUser("user1", "password123");   // should succeed, username and passwords match
    table.loginUser("user2", "wrongpassword"); // purposely using wrong password, should fail

    return 0;
}
