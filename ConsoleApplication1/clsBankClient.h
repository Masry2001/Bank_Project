#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;


class clsBankClient : public clsPerson {

private:

	enum enMode { emptyMode = 0, upadateMode = 1, addNewMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string line) {

		vector <string> vClient = clsString::splitEachWordOfStringInToVector(line, "#//#");

		return (clsBankClient(enMode::upadateMode, vClient[0], vClient[1], vClient[2], vClient[3],
			vClient[4], vClient[5], stod(vClient[6])));
	}

	static string _ConvertClientObjectToLine(clsBankClient client, string seprator = "#//#") {

		string clientRecord = "";
		clientRecord += client.firstName + seprator;
		clientRecord += client.lastName + seprator;
		clientRecord += client.email + seprator;
		clientRecord += client.phone + seprator;
		clientRecord += client.accountNumber() + seprator;
		clientRecord += client.pinCode + seprator;
		clientRecord += to_string(client.accountBalance);
		return clientRecord;

	}

	static clsBankClient _GetEmptyClientOpject() {
		return clsBankClient(enMode::emptyMode, "", "", "", "", "", "", 0);
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients) {

		fstream myFile;
		myFile.open("Clients.txt", ios::out); // overwrite

		string clientRecord;

		if (myFile.is_open()) {

			for (clsBankClient& client : vClients) {


				if (client._MarkedForDelete == false) { // client.markedForDelete()

					//we only write records that are not marked for delete.  

					clientRecord = _ConvertClientObjectToLine(client);
					myFile << clientRecord << endl;
				}

			}
			myFile.close();
		}
	}

	static vector <clsBankClient> _LoadClientsDataFromFile() {

		vector <clsBankClient> vClients;

		fstream clientDataFile;
		clientDataFile.open("Clients.txt", ios::in);

		if (clientDataFile.is_open()) {

			string line;

			while (getline(clientDataFile, line)) {
				clsBankClient client = _ConvertLineToClientObject(line);
				vClients.push_back(client);
			}

			clientDataFile.close();
		}
		return vClients;
	}

	void _AddDataLineToFile(string stDataLine) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _Update() {

		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& c : vClients) {

			if (c.accountNumber() == this->accountNumber()) {

				c = *this;
				break;

			}

		}

		_SaveClientsDataToFile(vClients);

	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertClientObjectToLine(*this));

	}

	// total Balances
	static void _ClientBalanceTable(clsBankClient client) {
		cout << "| " << setw(15) << left << client.accountNumber();
		cout << "| " << setw(40) << left << client.fullName();
		cout << "| " << setw(12) << left << client.accountBalance;
	}


	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string userName, string seprator = "#//#") {

		string transferRecord = "";
		transferRecord += clsDate::getSystemDateTimeString() + seprator;
		transferRecord += accountNumber() + seprator;
		transferRecord += DestinationClient.accountNumber() + seprator;
		transferRecord += to_string(Amount) + seprator;
		transferRecord += to_string(accountBalance) + seprator;
		transferRecord += to_string(DestinationClient.accountBalance) + seprator;
		transferRecord += userName;
		return transferRecord;

	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName) {

		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("transferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	struct stTransferRecord;
	static stTransferRecord _ConvertTranferLogLineToRecord(string line) {

		stTransferRecord transferLogRecord;

		vector <string> transferLogDataLine = clsString::splitEachWordOfStringInToVector(line, "#//#");

		transferLogRecord.dateTime = transferLogDataLine[0];
		transferLogRecord.sourceAccNum = transferLogDataLine[1];
		transferLogRecord.destinationAccNum = transferLogDataLine[2];
		transferLogRecord.amount = stof(transferLogDataLine[3]);
		transferLogRecord.sourceAccBal = stof(transferLogDataLine[4]);
		transferLogRecord.destinationAccBal = stof(transferLogDataLine[5]);
		transferLogRecord.userName = transferLogDataLine[6];
		return transferLogRecord;

	}

public:

	clsBankClient(enMode mode, string firstName, string lastName, string email,
		string phone, string accountNumber, string pinCode, float accountBalance) :
		clsPerson(firstName, lastName, email, phone)
	{
		_Mode = mode;
		_AccountNumber = accountNumber;
		_PinCode = pinCode;
		_AccountBalance = accountBalance;
	}

	struct stTransferRecord {
		string dateTime;
		string sourceAccNum;
		string destinationAccNum;
		float amount;
		float sourceAccBal;
		float destinationAccBal;
		string userName;
	};

	 bool isEmpty() {
		return(_Mode == enMode::emptyMode);
	}

	 bool markedForDeleted()
	 {
		 return _MarkedForDelete;
	 }

	string accountNumber() {
		return _AccountNumber;
	}

	string getPinCode() {
		return _PinCode;
	}

	void setPinCode(string pinCode) {
		_PinCode = pinCode;
	}

	__declspec(property(get = getPinCode, put = setPinCode)) string pinCode;

	float getAccountBalance() {
		return _AccountBalance;
	}

	void setAccountBalance(float accountBalance) {
		_AccountBalance = accountBalance;
	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float accountBalance;

	// No UI Related code inside object (seprate UI from the logic)
	void print() {
		cout << "\nClient Card: ";
		cout << "\n_______________________";
		cout << "\nFirst Name   : " << clsPerson::firstName;
		cout << "\nLast Name    : " << clsPerson::lastName;
		cout << "\nFull Name    : " << clsPerson::fullName();
		cout << "\nEmail        : " << clsPerson::email;
		cout << "\nPhone        : " << clsPerson::phone;
		cout << "\nAcc. Number  : " << _AccountNumber;
		cout << "\nPassword     : " << _PinCode;
		cout << "\nBalance      : " << _AccountBalance;
		cout << "\n_______________________\n";

	}

	static clsBankClient find (string accountNumber) {
		
		//vector <clsBankClient> vClient;

		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		if (myFile.is_open()) {
			string line;

			while (getline(myFile, line)) {
				
				clsBankClient client = _ConvertLineToClientObject(line);

				if (client.accountNumber() == accountNumber) {
					myFile.close();
					return client;
				}

				//vClient.push_back(client);

			}
			myFile.close();

		}
		return _GetEmptyClientOpject();

	}

	static clsBankClient find (string accountNumber, string pinCode) {
		
		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		if (myFile.is_open()) {
			string line;

			while (getline(myFile, line)) {
				
				clsBankClient client = _ConvertLineToClientObject(line);

				if ( (client.accountNumber() == accountNumber) && (client.pinCode == pinCode) ) {
					myFile.close();
					return client;
				}

			}
			myFile.close();

		}
		return _GetEmptyClientOpject();

	}

	static bool isClientExist(string accountNumber) {
		clsBankClient client = find(accountNumber);
		return (!client.isEmpty());
	}

	enum enSaveResults { svFailedEmptyObj = 0, svSucceeded = 1, svFailedAccountNumberExists = 2 };

	enSaveResults save() {

		switch (_Mode) {
			case enMode::emptyMode:
				return enSaveResults::svFailedEmptyObj;
				break;

			case enMode::upadateMode:
				_Update();
				return enSaveResults::svSucceeded;
				break;

			case enMode::addNewMode:
				if (isClientExist(_AccountNumber)) {
					return enSaveResults::svFailedAccountNumberExists;
				}
				else {
					_AddNew();
					_Mode = enMode::upadateMode;
					return enSaveResults::svSucceeded;

				}

				
		}

	}

	// update client
	// moved to clsAddNewClientScreen(_ReadClientInfo)
	static void readClientInfo(clsBankClient& client) {

		client.firstName = clsInputValidate::readString("Please Enter First Name     : ");
		client.lastName = clsInputValidate::readString("Please Enter Last Name      : ");

		client.email = clsInputValidate::readString("Please Enter Email          : ");
		client.phone = clsInputValidate::readString("Please Enter Phone          : ");

		client.pinCode = clsInputValidate::readString("Please Enter Pin Code       : ");

		client.accountBalance = clsInputValidate::readNumber<float>("Please Enter Account Balance: ");

	}

	static clsBankClient getClientByAccountNumber() {

		string accountNumber = clsInputValidate::readString("Please Enter Client Account Number: ");

		while (!clsBankClient::isClientExist(accountNumber)) {

			accountNumber = clsInputValidate::readString("Account Number Not Found, Choose Anohter: ");

		}

		clsBankClient client = clsBankClient::find(accountNumber);

		return client;
	}

	static void updateClientBalance() {

		clsBankClient client = getClientByAccountNumber();
		client.print();

		cout << "\n\nUpdate Client Balance: ";
		cout << "\n______________________\n";

		client.accountBalance = clsInputValidate::readNumber<float>("Enter Account Balance: ");

		clsBankClient::enSaveResults saveResult = client.save();

		switch (saveResult) {
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";
			client.print();
			break;

		case clsBankClient::enSaveResults::svFailedEmptyObj:
			cout << "\nError Account Was Not Saved Because It's Empty";
			break;
		}

	}

	static void updateClientPinCode() {


		clsBankClient client = getClientByAccountNumber();
		client.print();

		cout << "\n\nUpdate Client Pin Code: ";
		cout << "\n______________________\n";

		client.pinCode = clsInputValidate::readString("Please Enter Pin Code: ");


		clsBankClient::enSaveResults saveResult = client.save();

		switch (saveResult) {
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";
			client.print();
			break;

		case clsBankClient::enSaveResults::svFailedEmptyObj:
			cout << "\nError Account Was Not Saved Because It's Empty";
			break;
		}


	}

	static void updateClientPhone() {


		clsBankClient client = getClientByAccountNumber();
		client.print();

		cout << "\n\nUpdate Client Phone: ";
		cout << "\n______________________\n";

		client.phone = clsInputValidate::readString("Please Enter Phone: ");


		clsBankClient::enSaveResults saveResult = client.save();

		switch (saveResult) {
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";
			client.print();
			break;

		case clsBankClient::enSaveResults::svFailedEmptyObj:
			cout << "\nError Account Was Not Saved Because It's Empty";
			break;
		}


	}

	static void updateClientEmail() {


		clsBankClient client = getClientByAccountNumber();
		client.print();

		cout << "\n\nUpdate Client Email: ";
		cout << "\n______________________\n";

		client.email = clsInputValidate::readString("Please Enter Email: ");


		clsBankClient::enSaveResults saveResult = client.save();

		switch (saveResult) {
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";
			client.print();
			break;

		case clsBankClient::enSaveResults::svFailedEmptyObj:
			cout << "\nError Account Was Not Saved Because It's Empty";
			break;
		}


	}

	static void updateClientName() {

		clsBankClient client = getClientByAccountNumber();
		client.print();

		cout << "\n\nUpdate Client Name: ";
		cout << "\n______________________\n";

		client.firstName = clsInputValidate::readString("Please Enter First Name: ");
		client.lastName = clsInputValidate::readString("Please Enter Last Name : ");

		clsBankClient::enSaveResults saveResult = client.save();

		switch (saveResult) {
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";
			client.print();
			break;

		case clsBankClient::enSaveResults::svFailedEmptyObj:
			cout << "\nError Account Was Not Saved Because It's Empty";
			break;
		}

	}

	// moved to clsUpdateClientScreen(showUpdateClientScreen)
	static void updateClientInfo() {

		clsBankClient client = getClientByAccountNumber();
		client.print();

		cout << "\n\nUpdate Client Info: ";
		cout << "\n______________________\n";

		readClientInfo(client);

		clsBankClient::enSaveResults saveResult = client.save();

		switch (saveResult) {
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";
			client.print();
			break;

		case clsBankClient::enSaveResults::svFailedEmptyObj:
			cout << "\nError Account Was Not Saved Because It's Empty";
			break;
		}

	}

	// add client

	static clsBankClient getAddNewClientObj(string accountNumber) {
		return clsBankClient(enMode::addNewMode, "", "", "", "", accountNumber, "", 0);
	}

	// moved to clsAddNewClientScreen(showAddNewClientScreen)
	static void addNewClient() {

		string accountNumber = clsInputValidate::readString("\nPlease Enter Account Number: ");

		while (clsBankClient::isClientExist(accountNumber)) {
			cout << "Account Number Is Already Used, Choose Anohter: ";
			accountNumber = clsInputValidate::readString("\nPlease Enter Account Number: ");
		}

		clsBankClient newClient = clsBankClient::getAddNewClientObj(accountNumber);

		clsBankClient::readClientInfo(newClient);

		clsBankClient::enSaveResults saveResult = newClient.save();

		switch (saveResult) {
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Added Successfully :-)\n";
			newClient.print();
			break;

		case clsBankClient::enSaveResults::svFailedEmptyObj:
			cout << "\nError Account Was Not Saved Because It's Empty.";
			break;

		case clsBankClient::enSaveResults::svFailedAccountNumberExists:
			cout << "\nError Account Was Not Added Because Account Number Exists.";
			break;
		}


	}

	// delete client
	 bool Delete() {
		
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& c : vClients) {
			if (c.accountNumber() == this->_AccountNumber) {
				c._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientOpject();
		return true;

	}

	 // moved to clsDeleteClientScreen (showDeleteClientScreen)
	 static void deleteClient() {

		 clsBankClient client = clsBankClient::getClientByAccountNumber();
		 client.print();

		 cout << "\nAre You Sure You Want To Delete This Client Y/N? ";
		 char answer;
		 cin >> answer;

		 if (answer == 'y' || answer == 'Y') {

			 if (client.Delete()) {
				 cout << "\nClient Deleted Successfully :-)\n";
				 client.print();
			 }
			 else {
				 cout << "\nError Client Was Not Deleted.\n";
			 }
		 }

	 }

	// show Clients
	static vector <clsBankClient> getClientsList() {
		 return _LoadClientsDataFromFile();
	}

	// moved to clsClientListScreen
	static void printClientRecord(clsBankClient client) {

		 cout << setw(8) << left << "" << "| " << setw(15) << left << client.accountNumber();
		 cout << "| " << setw(20) << left << client.fullName();
		 cout << "| " << setw(12) << left << client.phone;
		 cout << "| " << setw(20) << left << client.email;
		 cout << "| " << setw(10) << left << client.pinCode;
		 cout << "| " << setw(12) << left << client.accountBalance;

	 }
	// moved to clsClientListScreen
	static void showClientsList() {

		 vector <clsBankClient> vClients = clsBankClient::getClientsList();

		 // the header
		 cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
		 cout << endl << string(100, '_') << endl;
		 cout << "| " << left << setw(15) << "Account Number";
		 cout << "| " << left << setw(20) << "Client Name";
		 cout << "| " << left << setw(12) << "Phone";
		 cout << "| " << left << setw(20) << "Email";
		 cout << "| " << left << setw(10) << "Pin Code";
		 cout << "| " << left << setw(12) << "Balance";
		 cout << endl << string(100, '_') << endl;


		 if (vClients.size() == 0) {
			 cout << "\t\t\t\tNo Clients Available In The System!";
		 }
		 else {
			 for (clsBankClient& client : vClients) {

				 printClientRecord(client);
				 cout << endl;

			 }
			 cout << endl << string(100, '_') << endl;
		 }


	 }

	// total Balances
	static float getTotalBalances() {
		vector <clsBankClient> vClients = getClientsList();
		float totalBalance = 0;
		for (clsBankClient& client : vClients) {
			totalBalance += client.accountBalance;
		}
		return totalBalance;

	}

	static void showTotalBalances() {

		vector <clsBankClient> vClients = clsBankClient::getClientsList();

		cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Clients(s).";
		cout << endl << string(100, '_') << endl;
		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << endl << string(100, '_') << endl;

		for (clsBankClient& client : vClients) {
			_ClientBalanceTable(client);
			cout << endl;
		}
		cout << string(100, '_') << endl;

		float totalBalances = clsBankClient::getTotalBalances();
		cout << "\n\t\t\tTotal Balances = " << totalBalances;

		cout << "\n\t\t\t(" << clsUtil::numberToText(totalBalances) << ")\n";

	}

	void deposit(float amount)
	{
		_AccountBalance += amount;
		save();
	}

	bool withdraw(float amount) {

		if (amount > _AccountBalance) {
			return false;
		} 
		else {
			_AccountBalance -= amount;
			save();
			return true;
		}


	}

	bool transfer(float Amount, clsBankClient& DestinationClient, string userName) {

		if (Amount > accountBalance)
		{
			return false;
		}
		
		withdraw(Amount);
		DestinationClient.deposit(Amount);

		_RegisterTransferLog(Amount, DestinationClient, userName);

		return true;
	}

	static vector <stTransferRecord> getTransferLogList() {

		vector < stTransferRecord> vTransferLogRecords;

		fstream transferLogFile;

		transferLogFile.open("transferLog.txt", ios::in);

		if (transferLogFile.is_open()) {

			string line;
			stTransferRecord trnsferLogRecord;

			while ( getline(transferLogFile, line) ) {

				trnsferLogRecord = _ConvertTranferLogLineToRecord(line);

				vTransferLogRecords.push_back(trnsferLogRecord);

			}

			transferLogFile.close();

		}

		return vTransferLogRecords;
	}




};

