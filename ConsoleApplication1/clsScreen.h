#pragma once

#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{

protected:

	static void _DrawScreenHeader(string title, string subTitle = "") {
	
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << title;
        if (subTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << subTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        CurrentUserAndDate();
	}

    static bool checkAccessRights(clsUser::enPermissions permission) {

        if (!currentUser.checkAccessPermission(permission)) {

            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else {
            return true;
        }


    }

    static void CurrentUserAndDate() {
        cout << "\t\t\t\t\t" << "User: " << currentUser.userName << "\t\t" << "Permissions: " << currentUser.permissions << endl;
        cout << "\t\t\t\t\t" << "Date: " << clsDate::dateToString(clsDate()) << "\n\n";
    }


};

