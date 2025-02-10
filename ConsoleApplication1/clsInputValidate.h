#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"


class clsInputValidate
{

public:

	//static bool isNumberBetween(int num, int from, int to) {
	//	return (num >= from && num <= to);
	//}	

	//static bool isNumberBetween(short num, short from, short to) {
	//	return (num >= from && num <= to);
	//}	

	//static bool isNumberBetween(double num, double from, double to) {
	//	return (num >= from && num <= to);
	//}

	//static bool isNumberBetween(float num, float from, float to) {
	//	return (num >= from && num <= to);
	//}

	template <typename T>
	static bool isNumberBetween(T num, T from, T to) {
		return (num >= from && num <= to);
	}


	//static int readIntNumber(string message = "inter number: ") {
	//	int number;
	//	cout << message;
	//	cin >> number;
	//	while (cin.fail()) {
	//		cin.clear();
	//		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//		cout << "inter a number not a char or a string: ";
	//		cin >> number;
	//	}

	//	return number;
	//}

	//static short readShortNumber(string message = "inter number: ") {
	//	short number;
	//	cout << message;
	//	cin >> number;
	//	while (cin.fail()) {
	//		cin.clear();
	//		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//		cout << "inter a number not a char or a string: ";
	//		cin >> number;
	//	}

	//	return number;
	//}

	//static float readFloatNumber(string message = "inter number: ") {
	//	float number;
	//	cout << message;
	//	cin >> number;
	//	while (cin.fail()) {
	//		cin.clear();
	//		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//		cout << "inter a number not a char or a string: ";
	//		cin >> number;
	//	}

	//	return number;
	//}

	//static double readDbNumber(string message = "inter number: ") {
	//	double number;
	//	cout << message;
	//	cin >> number;
	//	while (cin.fail()) {
	//		cin.clear();
	//		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//		cout << "inter a number not a char or a string: ";
	//		cin >> number;
	//	}

	//	return number;
	//}

	template <typename T>
	static T readNumber(string message = "inter a number: ") {

		T number;
		cout << message;
		cin >> number;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "inter a number not a char or a string: ";
			cin >> number;
		}

		return number;

	}


	//static int readIntNumberBetween(int from, int to, string msgAppersIfNumOutOfRange = "number is out of range: ") {
	//	int number = readIntNumber("");

	//	while (!isNumberBetween(number, from, to)) {
	//		number = readIntNumber(msgAppersIfNumOutOfRange);
	//	}

	//	return number;
	//}

	//static short readShortNumberBetween(short from, short to, string msgAppersIfNumOutOfRange = "number is out of range: ") {
	//	short number = readShortNumber("");

	//	while (!isNumberBetween(number, from, to)) {
	//		number = readShortNumber(msgAppersIfNumOutOfRange);
	//	}

	//	return number;
	//}

	//static double readDbNumberBetween(double from, double to, string msgAppersIfNumOutOfRange = "number is out of range: ") {
	//	double number = readDbNumber("");

	//	while (!isNumberBetween(number, from, to)) {
	//		number = readDbNumber(msgAppersIfNumOutOfRange);
	//	}

	//	return number;
	//}	
	//
	//static float readFloatNumberBetween(float from, float to, string msgAppersIfNumOutOfRange = "number is out of range: ") {
	//	float number = readNumber<float>("");

	//	while (!isNumberBetween(number, from, to)) {
	//		number = readNumber<float>(msgAppersIfNumOutOfRange);
	//	}

	//	return number;
	//}

	template <typename T>
	static T readNumberBetween(T from, T to, string msgAppersIfNumOutOfRange = "number is out of range: ") {

		T number = readNumber <T>("");

		while (!isNumberBetween(number, from, to)) {
			number = readNumber <T>(msgAppersIfNumOutOfRange);
		}

		return number;
	}


	static bool isDateBetween(clsDate date, clsDate startDate, clsDate endDate) {

		if (clsDate::isDate1AfterDate2(startDate, endDate)) {
			clsDate::swapDates(startDate, endDate);
		}

		return (clsDate::compareDates(date, startDate) >= 0 && clsDate::compareDates(date, endDate) <= 0);
	}

	static bool isValidDate(clsDate date) {

		return clsDate::isValidDate(date);

	}

	static string readString(const string& message = "Inter a message: ") {

			cout << message;
			string s = "";
			getline(cin >> ws, s);
			return s;
		
	}


};

