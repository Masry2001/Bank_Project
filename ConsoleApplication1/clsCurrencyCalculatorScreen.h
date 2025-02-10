#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
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

	static void _CalculationResults(float amount, clsCurrency currency1, clsCurrency currency2) {


		cout << "\nConvert From: \n";
		_PrintCurrency(currency1);

		float amountInUSD = currency1.convertToUSD(amount);

		cout << amount << " " << currency1.CurrencyCode() << " = " << amountInUSD << " USD\n";

		if (currency2.CurrencyCode() == "USD") {
			return;
		}

		cout << "\nConverting From USD TO: \n";

		_PrintCurrency(currency2);

		float amountInCurrency2 = currency1.convertToOtherCurrency(amount, currency2);

		cout << amount << " " << currency1.CurrencyCode() << " = " << amountInCurrency2 << " " << currency2.CurrencyCode() << endl;

	}

public:

	static void showCurrencyCalculatorScreen() {

		char Continue = 'y';

		while (Continue == 'y' || Continue == 'Y') {

			system("cls");

			_DrawScreenHeader("\t  Update Currency Screen");

			string code1 = clsInputValidate::readString("\nPlease Enter Currency1 Code: \n");
			clsCurrency currency1 = clsCurrency::getCurrency(code1);

			string code2 = clsInputValidate::readString("\nPlease Enter Currency2 Code: \n");
			clsCurrency currency2 = clsCurrency::getCurrency(code2);

			float amount = clsInputValidate::readNumber <float>("\nEnter Amount To Exchange: \n");

			_CalculationResults(amount, currency1, currency2);

			cout << "\nDo You Want To Perform Another Calculation? y/n? ";
			cin >> Continue;
		}




		


	}

};

