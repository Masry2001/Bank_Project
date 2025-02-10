#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyScreen : protected clsScreen
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

	static float _ReadRate() {

		float NewRate = clsInputValidate::readNumber<float>("\nEnter New Rate: ");
		return NewRate;

	}


public:

	static void showUpdateCurrencyRateScreen()
	{

		_DrawScreenHeader("\tUpdate Currency Screen");

		string CurrencyCode = clsInputValidate::readString("\nPlease Enter Currency Code: ");


		clsCurrency Currency = clsCurrency::getCurrency(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "\nAre you sure you want to update the rate of this Currency y/n? ";

		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			cout << "\n\nUpdate Currency Rate:";
			cout << "\n____________________\n";

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);

		}

	}
};

