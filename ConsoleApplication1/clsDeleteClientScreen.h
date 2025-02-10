#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
	
private:
	static void _PrintClient(clsBankClient client) {

		cout << "\nClient Card: ";
		cout << "\n_______________________";
		cout << "\nFirst Name   : " << client.firstName;
		cout << "\nLast Name    : " << client.lastName;
		cout << "\nFull Name    : " << client.fullName();
		cout << "\nEmail        : " << client.email;
		cout << "\nPhone        : " << client.phone;
		cout << "\nAcc. Number  : " << client.accountNumber();
		cout << "\nPassword     : " << client.pinCode;
		cout << "\nBalance      : " << client.accountBalance;
		cout << "\n_______________________\n";

	}

public:
	static void showDeleteClientScreen() {

		if (!checkAccessRights(clsUser::enPermissions::pDeleteClient)) {
			return; // if the user dons't have the permission exit the funcion
		}

		_DrawScreenHeader("\tDelete Client Screen");

		clsBankClient client = clsBankClient::getClientByAccountNumber();
		_PrintClient(client);

		cout << "\nAre You Sure You Want To Delete This Client Y/N? ";
		char answer;
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {

			if (client.Delete()) {
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(client);
			}
			else {
				cout << "\nError Client Was Not Deleted.\n";
			}
		}

	}



};

