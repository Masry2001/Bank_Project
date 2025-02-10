#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClient client) {

		cout << "\nClient Card: ";
		cout << "\n_______________________";
		cout << "\nFull Name    : " << client.fullName();
		cout << "\nAcc. Number  : " << client.accountNumber();
		cout << "\nBalance      : " << client.accountBalance;
		cout << "\n_______________________\n";

	}

	static string _ReadAccountNumber() {
		string AccountNumber;
		AccountNumber = clsInputValidate::readString("\nPlease Enter Account Number to Transfer From: ");
		while (!clsBankClient::isClientExist(AccountNumber))
		{
			AccountNumber = clsInputValidate::readString("\nAccount number is not found, choose another one: ");
		}
		return AccountNumber;
	}

	static float ReadAmount(clsBankClient SourceClient) {

		float Amount = clsInputValidate::readNumber<float>("\nEnter Transfer Amount? ");

		while (Amount > SourceClient.accountBalance)
		{
			Amount = clsInputValidate::readNumber<float>("\nAmount Exceeds the available Balance, Enter another Amount ? ");
		}
		return Amount;
	}

public:

	static void showTransferScreen() {

		_DrawScreenHeader("\t   Transfer Screen");

		clsBankClient SourceClient = clsBankClient::find(_ReadAccountNumber());

		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::find(_ReadAccountNumber());

		_PrintClient(DestinationClient);

		float Amount = ReadAmount(SourceClient);

		cout << "\nAre you sure you want to perform this operation? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {

			if (SourceClient.transfer(Amount, DestinationClient, currentUser.userName)) {

				cout << "\nTransfer done successfully\n";
			}
			else {

				cout << "\nTransfer Faild \n";
			}
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);




	}

};

