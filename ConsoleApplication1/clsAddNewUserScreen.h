#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

using namespace std;

class clsAddNewUserScreen : protected clsScreen
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
        
        cout << "\nLogin Registers? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
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

    static void showAddNewUserScreen() {

        _DrawScreenHeader("\t  Add New User Screen");

        string userName = "";

        userName = clsInputValidate::readString("\nPlease Enter UserName: ");
        while (clsUser::isUserExist(userName))
        {
            userName = clsInputValidate::readString("\nUserName Is Already Used, Choose another one: ");
        }

        clsUser newUser = clsUser::getAddNewUserObj(userName);

        _ReadUserInfo(newUser);

        clsUser::enSaveResults saveResult;

        saveResult = newUser.save();

        switch (saveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(newUser);
            break;
        }
        case clsUser::enSaveResults::svFailedEmptyObj:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFailedUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
        }
    }
};

