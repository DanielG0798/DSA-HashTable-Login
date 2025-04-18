#include <iostream>
#include <limits>
#include "hash_table.h"
using namespace std;

int main() {
    HashTable table(100);

    bool loopSwitchCase = true;
    bool retryPassword = true;
    bool loginSuccess = false;

    string userName = " ";
    string oldPassword = " ";
    string passwordChange = " ";
    string currentPassword = " ";
    string passwordConfirm = " ";

    int choice = 0;
    int secondChoice = 0; // Used for account page switch case
    int nextSwitchCase = 1; // Leads to the account page after login

    while(loopSwitchCase && nextSwitchCase == 1){
        cout << " * Select an option below * " << endl;
        cout << "Option 1: Create account" << endl;
        cout << "Option 2: Login (returning user)" << endl;
        cout << "Option 0: Shutdown" << endl;
        cout << "Type an option number here: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Preventing cin to getline input buffer problem
        switch (choice) {
            case 1:
                while(retryPassword){
                    cout << " * New account * " << endl;
                    cout << "Username: ";
                    getline(cin, userName);
                    cout << "Password: ";
                    getline(cin, currentPassword);
                    cout << "Confirm Password: ";
                    getline(cin, passwordConfirm);
                    if (currentPassword != passwordConfirm) {
                        cout << "Passwords do not match, try again" << endl;
                    }else{
                        table.insertUser(userName, currentPassword);
                        retryPassword = false;
                    }
                }
                userName = " ";
                retryPassword = true;
                break;
            case 2:
                while(!loginSuccess){
                    cout << " * Returning User * " << endl;
                    cout << "Username: ";
                    getline(cin, userName);
                    cout << "Password: ";
                    getline(cin, currentPassword);
                    loginSuccess = table.loginUser(userName, currentPassword);
                }
                nextSwitchCase = 2;
                break;
            case 0:
                cout << "Shutting down, goodbye :P" << endl;
                loopSwitchCase = false;
                break;
            default:
                cout << "Please enter a valid choice option, try again" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }
    if (nextSwitchCase == 2){
        while(loopSwitchCase){
            cout << " * Profile options * " << endl;
            cout << "Option 1: Change Password" << endl;
            cout << "Option 2: Delete Account" << endl;
            cout << "Option 0: Log off" << endl;
            cout << "Type an option number here: ";
            cin >> secondChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (secondChoice) {
                case 1:
                    cout << " * Password Change * " << endl;
                    cout << "Enter your current password: ";
                    getline(cin, oldPassword);
                    cout << "Enter new password: ";
                    getline(cin, passwordChange);
                    cout << "Confirm new password: ";
                    getline(cin, passwordConfirm);

                    if (passwordChange == passwordConfirm) {
                        table.changePassword(userName, oldPassword, passwordChange);
                        loopSwitchCase = false;
                    } else {
                        cout << "New passwords do not match. Try again." << endl;
                    }
                    break;
                case 2:
                    bool deletionSuccessful;
                    cout << " * Account Deletion * " << endl;
                    cout << "WARNING - Account deletion is final!" << endl;
                    cout << "Enter password: ";
                    getline(cin,currentPassword);
                    deletionSuccessful = table.deleteUser(userName,currentPassword);
                    if(deletionSuccessful){
                        userName = " ";
                        currentPassword = " ";
                        loopSwitchCase = false;
                        break;
                    }
                    break;
                case 0:
                    cout << "Logging out session..." << endl;
                    loopSwitchCase = false;
                    break;
                default:
                    cout << "Please enter a valid choice option, try again" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
            }

        }
    }
    return 0;
}
