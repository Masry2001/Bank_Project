#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
	
private:

	static void _PrintCurrency(clsCurrency currency) {

		cout << "\nCurrency Card: ";
		cout << "\n_______________________";
		cout << "\nCountry   : " << currency.Country();
		cout << "\nCode      : " << currency.CurrencyCode();
		cout << "\nName      : " << currency.CurrencyName();
		cout << "\nRate      : " << currency.Rate();
		cout << "\n_______________________\n";

	}

	static void _ShowResults(clsCurrency currency) {

		if (!currency.IsEmpty()) {

			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(currency);

		}
		else {
			cout << "\nCurrency Was Not Found :-(\n";

		}

	}



public:

	static void showFindCurrencyScreen() {

		_DrawScreenHeader("\t  Find Currency Screen");

		cout << "Find By: [1] Code Or [2] Country? ";
		short num = clsInputValidate::readNumberBetween<short>(1, 2, "Enter [1] For Find By Code Or [2] For Find By Country ");

		if (num == 1) {

			string code = clsInputValidate::readString("\nPlease Enter Country Code: ");

			clsCurrency currency = clsCurrency::FindByCode(code);
			_ShowResults(currency);

		}
		else if (num == 2) {

			string country = clsInputValidate::readString("\nPlease Enter Country Name: ");

			clsCurrency currency = clsCurrency::FindByCountry(country);
			_ShowResults(currency);

		}



	}


};

