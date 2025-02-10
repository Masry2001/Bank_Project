#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrenciesList.h"
#include "clsInputValidate.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{

private:

    enum enCurrencyExchangeOptions {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
        eCurrencyCalculator = 4, eMainMenu = 5
    };

    static short _ReadCurrencyExchangeMenuOption() {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::readNumberBetween<short>(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static  void _GoBackToCurrencyExchangeMenu() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Exchange Menu...\n";

        system("pause>0");
        showCurrencyExchangeMenu();
    }

    static void _ShowCurrenciesListScreen() {
        
        clsCurrenciesList::showCurrenciesListScreen();

    }

    static void _ShowFindCurrencyScreen() {
        clsFindCurrencyScreen::showFindCurrencyScreen();

    }

    static void _ShowUpdateCurrencyScrren() {
        clsUpdateCurrencyScreen::showUpdateCurrencyRateScreen();

    }

    static void _ShowCurrencyCalulatorScreen() {
        clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();

    }


    static void _PerfromMainMenueOption(enCurrencyExchangeOptions currencyExchangeOption) {

        switch (currencyExchangeOption) {

        case enCurrencyExchangeOptions::eListCurrencies:
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeOptions::eUpdateRate:
            system("cls");
            _ShowUpdateCurrencyScrren();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalulatorScreen();
            _GoBackToCurrencyExchangeMenu();
            break;

        case enCurrencyExchangeOptions::eMainMenu:
            
            break;

        }

    }



public:

	static void showCurrencyExchangeMenu() {

        system("cls");

		_DrawScreenHeader("Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enCurrencyExchangeOptions)_ReadCurrencyExchangeMenuOption());

	}
};

