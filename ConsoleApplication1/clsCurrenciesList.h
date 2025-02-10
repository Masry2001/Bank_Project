#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrenciesList : protected clsScreen
{

private:

    static void _PrintCurrencyRecordLine(clsCurrency currency)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << currency.Country();
        cout << "| " << setw(10) << left << currency.CurrencyCode();
        cout << "| " << setw(40) << left << currency.CurrencyName();
        cout << "| " << setw(15) << left << currency.Rate();


    }

public:
	
	static void showCurrenciesListScreen() {

            vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

            string Title = "\t  Currencies List Screen";
            string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currency.";

            _DrawScreenHeader(Title, SubTitle);

            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "______________________________________________\n" << endl;

            cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
            cout << "| " << left << setw(10) << "Code";
            cout << "| " << left << setw(40) << "Currency Name";
            cout << "| " << left << setw(15) << "Rate/(1$)";
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "______________________________________________\n" << endl;

            if (vCurrencies.size() == 0)
                cout << "\t\t\t\tNo Currencies Available In the System!";
            else

                for (clsCurrency& currency : vCurrencies) {

                    _PrintCurrencyRecordLine(currency);
                    cout << endl;
                }

            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "______________________________________________\n" << endl;
        

	}
};

