#pragma once

#include <iostream>
#include "clsScreen.h"
//#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsUpdateClientScreen : clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& client) {

		client.firstName = clsInputValidate::readString("Please Enter First Name     : ");
		client.lastName = clsInputValidate::readString("Please Enter Last Name      : ");

		client.email = clsInputValidate::readString("Please Enter Email          : ");
		client.phone = clsInputValidate::readString("Please Enter Phone          : ");

		client.pinCode = clsInputValidate::readString("Please Enter Pin Code       : ");

		client.accountBalance = clsInputValidate::readNumber<float>("Please Enter Account Balance: ");

	}

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

	static void showUpdateClientScreen() {

		if (!checkAccessRights(clsUser::enPermissions::pUpdateClients)) {
			return; // if the user dons't have the permission exit the funcion
		}

		_DrawScreenHeader("\t  Update Client Screen");

		clsBankClient client = clsBankClient::getClientByAccountNumber();
		_PrintClient(client);

		cout << "Are You Sure You Want To Update The Client? Y/N ?";
		char answer = 'n';
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {

			cout << "\n\nUpdate Client Info: ";
			cout << "\n______________________\n";

			_ReadClientInfo(client);

			clsBankClient::enSaveResults saveResult = client.save();

			switch (saveResult) {
			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\nAccount Updated Successfully :-)\n";
				_PrintClient(client);
				break;

			case clsBankClient::enSaveResults::svFailedEmptyObj:
				cout << "\nError Account Was Not Saved Because It's Empty";
				break;
			}
		}


	}

}; // class end

