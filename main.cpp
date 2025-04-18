#include <iostream>
#include <limits>
#include "hash_table.h"
using namespace std;

int main() {
	HashTable table(100);

	bool loopSwitchCase = true, retryPassword = true, loginSuccess = false, deletionSuccessful = false;

	string userName, oldPassword, passwordChange, currentPassword, passwordConfirm;
	int choice, secondChoice; // Used for account page switch case
	int nextSwitchCase = 1; // Leads to the account page after login

	while(loopSwitchCase && nextSwitchCase == 1){
		cout << " * Select an option below * " << endl
			<< "Option 1: Create account" << endl
			<< "Option 2: Login (returning user)" << endl
			<< "Option 0: Shutdown" << endl
			<< "Type an option number here: ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Preventing cin to getline input buffer problem

		switch (choice) {
			case 1:
				retryPassword = true;
				while(retryPassword){
					cout << " * New account * " << endl
						<< "Username: ";
					getline(cin, userName);
					cout << "Password: ";
					getline(cin, currentPassword);
					cout << "Confirm Password: ";
					getline(cin, passwordConfirm);

					if (currentPassword != passwordConfirm) {
						cout << "Passwords do not match, try again" << endl;
						continue;
					}

					table.insertUser(userName, currentPassword);
					retryPassword = false;
				}
				break;
			case 2:
				while(!loginSuccess){
					cout << " * Returning User * " << endl
						<< "Username: ";
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
		}
	}
	if (nextSwitchCase == 2){
		while(loopSwitchCase){
			cout << " * Profile options * " << endl
				<< "Option 1: Change Password" << endl
				<< "Option 2: Delete Account" << endl
				<< "Option 0: Log off" << endl
				<< "Type an option number here: ";
			cin >> secondChoice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (secondChoice) {
				case 1:
					cout << " * Password Change * " << endl
						<< "Enter your current password: ";
					getline(cin, oldPassword);
					cout << "Enter new password: ";
					getline(cin, passwordChange);
					cout << "Confirm new password: ";
					getline(cin, passwordConfirm);

					if (passwordChange != passwordConfirm) {
						cout << "New passwords do not match. Try again." << endl;
						continue;
					}

					table.changePassword(userName, oldPassword, passwordChange);
					loopSwitchCase = false;
					break;
				case 2:
					cout << " * Account Deletion * " << endl
						<< "WARNING - Account deletion is final!" << endl
						<< "Enter password: ";
					getline(cin,currentPassword);

					deletionSuccessful = table.deleteUser(userName,currentPassword);
					if (deletionSuccessful) loopSwitchCase = false;
					continue;
					break;
				case 0:
					cout << "Logging out session..." << endl;
					loopSwitchCase = false;
					break;
				default:
					cout << "Please enter a valid choice option, try again" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}
	}

	return 0;
}
