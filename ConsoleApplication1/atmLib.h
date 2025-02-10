#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
#include "clsInputValidate.h"


using namespace std;


namespace atmLib {


	const string filePath = "clientDataFile.txt";

	struct stClientData {
		string accountNumber = "unknown";
		string pinCode = "unkonwn";
		string name = "unknown";
		string phone = "unknown";
		int accountBalance = 0;
		bool markForDelete = false;
	};

	stClientData currentClient;

	enum enMainMenuOption {

		eQuickWithdraw = 1,
		eNormalWithdraw = 2,
		eDeposit = 3,
		eCheckBalance = 4,
		eLogout = 5,
	};

	void loginScreen();
	void mainMenuScreen();
	void quickWithdrawOptions();


	stClientData readClientData() {

		stClientData client;
		cout << "\nEnter Account Number? ";
		cin >> client.accountNumber;
		cout << "\nEnter Pincode? ";
		cin >> client.pinCode;

		return client;
	}


	void loginScreenHeader() {
		// course 8
		system("cls");
		cout << std::string(50, '=');
		cout << "\n\t\Login Screen \n";
		cout << std::string(50, '=') << endl;
	}


	stClientData convertLineToRecord(string clientRecord, string seprator = "#//#") {

		vector <string> vString = clsString::splitEachWordOfStringInToVector(clientRecord, seprator);
		stClientData client;

		client.accountNumber = vString[0];
		client.pinCode = vString[1];
		client.name = vString[2];
		client.phone = vString[3];
		client.accountBalance = stoi(vString[4]);

		return client;
	}

	string convertRecordToLine(stClientData client, string seprator = "#//#") {
		string clientRecord = "";
		clientRecord += client.accountNumber + seprator;
		clientRecord += client.pinCode + seprator;
		clientRecord += client.name + seprator;
		clientRecord += client.phone + seprator;
		clientRecord += to_string(client.accountBalance);
		return clientRecord;
	}


	vector <stClientData> loadClientsDataFromFile() {

		vector <stClientData> vClients;

		fstream clientDataFile;
		clientDataFile.open(filePath, ios::in);

		if (clientDataFile.is_open()) {
			string line;
			stClientData client;

			while (getline(clientDataFile, line)) {
				client = convertLineToRecord(line);
				vClients.push_back(client);
			}

			clientDataFile.close();
		}
		return vClients;
	}

	vector <stClientData> vClients = loadClientsDataFromFile();


	bool IsAccountNumberAndPinRight(string accountNumber, string pinCode, stClientData& currentClient) {


		for (stClientData& client : vClients) {
			if (client.accountNumber == accountNumber && client.pinCode == pinCode) {
				currentClient = client;
				return 1;
			}
		}
		return 0;
	}

	void checkBalance() {
		cout << std::string(50, '=');
		cout << "\n\t\tATM Main Menu Screen \n";
		cout << std::string(50, '=');

		cout << "\nYour Balance is " << currentClient.accountBalance << endl;
	}

	void saveClientsDataToFile(vector<stClientData>& vClients) {

		fstream myFile;
		myFile.open(filePath, ios::out);

		string clientRecord;

		if (myFile.is_open()) {

			for (stClientData& client : vClients) {

					clientRecord = convertRecordToLine(client);
					myFile << clientRecord << endl;

			}
			myFile.close();
		}
	}



	//Deposite

	void depositeToClient() {

		char answer = 'n';

		float depositeAmount = clsInputValidate::readNumber<float>("\nPlease enter deposite amount? ");

		cout << "\nAre you sure you want to perform this transaction y/n\n";
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {

			for (stClientData& c : vClients) {
				if (c.accountNumber == currentClient.accountNumber) {
					c.accountBalance += depositeAmount;
					currentClient.accountBalance += depositeAmount;
					break;
				}
			}

			saveClientsDataToFile(vClients);


			cout << "\nDone Successfully, New Balance is " << currentClient.accountBalance << endl;
		}

		

	}

	void depositeScreen() {
		cout << std::string(50, '-');
		cout << "\n\tDeposite Screen\n";
		cout << std::string(50, '-');

		depositeToClient();

	}


	//Normale withdraw
	float withdrawConditions() {

		int withdrawAmount = clsInputValidate::readNumber<int>("\nPlease Enter Withdraw Amount (multible of 5)? ");

		while (true) {

			if (withdrawAmount > currentClient.accountBalance) {
				cout << "Withdraw Amount Exceeds The Balance. You Can Withdraw Up To: " << currentClient.accountBalance;
			}
			else if (withdrawAmount % 5 != 0) {
				cout << "Withdraw Amount must be a multiple of 5.";
			}
			else {
				// Valid withdrawal amount
				break;
			}

			withdrawAmount = clsInputValidate::clsInputValidate::readNumber<int>("\nPlease Enter a Valid Withdraw Amount: ");
		}
		return withdrawAmount;

	}

	void withdrawFromClient() {


		int withdrawAmount = withdrawConditions();

		char answer = 'n';
		cout << "\nAre you sure you want to perform this transaction y/n\n";
		cin >> answer;

		if (answer == 'y' || answer == 'Y') {

			for (stClientData& c : vClients) {
				if (c.accountNumber == currentClient.accountNumber) {

					c.accountBalance -= withdrawAmount;
					currentClient.accountBalance -= withdrawAmount;
					break;
				}
			}

			saveClientsDataToFile(vClients);

			cout << "\nDone Successfully, New Balance is " << currentClient.accountBalance << endl;

		}

	}

	void normalWithdraw() {
		cout << std::string(50, '-');
		cout << "\n\tNormal Withdraw\n";
		cout << std::string(50, '-');

		withdrawFromClient();

	}

	//Quick Withdraw

	void quickWithdraw(int withdrawAmount) {
		char confirmation;
		cout << "Are You Sure You Want To Perform This Transaction? y/n? ";
		cin >> confirmation;

		if (confirmation != 'y' && confirmation != 'Y') {
			cout << "Transaction Canceled. Your Balance: " << currentClient.accountBalance;
			return;
		}

		if (withdrawAmount > currentClient.accountBalance) {
			system("cls");
			cout << "\nWithdraw Amount Exceeds The Balance. You Can Withdraw Up To: " << currentClient.accountBalance << endl;
			cout << "press any key to continue...";
			system("pause>0");
			system("cls");
			quickWithdrawOptions();	
			return;
		}

		// Withdrawal options or additional processing

		// Update balances in the vector and save to file
		for (stClientData& c : vClients) {
			if (c.accountNumber == currentClient.accountNumber) {
				c.accountBalance -= withdrawAmount;
				currentClient.accountBalance -= withdrawAmount;
				break;
			}
		}

		saveClientsDataToFile(vClients);
		cout << "Transaction Successful. Your New Balance: " << currentClient.accountBalance << endl;
	}

	void choosingFromQucikWithdraw(short option) {

		switch (option) {
			case 1:
				quickWithdraw(20);
				break;
			case 2:
				quickWithdraw(50);
				break;
			case 3:
				quickWithdraw(100);
				break;
			case 4:
				quickWithdraw(200);
				break;
			case 5:
				quickWithdraw(400);
				break;
			case 6:
				quickWithdraw(600);
				break;
			case 7:
				quickWithdraw(800);
				break;
			case 8:
				quickWithdraw(1000);
				break;
			case 9:
				mainMenuScreen();
				break;
			default:
				cout << "\nEnter Number From 1 to 9\n";

			
	}


	}

	short readQuickWithdrawOption() {
		short option = 0;
		while (option < 1 || option > 9) {

			cout << "Choose What To Do From [1] to [9]? ";
			cin >> option;

		}
		return option;
	}

	void quickWithdrawOptions() {
		cout << std::string(50, '=');
		cout << "\n\t\tQuick Withdraw \n";
		cout << std::string(50, '=');
		cout << "\n\t[1] 20 \t\t[2] 50\n";
		cout << "\t[3] 100\t\t[4] 200\n";
		cout << "\t[5] 400\t\t[6] 600\n";
		cout << "\t[7] 700\t\t[8] 1000\n";
		cout << "\t[9] Exit\n";
		cout << std::string(50, '=');
		cout << "\nYour Balance is " << currentClient.accountBalance << endl;
	
		choosingFromQucikWithdraw(readQuickWithdrawOption());

		

	}





	void goBackToMainMenu() {
		cout << "\n\n Press Any Key To Go Back To Main Menu...";
		system("pause>0");
		mainMenuScreen();
	}

	void choosingFromMainMenu(enMainMenuOption mainMenuOption) {


		switch (mainMenuOption) {
		case enMainMenuOption::eQuickWithdraw:
			system("cls");
			quickWithdrawOptions();
			goBackToMainMenu();
			break;
		case enMainMenuOption::eNormalWithdraw:
			system("cls");
			normalWithdraw();
			goBackToMainMenu();
			break;
		case enMainMenuOption::eDeposit:
			system("cls");
			depositeScreen();
			goBackToMainMenu();
			break;
		case enMainMenuOption::eCheckBalance:
			system("cls");
			checkBalance();
			goBackToMainMenu();
			break;
		case enMainMenuOption::eLogout:
			system("cls");
			loginScreen();
			break;
		default:
			cout << "not a valid number please choose from 1 to 7";
			goBackToMainMenu();
		}

	}

	short readMainMenuOption() {
		cout << "\nChoose What Do You Want To Do? [1 to 5]? ";
		short option = 0;
		cin >> option;
		return option;
	}

	void mainMenuScreen() {
		system("cls");
		cout << "Hello " << currentClient.name;
		cout << endl;
		cout << std::string(50, '=');
		cout << "\n\t\tATM Main Menu Screen \n";
		cout << std::string(50, '=');
		cout << "\n\t[1] Quick Withdraw.\n";
		cout << "\t[2] Normal Withdraw.\n";
		cout << "\t[3] Deposit.\n";
		cout << "\t[4] Check Balance.\n";
		cout << "\t[5] Logout.\n";
		cout << std::string(50, '=');

		choosingFromMainMenu((enMainMenuOption)readMainMenuOption());

	}


	void loginScreen() {

		bool loginFailed = false;

		do {
			loginScreenHeader();

			if (loginFailed) {

				cout << "Invalid AccountNumber/Pincode!\n";

			}
			stClientData client = readClientData();
			loginFailed = !IsAccountNumberAndPinRight(client.accountNumber, client.pinCode, currentClient);

		} while (loginFailed);

		mainMenuScreen();

	}


}
