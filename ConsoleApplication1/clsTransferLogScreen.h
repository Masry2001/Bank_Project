#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:

    static void _PrintTransferLogRecordLine(clsBankClient::stTransferRecord TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferLogRecord.dateTime;
        cout << "| " << setw(10) << left << TransferLogRecord.sourceAccNum;
        cout << "| " << setw(10) << left << TransferLogRecord.destinationAccNum;
        cout << "| " << setw(10) << left << TransferLogRecord.amount;
        cout << "| " << setw(10) << left << TransferLogRecord.sourceAccBal;
        cout << "| " << setw(10) << left << TransferLogRecord.destinationAccBal;
        cout << "| " << setw(20) << left << TransferLogRecord.userName;

    }


public: 
	static void showTransferLogScreen() {

		vector <clsBankClient::stTransferRecord> vTransferLogRecords = clsBankClient::getTransferLogList();

		string title = "    Login Register List Screen";
 		string subTitle = "\t   (" + to_string(vTransferLogRecords.size()) + ") Record(s).";
		_DrawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "S.Acct";
        cout << "| " << left << setw(10) << "D.Acct";
        cout << "| " << left << setw(10) << "Ammount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(20) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecords.size() == 0) {

            cout << "\t\t\t\tNo Transfers Available In the System!";

        } else {

            for (clsBankClient::stTransferRecord& record : vTransferLogRecords) {

                _PrintTransferLogRecordLine(record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;




	}
};

