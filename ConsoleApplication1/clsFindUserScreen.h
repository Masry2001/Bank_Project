#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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

	static void showFindUserScreen() {

        _DrawScreenHeader("\tFind User Screen");

        clsUser user = clsUser::getUserByUserName();

        if (user.isEmpty()) {
            cout << "\nUser Was not Found :-(\n";
        }
        else {
            cout << "\nUser Found :-)\n";
        }

        _PrintUser(user);

	}
};

