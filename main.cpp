#include <iostream>
#include "hash_table.h"
using namespace std;

int main() {
    HashTable table(10);

    // switch case menu options go here
    // Example of inserting users
    table.insertUser("user1", "password123");
    table.insertUser("user2", "password456");

    // Example of logging in
    table.loginUser("user1", "password123");
    table.loginUser("user2", "wrongpassword"); // purposely using wrong password

    return 0;
}
