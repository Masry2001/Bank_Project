#pragma once

#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "Global.h"


using namespace std;

class clsLoginScreen : protected clsScreen
{

private:

    static bool _Login() {

        bool LoginFaild = false;

        string userName, password;
        short trials = 3;

        do {

            if (LoginFaild)
            {
                trials--;
                cout << "\nInvlaid Username/Password!\n";
                cout << "You have " << trials << " Trial(s) to login.\n";

                if (trials == 0) {
                    cout << "\n______________________________________";
                    cout << "\nYou Are Locked After 3 Failed Trials.\n";
                    cout << "______________________________________\n";
                    return false;
                }
            }

            userName = clsInputValidate::readString("\nEnter userName: ");
            password = clsInputValidate::readString("\nEnter Password: ");

            currentUser = clsUser::find(userName, password);

            LoginFaild = currentUser.isEmpty();

        } while (LoginFaild);

        currentUser.RegisterLogin();

        clsMainScreen::showMainMenu();
        return true;

    }

public:

    static bool ShowLoginScreen() {
        system("cls");
        _DrawScreenHeader("\t     Login Screen");
        return _Login();

    }

};

