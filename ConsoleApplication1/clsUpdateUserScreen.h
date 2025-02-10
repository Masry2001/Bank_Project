#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
{

private:
    static void _ReadUserInfo(clsUser& user)
    {
        user.firstName = clsInputValidate::readString("\nEnter FirstName: ");

        user.lastName = clsInputValidate::readString("\nEnter LastName: ");

        user.email = clsInputValidate::readString("\nEnter Email: ");

        user.phone = clsInputValidate::readString("\nEnter Phone: ");

        user.password = clsInputValidate::readString("\nEnter Password: ");

        cout << "\nEnter Permission: ";
        user.permissions = _ReadPermissionsToSet();
    }

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        return Permissions;

    }

    static void _PrintUser(clsUser user)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << user.firstName;
        cout << "\nLastName    : " << user.lastName;
        cout << "\nFull Name   : " << user.fullName();
        cout << "\nEmail       : " << user.email;
        cout << "\nPhone       : " << user.phone;
        cout << "\nUser Name   : " << user.userName;
        cout << "\nPassword    : " << user.password;
        cout << "\nPermissions : " << user.permissions;
        cout << "\n___________________\n";

    }

public:

	static void showUpdateUserScreen() {
		
        _DrawScreenHeader("\tUpdate User Screen");

        clsUser user = clsUser::getUserByUserName();
        _PrintUser(user);

        cout << "\nAre you sure you want to update this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {

            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";


            _ReadUserInfo(user);

            clsUser::enSaveResults SaveResult;

            SaveResult = user.save();

            switch (SaveResult) {

            case  clsUser::enSaveResults::svSucceeded:
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(user);
                break;

            case clsUser::enSaveResults::svFailedEmptyObj:
                cout << "\nError User was not saved because it's Empty";
                break;

            }

        }

	}


};

