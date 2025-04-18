#include <iostream>
#include <limits>
#include "hash_table.h"
using namespace std;

bool creationOptions(HashTable &ht, int &nextCase, string &userName) {
	bool loopCase = true, retryPassword = true, loginSuccess = false;
	int choice, passwordRetries;
	string currentPassword, passwordConfirm;

	while (loopCase) {
		cout << endl
			<< " * Select an option below * " << endl
			<< "Option 1: Create account" << endl
			<< "Option 2: Login (returning user)" << endl
			<< "Option 0: Shutdown" << endl
			<< "Type an option number here: ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Preventing cin to getline input buffer problem

		switch (choice) {
		case 1:
			retryPassword = true;
			while (retryPassword) {
				cout
					<< " * New account * " << endl
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

				ht.insertUser(userName, currentPassword);
				retryPassword = false;
			}
			break;
		case 2:
			loginSuccess = false;
			passwordRetries = 5;
			while (!loginSuccess && passwordRetries > 0) {
				cout << " * Returning User * " << endl
					<< "Username: ";
				getline(cin, userName);
				cout << "Password: ";
				getline(cin, currentPassword);

				loginSuccess = ht.loginUser(userName, currentPassword);
				if (!loginSuccess) cout << "Remaining retries: " << --passwordRetries << endl;
			}

			if (passwordRetries == 0) continue;

			nextCase = 2;
			return true;
			break;
		case 0:
			cout << "Shutting down, goodbye :P" << endl;
			return false;
			break;
		default:
			cout << "Please enter a valid choice option, try again" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
		}
	}
};
void profileOptions(HashTable& ht, int& nextCase, string userName) {
	bool loopCase = true, retryPassword = true, loginSuccess = false;
	int secondChoice;
	string oldPassword, passwordChange, passwordConfirm, currentPassword;

	while (loopCase) {
		cout << endl
			<< " * Profile options * " << endl
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

			ht.changePassword(userName, oldPassword, passwordChange);
			break;
		case 2:
			cout << " * Account Deletion * " << endl
				<< "WARNING - Account deletion is final!" << endl
				<< "Enter password: ";
			getline(cin, currentPassword);

			if (ht.deleteUser(userName, currentPassword)) {
				// Log out if user is deleted
				nextCase = 1;
				loopCase = false;
			};
			break;
		case 0:
			cout << "Logging out session..." << endl;
			nextCase = 1;
			loopCase = false;
			break;
		default:
			cout << "Please enter a valid choice option, try again" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
		}
	}
};

int main() {
	HashTable table(100);

	bool loopSwitchCase = true;
	int nextSwitchCase = 1; // Leads to the account page after login
	string userName;

	while (loopSwitchCase) {
		if (nextSwitchCase == 1) {
			loopSwitchCase = creationOptions(table, nextSwitchCase, userName);
		}
		if (nextSwitchCase == 2) {
			profileOptions(table, nextSwitchCase, userName);
		}
	}

	return 0;
}
