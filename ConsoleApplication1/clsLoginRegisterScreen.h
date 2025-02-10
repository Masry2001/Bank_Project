#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"


using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{

private:

    static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.dateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.userName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.permissions;
    }

public:

    static void showLoginRegisterScreen() {

        if (!checkAccessRights(clsUser::enPermissions::pLoginRegister)) {
            return; // if the user dons't have the permission exit the funcion
        }

        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::getLoginRegisterList();

        string Title = "    Login Register List Screen";
        string SubTitle = "\t   (" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0) {

            cout << "\t\t\t\tNo Logins Available In the System!";

        } else {

            for (clsUser::stLoginRegisterRecord &Record : vLoginRegisterRecord) {

                _PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

