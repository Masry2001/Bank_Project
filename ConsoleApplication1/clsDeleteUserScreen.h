#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{

private:
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
	static void showDeleteUserScreen() {

        _DrawScreenHeader("\tDelete User Screen");

        clsUser user = clsUser::getUserByUserName();
        _PrintUser(user);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {

            if (user.Delete() ) {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(user);
            }
            else {
                cout << "\nError User Was not Deleted\n";
            }
        }

	}

};

