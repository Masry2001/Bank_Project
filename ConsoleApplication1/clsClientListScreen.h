#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUser.h"

class clsClientListScreen : protected clsScreen {

private:
	static void printClientRecord(clsBankClient client) {

		cout << setw(8) << left << "" << "| " << setw(15) << left << client.accountNumber();
		cout << "| " << setw(20) << left << client.fullName();
		cout << "| " << setw(12) << left << client.phone;
		cout << "| " << setw(20) << left << client.email;
		cout << "| " << setw(10) << left << client.pinCode;
		cout << "| " << setw(12) << left << client.accountBalance;

	}


public:

	static void showClientsList() {

		if (!checkAccessRights(clsUser::enPermissions::pListClients)) {
			return; // if the user dons't have the permission exit the funcion
		}

		vector <clsBankClient> vClients = clsBankClient::getClientsList();

		string Title = "\t  Client List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;



		if (vClients.size() == 0) {
			cout << "\t\t\t\tNo Clients Available In The System!";
		}
		else {
			for (clsBankClient& client : vClients) {

				printClientRecord(client);
				cout << endl;

			}
			cout << endl << string(100, '_') << endl;
		}


	}


};

