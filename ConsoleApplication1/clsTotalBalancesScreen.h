#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{

private:

    static void PrintClientRecordBalanceLine(clsBankClient client) {
        cout << setw(25) << left << "" << "| " << setw(15) << left << client.accountNumber();
        cout << "| " << setw(40) << left << client.fullName();
        cout << "| " << setw(12) << left << client.accountBalance;
    }

public:

    static void ShowTotalBalances()
    {

        vector <clsBankClient> vClients = clsBankClient::getClientsList();

        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;


        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {
                PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        float TotalBalances = clsBankClient::getTotalBalances();
        cout << setw(8) << left << "" << "\t\t\t\t\t\t\t     Total Balances = " << TotalBalances << endl;
        cout << setw(8) << left << "" << "\t\t\t\t  ( " << clsUtil::numberToText(TotalBalances) << ")";
    }
};

