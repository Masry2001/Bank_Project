#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsUtil.h"


using namespace std;

class clsUser : public clsPerson
{

private:

	enum enMode { emptyMode = 0, upadateMode = 1, addNewMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	string _PrepareLogInRecord(string seprator = "#//#") {

		string loggedInUserRecord = "";

		string encryptedPass = clsUtil::encryptText(password);

		loggedInUserRecord += clsDate::getSystemDateTimeString() + seprator;
		loggedInUserRecord += userName + seprator;
		loggedInUserRecord += encryptedPass + seprator;
		loggedInUserRecord += to_string(permissions);
		return loggedInUserRecord;

	}

	static clsUser _ConvertLineToUserObject(string line) {

		vector <string> vUsers = clsString::splitEachWordOfStringInToVector(line, "#//#");

		string decryptedPass = clsUtil::decryptText(vUsers[5]);

		return (clsUser(enMode::upadateMode, vUsers[0], vUsers[1], vUsers[2], vUsers[3],
			vUsers[4], decryptedPass, stoi(vUsers[6])));
	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord (string line) {

		stLoginRegisterRecord loginRegisterRecord;

		vector <string> loginRegisterDataLine = clsString::splitEachWordOfStringInToVector(line, "#//#");

		string decryptedPass = clsUtil::encryptText(loginRegisterDataLine[2]);

		loginRegisterRecord.dateTime = loginRegisterDataLine[0];
		loginRegisterRecord.userName = loginRegisterDataLine[1];
		loginRegisterRecord.password = decryptedPass;
		loginRegisterRecord.permissions = stoi(loginRegisterDataLine[3]);
		return loginRegisterRecord;
		
	}

	static string _ConvertUserObjectToLine(clsUser user, string seprator = "#//#") {

		string encryptedPass = clsUtil::encryptText(user.password);

		string clientRecord = "";
		clientRecord += user.firstName + seprator;
		clientRecord += user.lastName + seprator;
		clientRecord += user.email + seprator;
		clientRecord += user.phone + seprator;
		clientRecord += user.userName + seprator;
		clientRecord += encryptedPass + seprator;
		clientRecord += to_string(user.permissions);
		return clientRecord;

	}

	static clsUser _GetEmptyUserOpject() {
		return clsUser(enMode::emptyMode, "", "", "", "", "", "", 0);
	}

	static void _SaveUsersDataToFile(vector<clsUser> vUsers) {

		fstream myFile;
		myFile.open("users.txt", ios::out); // overwrite

		string clientRecord;

		if (myFile.is_open()) {

			for (clsUser& user : vUsers) {


				if (user._MarkedForDelete == false) { // client.markedForDelete()

					//we only write records that are not marked for delete.  

					clientRecord = _ConvertUserObjectToLine(user);
					myFile << clientRecord << endl;
				}

			}
			myFile.close();
		}
	}

	static vector <clsUser> _LoadUsersDataFromFile() {

		vector <clsUser> vUsers;

		fstream usersFile;
		usersFile.open("users.txt", ios::in);

		if (usersFile.is_open()) {

			string line;

			while (getline(usersFile, line)) {
				clsUser user = _ConvertLineToUserObject(line);
				vUsers.push_back(user);
			}

			usersFile.close();
		}
		return vUsers;
	}

	void _Update() {

		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& c : vUsers) {

			if (c.userName == this->userName) {

				c = *this;
				break;

			}

		}

		_SaveUsersDataToFile(vUsers);

	}

	void _AddDataLineToFile(string stDataLine) {

		fstream MyFile;
		MyFile.open("users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertUserObjectToLine(*this));

	}



public:

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128,
	};

	struct stLoginRegisterRecord {
		string dateTime;
		string userName;
		string password;
		int permissions;
	};

	clsUser(enMode mode, string firstName, string lastName, string email, string phone, string userName, string password, int permissions) : clsPerson(firstName, lastName, email, phone) {

		_Mode = mode;
		_UserName = userName;
		_Password = password;
		_Permissions = permissions;
	}

	bool isEmpty() {
		return(_Mode == enMode::emptyMode);
	}

	bool markedForDelete()
	{
		return _MarkedForDelete;
	}

	enMode getMode() {
		return _Mode;
	}

	string getUserName() {
		return _UserName;
	}

	void setUserName(string userName) {
		_UserName = userName;
	}

	__declspec(property(get = getUserName, put = setUserName)) string userName;

	string getPassword() {
		return _Password;
	}

	void setPassword(string password) {
		_Password = password;
	}

	__declspec(property(get = getPassword, put = setPassword)) string password;

	int getPermissions() {
		return _Permissions;
	}

	void setPermissions(int permissions) {
		_Permissions = permissions;
	}

	__declspec(property(get = getPermissions, put = setPermissions)) int permissions;

	static clsUser find(string userName) {

		//vector <clsBankClient> vClient;

		fstream myFile;
		myFile.open("users.txt", ios::in);

		if (myFile.is_open()) {
			string line;

			while (getline(myFile, line)) {

				clsUser user = _ConvertLineToUserObject(line);

				if (user.userName == userName) {
					myFile.close();
					return user;
				}

				//vClient.push_back(client);

			}
			myFile.close();

		}
		return _GetEmptyUserOpject();

	}

	static clsUser find(string userName, string password) {

		fstream myFile;
		myFile.open("users.txt", ios::in);

		if (myFile.is_open()) {
			string line;

			while (getline(myFile, line)) {

				clsUser user = _ConvertLineToUserObject(line);

				if ((user.userName == userName) && (user.password == password)) {
					myFile.close();
					return user;
				}

			}
			myFile.close();

		}
		return _GetEmptyUserOpject();

	}

	static bool isUserExist(string userName) {
		clsUser user = find(userName);
		return (!user.isEmpty());
	}

	enum enSaveResults { svFailedEmptyObj = 0, svSucceeded = 1, svFailedUserExists = 2 };

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
			if (isUserExist(_UserName)) {
				return enSaveResults::svFailedUserExists;
			}
			else {
				_AddNew();
				_Mode = enMode::upadateMode;
				return enSaveResults::svSucceeded;

			}


		}

	}

	bool Delete() {

		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& c : vUsers) {
			if (c.userName == this->_UserName) {
				c._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserOpject();
		return true;

	}

	static clsUser getAddNewUserObj(string userName) {
		
		return clsUser(enMode::addNewMode, "", "", "", "", userName, "", 0);

	}

	static vector <clsUser> getUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	static clsUser getUserByUserName() {

		string userName = clsInputValidate::readString("Please Enter UserName: ");

		while (!clsUser::isUserExist(userName)) {

			userName = clsInputValidate::readString("UserName Not Found, Choose Anohter: ");

		}

		clsUser user = clsUser::find(userName);

		return user;
	}

	bool checkAccessPermission (enPermissions permission ) {

		if (this->permissions == enPermissions::eAll) {
			return true;
		}
		else if ((this->permissions & permission) == permission) {
			return true;
		}
		else {
			return false;
		}

	}

	void RegisterLogin() {

		fstream myFile;
		myFile.open("loginRegister.txt", ios::out | ios::app); // append mode
		string loggedInUserRecord;

		if (myFile.is_open()) {

			loggedInUserRecord = _PrepareLogInRecord();
			myFile << loggedInUserRecord << endl;

			myFile.close();
		}
	}

	static vector <stLoginRegisterRecord> getLoginRegisterList() {

		vector < stLoginRegisterRecord> vLoginRegisterRecord;

		fstream loginRegisterFile;

		loginRegisterFile.open("loginRegister.txt", ios::in);

		if (loginRegisterFile.is_open()) {

			string line;
			stLoginRegisterRecord loginRegisterRecord;

			while (getline(loginRegisterFile, line)) {

				loginRegisterRecord = _ConvertLoginRegisterLineToRecord(line);

				vLoginRegisterRecord.push_back(loginRegisterRecord);

			}

			loginRegisterFile.close();

		}

		return vLoginRegisterRecord;
	}


};

