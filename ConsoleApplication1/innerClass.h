#pragma once

#include <iostream>;
using namespace std;


class clsPersons {

	class clsAddress {

		string _Address1;
		string _City;
		string _Country;

	public:

		clsAddress(string address1, string city, string country) {
			_Address1 = address1;
			_City = city;
			_Country = country;
		}

		void print() {
			cout << "Address1: " << _Address1 << endl;
			cout << "City: " << _City << endl;
			cout << "Country: " << _Country << endl;
		}

		string address() {
			return _Address1;
		}

		void setAddress(string address) {
			_Address1 = address;
		}

		string city() {
			return _City;
		}

		void setCity(string city) {
			_City = city;
		}

		string country() {
			return _Country;
		}

		void setCountry(string country) {
			_Country = country;
		}

	};
	string _FirstName;
	string _LastName;

public:

	clsAddress address1;

	clsPersons(string address1, string city, string country, string firstName, string lastName) :
		address1(address1, city, country)
	{
		_FirstName = firstName;
		_LastName = lastName;
	}

	string firstName() {
		return _FirstName;
	}

	void setFirstName(string name) {
		_FirstName = name;
	}

	string lastName() {
		return _LastName;
	}

	void setLastName(string name) {
		_LastName = name;
	}

	string fullName() {
		return (_FirstName + " " + _LastName);
	}



};


class clsTest {

private:
	string _FirstName;
	string _LastName;

public:

	static int counter;
	int var = 10;

	// static functions can be called by class level => clsTest::fun() (you don't need to initiate an object to use static function).
	static int fun() {
		return 10 + counter;
	}

	// constructor is a function that has the same name as class name and take no type
	// the constructor function is executed dynamically when an opject is created
	clsTest(string firstName, string lastName) {
		_FirstName = firstName;
		_LastName = lastName;
		counter++;
	}

	// destructor
	// the destructor function is executed dynamically when an opject is finished
	~clsTest() {
		cout << "\nhi I'm destructor\n";
	}

	void setFirstName(string firstName) {
		_FirstName = firstName;
	}
	string getFirstName() {
		return _FirstName;
	}

	void setLastName(string lastName) {
		_LastName = lastName;
	}
	string getLastName() {
		return _LastName;
	}

	string fullName() {
		return (_FirstName + " " + _LastName);
	}

	__declspec(property(get = getFirstName, put = setFirstName)) string firstName;
	__declspec(property(get = getLastName, put = setLastName)) string lastName;

};
int clsTest::counter = 10;