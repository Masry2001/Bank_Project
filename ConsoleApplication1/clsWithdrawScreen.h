#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;


class clsWithdrawScreen : protected clsScreen
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

	static void showWithdrawScreen() {

		_DrawScreenHeader("\t   Withdraw Screen");

		clsBankClient client = clsBankClient::getClientByAccountNumber();
		_PrintClient(client);

		float amount = 0;
		amount = clsInputValidate::readNumber<float>("\nPlease enter withdraw amount? ");

		cout << "\nAre you sure you want to perform this transaction? Y/N? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {

			if (client.withdraw(amount))
			{
				cout << "\nAmount Withdrew Successfully.\n";
				cout << "\nNew Balance Is: " << client.accountBalance;
			}
			else
			{
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmout to withdraw is: " << amount;
				cout << "\nYour Balance is: " << client.accountBalance;

			}

		}
		else {
			cout << "\nOperation was cancelled.\n";
		}

	}

};

