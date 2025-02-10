#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "clsString.h"
#include "clsInputValidate.h"


using namespace std;



namespace bankLib {



		const string usersFilePath = "users.txt";

		struct stUsersData {
			string username = "unknown";
			string password = "unknown";
			short permissions = -1;
			bool markForDelete = false;
		};

		enum enUsersMenuOption {

			eListUsers = 1,
			eAddNewUser = 2,
			eDeleteUser = 3,
			eUpdateUser = 4,
			eFindUser = 5,
			eMainMenu_Users = 6,
		};

		enum enMainMenuOption {

			eListClients = 1,
			eAddNewClient = 2,
			eDeleteClient = 3,
			eUpdateClient = 4,
			eFindClient = 5,
			eTransactions = 6,
			eManageUsers = 7,
			eLogout = 8,
		};


		enum enPermissions {
			pAll = -1,
			pListClients = 1,
			pAddNewClient = 2,
			pDeleteClient = 4,
			pUpdateClient = 8,
			pFindClient = 16,
			pTransactions = 32,
			pManageUsers = 64,

		};

		stUsersData currentUser;

		string convertUserRecordToLine(stUsersData user, string seprator = "#//#") {
			string clientRecord = "";
			clientRecord += user.username + seprator;
			clientRecord += user.password + seprator;
			clientRecord += to_string(user.permissions) + seprator;
			return clientRecord;
		}

		stUsersData convertUserLineToRecord(string userRecord, string seprator = "#//#") {


			vector <string> vString = clsString::splitEachWordOfStringInToVector(userRecord, seprator);
			stUsersData user;

			user.username = vString[0];
			user.password = vString[1];
			user.permissions = stoi(vString[2]);


			return user;
		}

		void printUserRecord(stUsersData user) {
			cout << "| " << setw(15) << left << user.username;
			cout << "| " << setw(15) << left << user.password;
			cout << "| " << setw(10) << left << user.permissions;
		}

		void printUserCard(stUsersData user) {
			cout << "Username : " << user.username << endl;
			cout << "Password: " << user.password << endl;
			cout << "Permissions: " << user.permissions << endl;
		}

		vector <stUsersData> loadUsersDataFromFile() {

			vector <stUsersData> vUsers;

			fstream usersDataFile;
			usersDataFile.open(usersFilePath, ios::in);

			if (usersDataFile.is_open()) {
				string line;
				stUsersData user;

				while (getline(usersDataFile, line)) {
					user = convertUserLineToRecord(line);
					vUsers.push_back(user);
				}

				usersDataFile.close();
			}
			return vUsers;

		}

		short userPermissions(stUsersData user) {
			char fullAccess;
			cout << "Do you want to give full access to " << user.username << "? y/n? ";
			cin >> fullAccess;
			short permission = 0;

			if (fullAccess != 'y' && fullAccess != 'Y') {

				char answer;
				cout << "Do you want to give access to: " << endl << endl;

				cout << "1- Show Client List? y/n? " << endl << endl;
				cin >> answer;
				if (answer == 'y' || answer == 'Y') {
					permission += enPermissions::pListClients;
				}

				cout << "2- Add New Client? y/n" << endl << endl;
				cin >> answer;
				if (answer == 'y' || answer == 'Y') {
					permission += enPermissions::pAddNewClient;
				}

				cout << "3- Delete Client? y/n" << endl << endl;
				cin >> answer;
				if (answer == 'y' || answer == 'Y') {
					permission += enPermissions::pDeleteClient;
				}

				cout << "4- Update Client? y/n" << endl << endl;
				cin >> answer;
				if (answer == 'y' || answer == 'Y') {
					permission += enPermissions::pUpdateClient;
				}

				cout << "5- Find Client? y/n" << endl << endl;
				cin >> answer;
				if (answer == 'y' || answer == 'Y') {
					permission += enPermissions::pFindClient;
				}

				cout << "6- Transactions? y/n" << endl << endl;
				cin >> answer;
				if (answer == 'y' || answer == 'Y') {
					permission += enPermissions::pTransactions;
				}

				cout << "7- Manage Users? y/n" << endl << endl;
				cin >> answer;
				if (answer == 'y' || answer == 'Y') {
					permission += enPermissions::pManageUsers;
				}

			}
			else {
				permission = -1;
			}
			user.permissions = permission;


			return permission;

		}

		bool findIfUserExistByUsername(string username, vector <stUsersData> vUsers, stUsersData& foundUser) {


			for (stUsersData& user : vUsers) {
				if (username == user.username) {
					foundUser = user;
					return 1;
				}
			}
			return 0;
		}

		bool checkAccessPermissions(enPermissions permission) {

			if (currentUser.permissions == enPermissions::pAll) {
				return true;
			}
			else if ((currentUser.permissions & permission) == permission) {
				return true;
			}
			else {
				return false;
			}

		}

		void showAccessDeniedMessage() {
			cout << "\n-----------------------------------\n";
			cout << "Access Denied, \nYou don't have permissions to do this,\nPlease contact your Admin ";
			cout << "\n-----------------------------------\n";

		}


		// findUser
		void getUser(string username, vector <stUsersData> vUsers) {

			stUsersData foundUser;

			if (findIfUserExistByUsername(username, vUsers, foundUser)) {

				cout << "\nThe Following Are The User Details\n";
				printUserCard(foundUser);

			}
			else {
				cout << "User with Username (" << username << ") is not found" << endl;
			}
		}




		// update user
		vector<stUsersData> saveUsersDataToFile(vector<stUsersData>& vUsers) {

			fstream myFile;
			myFile.open(usersFilePath, ios::out);

			string userRecord;

			if (myFile.is_open()) {

				for (stUsersData& user : vUsers) {

					if (user.markForDelete == false) {
						userRecord = convertUserRecordToLine(user);
						myFile << userRecord << endl;
					}

				}
				myFile.close();
			}
			return vUsers;
		}

		stUsersData changeUserRecord(string username) {
			stUsersData user;

			user.username = username;

			cout << "Enter Password? ";
			cin >> user.password;

			user.permissions = userPermissions(user);


			cout << endl;

			return user;
		}

		bool updateUserByUsername(string username, vector<stUsersData>& vUsers) {

			stUsersData foundUser;
			char answer = 'n';

			if (findIfUserExistByUsername(username, vUsers, foundUser)) {

				printUserCard(foundUser);

				cout << "\nAre you sure you want to update " << foundUser.username << " (y / n)? \n";
				cin >> answer;

				if (answer == 'y' || answer == 'Y') {

					for (stUsersData& user : vUsers) {
						if (user.username == username) {
							user = changeUserRecord(user.username);
							break;
						}
					}

					saveUsersDataToFile(vUsers);


					cout << "\nuser updated\n";
					return true;
				}

			}
			else {
				cout << "This User(" << username << ") is not found" << endl;
				return false;
			}
		}


		// delete user

		bool markUserForDeleteByUsername(string username, vector<stUsersData>& vUsers) {

			for (stUsersData& user : vUsers) {

				if (user.username == username) {
					user.markForDelete = true;
					return true;
				}
			}
			return false;

		}


		bool deleteUserByUsername(string username, vector<stUsersData>& vUsers) {

			stUsersData foundUser;
			char answer = 'n';

			if (username == "Admin") {
				cout << "This User Can't Be Deleted" << endl;
			}
			else {
				if (findIfUserExistByUsername(username, vUsers, foundUser)) {

					printUserCard(foundUser);

					cout << "\nAre you sure you want to delete " << foundUser.username << " y / n? \n";
					cin >> answer;

					if (answer == 'y' || answer == 'Y') {

						markUserForDeleteByUsername(username, vUsers);

						saveUsersDataToFile(vUsers);

						vUsers = loadUsersDataFromFile(); // referesh

						cout << "\nUser deleted\n";
						return true;
					}

				}
				else {
					cout << "Client with Username (" << username << ") is not found" << endl;
					return false;
				}
			}


		}




		// add user

		stUsersData readUserData() {

			stUsersData user;
			cout << "\nenter username? ";
			cin >> user.username;
			cout << "\nenter password? ";
			cin >> user.password;

			return user;
		}

		stUsersData createUser() {

			vector <stUsersData> vUsers = loadUsersDataFromFile();

			stUsersData user;

			cout << "Enter Username? ";
			cin >> user.username;
			cout << endl;
			bool isUnique = true;

			// Check if the entered username is unique
			do {
				isUnique = true;
				for (const stUsersData& u : vUsers) {
					if (user.username == u.username) {
						cout << "user with name [" << user.username << "] already exists." << endl;
						cout << "Enter another Username? ";
						cin >> user.username;
						isUnique = false; // Set flag to false to continue checking
						break; // No need to check further if a match is found
					}
				}
			} while (!isUnique);


			cout << endl;

			cout << "Enter Password? ";
			cin >> user.password;
			cout << endl;


			user.permissions = userPermissions(user);

			return user;

		}

		void addUserToFile() {

			fstream userDataFile;
			stUsersData user = createUser();
			string userRecord = convertUserRecordToLine(user);

			userDataFile.open(usersFilePath, ios::out | ios::app);
			if (userDataFile.is_open()) {
				userDataFile << userRecord << endl;
				userDataFile.close();
			}

		}

		void doYouWantToAddMoreUsers() {

			bool addMore = true;

			while (addMore) {
				cout << "Adding New User:\n\n";

				addUserToFile();
				cout << "\nUser Added Successfully, Do You Want To Add More Users (0, 1)\n";
				cin >> addMore;
				system("cls");
			}
		}

		// print user
		void printUsersData(vector < stUsersData> vUsers) {

			cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
			cout << endl << string(100, '_') << endl;
			cout << "| " << left << setw(15) << "Username";
			cout << "| " << left << setw(15) << "Password";
			cout << "| " << left << setw(10) << "Permissions";
			cout << endl << string(100, '_') << endl;

			for (stUsersData& user : vUsers) {
				printUserRecord(user);
				cout << endl;
			}
			cout << endl << string(100, '_') << endl;

		}


		void goBackToUsersMenu();
		void goBackToMainMenu();


		void choosingFromUsersMenu(enUsersMenuOption mainMenuOption) {

			vector <stUsersData> vUsers = loadUsersDataFromFile();

			switch (mainMenuOption) {
			case enUsersMenuOption::eListUsers:
				printUsersData(vUsers);
				goBackToUsersMenu();
				break;
			case enUsersMenuOption::eAddNewUser:
				doYouWantToAddMoreUsers();
				goBackToUsersMenu();
				break;
			case enUsersMenuOption::eDeleteUser:
				deleteUserByUsername(clsString::readString("inter Username"), vUsers);
				goBackToUsersMenu();
				break;
			case enUsersMenuOption::eUpdateUser:
				updateUserByUsername(clsString::readString("inter Username"), vUsers);
				goBackToUsersMenu();
				break;
			case enUsersMenuOption::eFindUser:
				getUser(clsString::readString("inter Username"), vUsers);
				goBackToUsersMenu();
				break;
			case enUsersMenuOption::eMainMenu_Users:
				goBackToMainMenu();
			default:
				cout << "not a valid number please choose from 1 to 6";
				goBackToUsersMenu();
			}

		}

		void usersMenuScreen() {

			if (!checkAccessPermissions(enPermissions::pManageUsers)) {

				showAccessDeniedMessage();
				return;

			}

			system("cls");
			cout << std::string(50, '=');
			cout << "\n\t\tManage Users Menu Screen \n";
			cout << std::string(50, '=');
			cout << "\n\t[1] List Users.\n";
			cout << "\t[2] Add New User.\n";
			cout << "\t[3] Delete User.\n";
			cout << "\t[4] Update User.\n";
			cout << "\t[5] Find User.\n";
			cout << "\t[6] Main Menu\n";

			cout << std::string(50, '=');
			cout << "\nChoose What Do You Want To Do? [1 to 6]? ";
			short option;
			cin >> option;
			system("cls");
			choosingFromUsersMenu((enUsersMenuOption)option);

		}

		void goBackToUsersMenu() {
			cout << "\n\n Press Any Key To Go Back To Users Menu...";
			system("pause>0");
			usersMenuScreen();
		}

		bool IsNameAndPassRight(string username, string password, stUsersData& currentUser) {

			vector <stUsersData> users = loadUsersDataFromFile();

			for (stUsersData& user : users) {
				if (user.username == username && user.password == password) {
					currentUser = user;
					return 1;
				}
			}
			return 0;
		}









	const string filePath = "clientDataFile.txt";

	struct stClientData {
		string accountNumber = "unknown";
		string pinCode = "unkonwn";
		string name = "unknown";
		string phone = "unknown";
		int accountBalance = 0;
		bool markForDelete = false;
	};


	vector <stClientData> loadClientsDataFromFile();



	stClientData readClientData() {

		vector <stClientData> vClients = loadClientsDataFromFile();

		stClientData client;

		cout << "Enter Account Number? ";
		cin >> client.accountNumber;
		bool isUnique = true;

		// Check if the entered account number is unique
		do {
			isUnique = true;
			for (const stClientData& c : vClients) {
				if (client.accountNumber == c.accountNumber) {
					cout << "Client with Account Number [" << client.accountNumber << "] already exists." << endl;
					cout << "Enter another Account Number: ";
					cin >> client.accountNumber;
					isUnique = false; // Set flag to false to continue checking
					break; // No need to check further if a match is found
				}
			}
		} while (!isUnique);


		cout << endl;


		cout << "Enter PinCode? ";
		cin >> client.pinCode;
		cout << endl;
		cout << "Enter Name? ";
		//If you have previously used cin >> someVariable, there might be a newline character left in the input buffer. This can cause getline to read an empty string.
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
		getline(cin, client.name);
		cout << endl;
		cout << "Enter Phone? ";
		cin >> client.phone;
		cout << endl;
		cout << "Enter Account Balance? ";
		cin >> client.accountBalance;
		cout << endl;
		return client;
	}

	stClientData changeClientRecord(string accountNumber) {
		stClientData client;

		client.accountNumber = accountNumber;

		cout << "\n\nEnter PinCode? ";
		getline(cin >> ws, client.pinCode);

		cout << "Enter Name? ";

		getline(cin, client.name);

		cout << "Enter Phone? ";
		getline(cin, client.phone);


		cout << "Enter Account Balance? ";
		cin >> client.accountBalance;
		cout << endl;

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

	void printClientCard(stClientData client) {
		cout << "Account Number : " << client.accountNumber << endl;
		cout << "Pin Code	: " << client.pinCode << endl;
		cout << "Name		: " << client.name << endl;
		cout << "Phone		: " << client.phone << endl;
		cout << "Account balance : " << client.accountBalance << endl;
	}

	void printClientRecord(stClientData client) {
		cout << "| " << setw(15) << left << client.accountNumber;
		cout << "| " << setw(10) << left << client.pinCode;
		cout << "| " << setw(40) << left << client.name;
		cout << "| " << setw(12) << left << client.phone;
		cout << "| " << setw(12) << left << client.accountBalance;
	}


	void addClientsToFile() {

		fstream clientDataFile;
		stClientData client = readClientData();
		string clientRecord = convertRecordToLine(client);

		clientDataFile.open(filePath, ios::out | ios::app);
		if (clientDataFile.is_open()) {
			clientDataFile << clientRecord << endl;
			clientDataFile.close();
		}

	}

	void doYouWantToAddMoreClients() {

		if (!checkAccessPermissions(enPermissions::pAddNewClient)) {

			showAccessDeniedMessage();
			return;

		}

		bool addMore = true;

		while (addMore) {
			cout << "Adding New Client:\n\n";

			addClientsToFile();
			cout << "\nClient Added Successfully, Do You Want To Add More Clients (1,0)\n";
			cin >> addMore;
			system("cls");
		}
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

	void printClientsData(vector <stClientData> vClients) {

		if (!checkAccessPermissions(enPermissions::pListClients)) {

			showAccessDeniedMessage();
			return;

		}

		cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
		cout << endl << string(100, '_') << endl;
		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(12) << "Balance";
		cout << endl << string(100, '_') << endl;

		for (stClientData& client : vClients) {
			printClientRecord(client);
			cout << endl;
		}
		cout << endl << string(100, '_') << endl;

	}



	bool findIfClientExistByAccountNumber(string accountNumber, vector <stClientData> vClients, stClientData& foundClient) {


		for (stClientData& client : vClients) {
			if (accountNumber == client.accountNumber) {
				foundClient = client;
				return 1;
			}
		}
		return 0;
	}


	void getClient(string accountNumber, vector <stClientData> vClients) {

		if (!checkAccessPermissions(enPermissions::pFindClient)) {

			showAccessDeniedMessage();
			return;

		}

		stClientData foundClient;

		if (findIfClientExistByAccountNumber(accountNumber, vClients, foundClient)) {

			cout << "\nThe Following Are The Client Details\n";
			printClientCard(foundClient);

		}
		else {
			cout << "Client with account number (" << accountNumber << ") is not found" << endl;
		}
	}


	bool markClientForDeleteByAccountNumber(string accountNumber, vector<stClientData>& vClients) {

		for (stClientData& client : vClients) {

			if (client.accountNumber == accountNumber) {
				client.markForDelete = true;
				return true;
			}
		}
		return false;

	}


	vector<stClientData> saveClientsDataToFile(vector<stClientData>& vClients) {

		fstream myFile;
		myFile.open(filePath, ios::out);

		string clientRecord;

		if (myFile.is_open()) {

			for (stClientData& client : vClients) {

				if (client.markForDelete == false) {
					clientRecord = convertRecordToLine(client);
					myFile << clientRecord << endl;
				}

			}
			myFile.close();
		}
		return vClients;
	}


	bool deleteClientByAccoutNumber(string accountNumber, vector<stClientData>& vClients) {

		if (!checkAccessPermissions(enPermissions::pDeleteClient)) {

			showAccessDeniedMessage();
			return 0;

		}

		stClientData client;
		char answer = 'n';

		if (findIfClientExistByAccountNumber(accountNumber, vClients, client)) {

			printClientCard(client);

			cout << "\nAre you sure you want to delete this client y/n\n";
			cin >> answer;

			if (answer == 'y' || answer == 'Y') {

				markClientForDeleteByAccountNumber(accountNumber, vClients);

				saveClientsDataToFile(vClients);

				vClients = loadClientsDataFromFile();

				cout << "\nclient deleted\n";
				return true;
			}

		}
		else {
			cout << "Client with account number (" << accountNumber << ") is not found" << endl;
			return false;
		}
	}


	bool updateClientByAccoutNumber(string accountNumber, vector<stClientData>& vClients) {

		if (!checkAccessPermissions(enPermissions::pUpdateClient)) {

			showAccessDeniedMessage();
			return 0;

		}

		stClientData client;
		char answer = 'n';

		if (findIfClientExistByAccountNumber(accountNumber, vClients, client)) {

			printClientCard(client);

			cout << "\nAre you sure you want to update this client y/n\n";
			cin >> answer;

			if (answer == 'y' || answer == 'Y') {

				for (stClientData& c : vClients) {
					if (c.accountNumber == accountNumber) {
						c = changeClientRecord(accountNumber);
						break;
					}
				}

				saveClientsDataToFile(vClients);


				cout << "\nclient updated\n";
				return true;
			}

		}
		else {
			cout << "Client with account number (" << accountNumber << ") is not found" << endl;
			return false;
		}
	}


	// moved to clsTranactionsScreen
	enum enTransactionMenuOption {
		eDeposit = 1,
		eWithdraw = 2,
		eTotalBalance = 3,
		eMainMenu_Transaction = 4
	};


	void endProgram() {
		cout << std::string(50, '-');
		cout << "\n\tProgram Ends :-)\n";
		cout << std::string(50, '-');
	}

	void mainMenuScreen();
	void loginScreen();

	void transactionMenuScreen();

	void goBackToMainMenu() {
		cout << "\n\n Press Any Key To Go Back To Main Menu...";
		system("pause>0");
		mainMenuScreen();
	}

	void goBackToTransactionMenu() {
		cout << "\n\n Press Any Key To Go Back To Tranactiono Menu...";
		system("pause>0");
		transactionMenuScreen();
	}


	bool depositeToAccoutNumber(string accountNumber, vector<stClientData> vClients) {

		stClientData client;
		char answer = 'n';

		if (findIfClientExistByAccountNumber(accountNumber, vClients, client)) {

			cout << "\nThe Following Are The Client Details\n";
			printClientCard(client);

			float depositeAmount = clsInputValidate::readNumber<float>("Please enter deposite amount? ");
			int newBalance = 0;

			cout << "\nAre you sure you want to perform this transaction y/n\n";
			cin >> answer;

			if (answer == 'y' || answer == 'Y') {

				for (stClientData& c : vClients) {
					if (c.accountNumber == accountNumber) {
						c.accountBalance = c.accountBalance + depositeAmount;
						newBalance = c.accountBalance;
						break;
					}
				}

				saveClientsDataToFile(vClients);


				cout << "\nDone Successfully, New Balance is " << newBalance << endl;
				return true;
			}

		}
		else {
			cout << "Client with account number (" << accountNumber << ") is not found" << endl;
			return false;
		}
	}

	void depositeScreen(vector <stClientData> vClients) {
		cout << std::string(50, '-');
		cout << "\n\tDeposite Screen\n";
		cout << std::string(50, '-');

		depositeToAccoutNumber(clsString::readString("\ninter account Number\n"), vClients);

	}



	int totalClientsBalances(vector <stClientData> vClients) {
		int totalBalance = 0;
		for (stClientData& client : vClients) {
			totalBalance += client.accountBalance;
		}
		return totalBalance;

	}

	void ClientBalanceTable(stClientData client) {
		cout << "| " << setw(15) << left << client.accountNumber;
		cout << "| " << setw(40) << left << client.name;
		cout << "| " << setw(12) << left << client.accountBalance;
	}

	void ClientsBalancesTable(vector <stClientData> vClients) {


		cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Clients(s).";
		cout << endl << string(100, '_') << endl;
		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << endl << string(100, '_') << endl;

		for (stClientData& client : vClients) {
			ClientBalanceTable(client);
			cout << endl;
		}
		cout << string(100, '_') << endl;

		cout << "\n\t\t\tTotal Balances = " << totalClientsBalances(vClients);

	}


	bool withdrawFromAccoutNumber(string accountNumber, vector<stClientData> vClients) {

		stClientData client;
		char answer = 'n';

		if (findIfClientExistByAccountNumber(accountNumber, vClients, client)) {

			cout << "\nThe Following Are The Client Details\n";
			printClientCard(client);

			float withdrawAmount = clsInputValidate::readNumber<float>("\nPlease Enter Withdraw Amount? ");
			while (withdrawAmount > client.accountBalance) {
				cout << "Withdraw Amount Exceeds The Balnce You Can Withdraw Up To: " << client.accountBalance;
				withdrawAmount = clsInputValidate::readNumber<float>("\nPlease Enter Another Withdraw Amount? ");
			}

			int newBalance = 0;

			cout << "\nAre you sure you want to perform this transaction y/n\n";
			cin >> answer;

			if (answer == 'y' || answer == 'Y') {

				for (stClientData& c : vClients) {
					if (c.accountNumber == accountNumber) {

						c.accountBalance = c.accountBalance - withdrawAmount;
						newBalance = c.accountBalance;
						break;
					}
				}

				saveClientsDataToFile(vClients);


				cout << "\nDone Successfully, New Balance is " << newBalance << endl;
				return true;
			}

		}
		else {
			cout << "Client with account number (" << accountNumber << ") is not found" << endl;
			return false;
		}
	}

	void withdrawScreen(vector <stClientData> vClients) {
		cout << std::string(50, '-');
		cout << "\nWithdraw Screen\n";
		cout << std::string(50, '-');

		withdrawFromAccoutNumber(clsString::readString("\nenter account number? \n"), vClients);

	}


	void choosingFromTransactionMenu(enTransactionMenuOption option) {

		vector <stClientData> vClients = loadClientsDataFromFile();

		switch (option) {

		case enTransactionMenuOption::eDeposit:

			depositeScreen(vClients);

			goBackToTransactionMenu();
			break;
		case enTransactionMenuOption::eWithdraw:

			withdrawScreen(vClients);

			goBackToTransactionMenu();
			break;
		case enTransactionMenuOption::eTotalBalance:

			ClientsBalancesTable(vClients);
			goBackToTransactionMenu();
			break;
		case enTransactionMenuOption::eMainMenu_Transaction:
			goBackToMainMenu();
			break;
		default:
			cout << "not a valid number please choose from 1 to 6";
			goBackToMainMenu();
		}
	}

	void transactionMenuScreen() {

		if (!checkAccessPermissions(enPermissions::pTransactions)) {

			showAccessDeniedMessage();
			return;

		}

		system("cls");
		cout << std::string(50, '=');
		cout << "\n\tTransaction Menu Screen \n";
		cout << std::string(50, '=');
		cout << "\n\t[1] Deposit.\n";
		cout << "\t[2] Withdraw.\n";
		cout << "\t[3] Total Balance.\n";
		cout << "\t[4] Main Menu.\n";

		cout << std::string(50, '=');
		cout << "\nChoose What Do You Want To Do? [1 to 4]? ";
		short option;
		cin >> option;
		system("cls");
		choosingFromTransactionMenu((enTransactionMenuOption)option);
	}


	void choosingFromMainMenu(enMainMenuOption mainMenuOption) {

		vector <stClientData> vClients = loadClientsDataFromFile();

		switch (mainMenuOption) {
		case enMainMenuOption::eListClients:
			printClientsData(vClients);
			goBackToMainMenu();
			break;
		case enMainMenuOption::eAddNewClient:
			doYouWantToAddMoreClients();
			goBackToMainMenu();
			break;
		case enMainMenuOption::eDeleteClient:
			deleteClientByAccoutNumber(clsString::readString("inter account number"), vClients);
			goBackToMainMenu();
			break;
		case enMainMenuOption::eUpdateClient:
			updateClientByAccoutNumber(clsString::readString("inter account NUmber"), vClients);
			goBackToMainMenu();
			break;
		case enMainMenuOption::eFindClient:
			getClient(clsString::readString("inter account Number"), vClients);
			goBackToMainMenu();
			break;
		case enMainMenuOption::eTransactions:
			transactionMenuScreen();
			goBackToMainMenu();
		case enMainMenuOption::eManageUsers:
			
			usersMenuScreen();
			goBackToMainMenu();
			break;
		case enMainMenuOption::eLogout:

			//clearIpnutStream();
			loginScreen();
			break;
		default:
			cout << "not a valid number please choose from 1 to 7";
			goBackToMainMenu();
		}

	}

	void showCurrentUserAndChoisesHeCanAccess() {
		cout << "Hello " << currentUser.username << " Your Permission Number: " << currentUser.permissions << ", Your Can Access ";
		if (currentUser.permissions == -1) {
			cout <<  "All" << endl;
		}
		else if (currentUser.permissions == 0) {
			cout << "Nothing" << endl;
		}
		else {
				if ((currentUser.permissions & enPermissions::pListClients) == enPermissions::pListClients) {
					cout << "1, ";
				}
				if ((currentUser.permissions & enPermissions::pAddNewClient) == enPermissions::pAddNewClient) {
					cout << "2, ";
				}
				if ((currentUser.permissions & enPermissions::pDeleteClient) == enPermissions::pDeleteClient) {
					cout << "3, ";
				}
				if ((currentUser.permissions & enPermissions::pUpdateClient) == enPermissions::pUpdateClient) {
					cout << "4, ";
				}
				if ((currentUser.permissions & enPermissions::pFindClient) == enPermissions::pFindClient) {
					cout << "5, ";
				}
				if ((currentUser.permissions & enPermissions::pTransactions) == enPermissions::pTransactions) {
					cout << "6, ";
				}
				if ((currentUser.permissions & enPermissions::pManageUsers) == enPermissions::pManageUsers) {
					cout << "7";
				}
				
		}

	}

	void mainMenuScreen() {
		system("cls");
		showCurrentUserAndChoisesHeCanAccess();
		cout << endl;
		cout << std::string(50, '=');
		cout << "\n\t\tMain Menu Screen \n";
		cout << std::string(50, '=');
		cout << "\n\t[1] Show Client List.\n";
		cout << "\t[2] Add New Client.\n";
		cout << "\t[3] Delete Client.\n";
		cout << "\t[4] Update Client Info.\n";
		cout << "\t[5] Find Client.\n";
		cout << "\t[6] Transactions\n";
		cout << "\t[7] Manage Users.\n";
		cout << "\t[8] Logout.\n";
		cout << std::string(50, '=');
		cout << "\nChoose What Do You Want To Do? [1 to 8]? ";
		short option;
		cin >> option;
		system("cls");
		choosingFromMainMenu((enMainMenuOption)option);

	}


	void loginScreenHeader() {
		// course 8
		system("cls");
		cout << std::string(50, '=');
		cout << "\n\t\Login Screen \n";
		cout << std::string(50, '=') << endl;
	}

	void loginScreen() {
		// course 8
		loginScreenHeader();

		stUsersData user = readUserData();

		while (!IsNameAndPassRight(user.username, user.password, currentUser)) {
			loginScreenHeader();

			cout << "Invalid Username/Password!\n";
			user = readUserData();

		}

		mainMenuScreen();

	}


}
