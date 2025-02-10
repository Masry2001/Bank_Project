#pragma once

#include <iostream>;
using namespace std;

class clsPerson {

private:
	short _ID;
	string _FirstName, _LastName, _Email, _Phone;


public:
	// you can have more than one constructor
	//Constructor
	//parametrized constructor
	// constructor is exceuted once we create the opject
	clsPerson(short id, string firstName, string lastName, string email, string phone) {
		_ID = id;
		_FirstName = firstName;
		_LastName = lastName;
		_Email = email;
		_Phone = phone;
	}



	void print() {
		cout << "\nInfo:";
		cout << "\n_________________________\n";

		cout << "ID\t : " << _ID << endl;
		cout << "FirstName: " << _FirstName << endl;
		cout << "LastName : " << _LastName << endl;
		cout << "FullName : " << _FirstName << " " << _LastName << endl;
		cout << "Email\t : " << _Email << endl;
		cout << "Phone\t : " << _Phone << endl;

		cout << "\n_________________________\n";
	}

	void sendEmail(string subject, string body) {
		cout << "\nThe follwing message sent successfully to email: " << _Email << endl;
		cout << "Subject: " << subject << endl;
		cout << "Body: " << body << endl;
	}

	void sendSMS(string message) {
		cout << "\nThe follwing SMS sent successfully to phone: " << _Phone << endl;
		cout << message << endl;
	}

	short id() {
		return _ID;
	}

	string firstName() {
		return _FirstName;
	}

	string lastName() {
		return _LastName;
	}

	string email() {
		return _Email;
	}

	string phone() {
		return _Phone;
	}

	string fullName() {
		return (_FirstName + " " + _LastName);
	}

	void setEmail(string email) {
		_Email = email;
	}

	void setFirstName(string firstName) {
		_FirstName = firstName;

	}

	void setLastName(string lastName) {
		_LastName = lastName;

	}

	void setPhone(string phone) {
		_Phone = phone;
	}

};

class clsEmployee : public clsPerson {

private:
	string _Title, _Department;
	int _Salary;

public:

	clsEmployee(short id, string firstName, string lastName, string email, string phone, string title, string department, int salary) : clsPerson(id, firstName, lastName, email, phone) {

		_Title = title;
		_Department = department;
		_Salary = salary;

	}


	// get properties
	string title() {
		return _Title;
	}

	string department() {
		return _Department;
	}

	int salary() {
		return _Salary;
	}

	// set properties

	void setTitle(string title) {
		_Title = title;
	}


	void setDepartment(string department) {
		_Department = department;
	}

	void setSalary(int salary) {
		_Salary = salary;
	}



	void print() {
		cout << "\nemployee info:";
		cout << "\n__________________________________\n";
		cout << "id\t  : " << id() << endl;
		cout << "firstname : " << firstName() << endl;
		cout << "lastname  : " << lastName() << endl;
		cout << "fullname  : " << fullName() << endl;
		cout << "title\t  : " << _Title << endl;
		cout << "department: " << _Department << endl;
		cout << "salary\t  : " << _Salary << endl;
		cout << "email\t  : " << email() << endl;
		cout << "phone\t  : " << phone() << endl;
		cout << "__________________________________\n";
	}

};

class clsDeveloper : public clsEmployee {

private:
	string _MainProgrammingLang;

public:
	clsDeveloper(short id, string firstName, string lastName, string email, string phone,
		string title, string department, int salary, string mainProgrammingLang)
		: clsEmployee(id, firstName, lastName, email, phone, title, department, salary)
	{
		_MainProgrammingLang = mainProgrammingLang;
	}

	//get properties
	string mainProgrammingLang() {
		return _MainProgrammingLang;
	}

	//set properties
	void setMainProgrammingLang(string mainProgrammingLang) {
		_MainProgrammingLang = mainProgrammingLang;
	}

	void print() {
		cout << "\nDeveloper info:";
		cout << "\n_______________________________________________\n";
		cout << "id                       : " << id() << endl;
		cout << "firstname                : " << firstName() << endl;
		cout << "lastname                 : " << lastName() << endl;
		cout << "fullname                 : " << fullName() << endl;
		cout << "title                    : " << title() << endl;
		cout << "department               : " << department() << endl;
		cout << "salary                   : " << salary() << endl;
		cout << "email                    : " << email() << endl;
		cout << "phone                    : " << phone() << endl;
		cout << "main Programming language: " << _MainProgrammingLang << endl;
		cout << "_______________________________________________\n";
	}
};

