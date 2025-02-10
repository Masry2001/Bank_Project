#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

using namespace std;

class clsAddNewClientScreen : protected clsScreen
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



	static void showAddNewClientScreen() {

		if (!checkAccessRights(clsUser::enPermissions::pAddNewClient)) {
			return; // if the user dons't have the permission exit the funcion
		}

		_DrawScreenHeader("\t  Add New Client Screen");


		string accountNumber = "";

		accountNumber = clsInputValidate::readString("\nPlease Enter Account Number: ");
		while (clsBankClient::isClientExist(accountNumber))
		{
			accountNumber = clsInputValidate::readString("\nAccount Number Is Already Used, Choose another one: ");
		}


		clsBankClient newClient = clsBankClient::getAddNewClientObj(accountNumber);

		_ReadClientInfo(newClient);

		clsBankClient::enSaveResults saveResult = newClient.save();

		switch (saveResult) {
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Added Successfully :-)\n";
			_PrintClient(newClient);
			break;

		case clsBankClient::enSaveResults::svFailedEmptyObj:
			cout << "\nError Account Was Not Saved Because It's Empty.";
			break;

		case clsBankClient::enSaveResults::svFailedAccountNumberExists:
			cout << "\nError Account Was Not Added Because Account Number Exists.";
			break;
		}


	}


};

