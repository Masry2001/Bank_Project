#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;



namespace myLibrary {


	int readPositiveNumber(string message) {
		int N;
		do {
			cout << message << endl;
			cin >> N;
		} while (N < 0);
		return N;
	}

	// moved to clsString 
	int readNumber(string message) {
		int number;
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

	static int readIntNumber(string message = "inter number: ") {
		int number;
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

	static short readShortNumber(string message = "inter number: ") {
		short number;
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

	static double readDbNumber(string message = "inter number: ") {
		double number;
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

	// moved to clsString 
	int generateRandomNum(int from, int to) {
		int random = rand() % (to - from + 1) + from;
		return random;
	}

	// moved to clsUtil
	void swap(int& A, int& B) {
		int temp;
		temp = A;
		A = B;
		B = temp;
	}

	int frequencyOfOneNumInABigNum(int digit, int digitToCheck) {

		int frequeny = 0, lastN = 0;

		while (digit > 0) {

			lastN = digit % 10;
			digit = digit / 10;
			if (lastN == digitToCheck) {
				frequeny = frequeny + 1;
			}
		}
		return frequeny;
	}

	void printDigitsFrequency(int digit) {

		for (int i = 0; i < 10; i++) {
			short digitFrequency = 0;
			digitFrequency = frequencyOfOneNumInABigNum(digit, i);

			if (digitFrequency > 0) {
				cout << "frequency of digit " << i << " in the digit " << digit << " = " << digitFrequency << endl << endl;
			}
		}
	}

	int reverseNumber(int digit) {
		int lastN = 0, reversedDigit = 0;

		while (digit > 0) {
			lastN = digit % 10;
			digit = digit / 10;
			reversedDigit = reversedDigit * 10 + lastN;
		}
		return reversedDigit;
	}

	void isItPlaindrome(int number) {

		int reversedNumber = reverseNumber(number);

		if (number == reversedNumber) {
			cout << number << " is a plaindrome number\n";
		}
		else {
			cout << number << " is not a plaindrome number\n";
		}

	}

	// moved to clsString 
	string encryptText(string text, short encryptionKey) {

		cout << "text before encryption is " << text << endl;

		for (int i = 0; i < text.length(); i++) {

			text[i] = char((int)text[i] + encryptionKey);
		}
		return text;
	}

	// moved to clsString
	string decryptText(string encryptedText, short encryptionKey) {

		for (int i = 0; i < encryptedText.length(); i++) {
			encryptedText[i] = char((int)encryptedText[i] - encryptionKey);
		}
		return encryptedText;
	}

	// moved to clsString
	enum enCharType {
		smallLetter,
		capLetter,
		number,
		specialChar
	};

	// moved to clsString
	char getRandomChar(enCharType charType) {
		switch (charType) {
		case specialChar:
			return generateRandomNum(32, 47);
		case number:
			return generateRandomNum(48, 57);
		case capLetter:
			return generateRandomNum(65, 90);
		case smallLetter:
			return generateRandomNum(97, 122);
		}
	}

	// moved to clsString
	string generateWord(enCharType charType, short wordLength) {
		string word;
		for (int i = 1; i <= wordLength; i++) {
			word = word + getRandomChar(charType);
		}
		return word;
	}	
	
	// moved to clsString
	string generateKey(short wordLength) {
		string key = "";
		for (int i = 1; i <= 3; i++) {
			key = key + generateWord(enCharType::capLetter, wordLength) + "-";
		}
		return key + generateWord(enCharType::capLetter, wordLength);
	}


	// moved to clsString
	void generateKeys(short numberOfKeys, short wordLength) {
		for (int i = 1; i <= numberOfKeys; i++) {
			cout << "Key [" << i << "]: ";
			cout << generateKey(wordLength) << endl;
		}
	}

	enum enPrimeOrNotPrime { prime = 1, notPrime = 2 };
	enPrimeOrNotPrime checkPrime(int number) {
		int m = number / 2;

		if (number <= 1) {
			return enPrimeOrNotPrime::notPrime;
		}

		for (int i = 2; i <= m; i++) {
			if (number % i == 0) {
				return enPrimeOrNotPrime::notPrime;
			}
		}
		return enPrimeOrNotPrime::prime;
	}

	int myPower(int base, int power) {
		if (power == 0) {
			return 1;
		}
		else {
			return (base * myPower(base, power - 1));
		}
	}

	void AddNumsToVec(vector <int>& vNums) {
		bool addMore = true;
		do {
			vNums.push_back(readNumber("inter a number"));
			cout << "\ndo you wnat to add more nums press 1\n";
			cin >> addMore;
		} while (addMore);
	}

	void printVectorNums(vector <int>& vNums) {
		printf("Vecotr numbers are: \n");
		for (int& num : vNums) {
			printf("%d  ", num);
		}
	}

	struct stPersonData {
		string fName;
		string lName;
		int age = 0;
	};

	void addPeopleToVec(vector <stPersonData>& vPeopleData) {
		stPersonData person;
		bool addMore = true;

		cout << "\nif you wnat to add person press 1 else press any\n";
		cin >> addMore;

		while (addMore) {
			cout << "enter first name: ";
			cin >> person.fName;
			cout << endl;

			cout << "enter last name: ";
			cin >> person.lName;
			cout << endl;

			cout << "enter age: ";
			cin >> person.age;

			vPeopleData.push_back(person);
			cout << "\nif you wnat to add person press 1 else press any\n";
			cin >> addMore;
		};
	}

	void printPeopleVector(vector <stPersonData>& vPeopleData) {
		printf("Vecotr People are: \n");
		for (stPersonData& person : vPeopleData) {
			cout << "first name: " << person.fName << endl;
			cout << "last name : " << person.lName << endl;
			cout << "age       : " << person.age << endl;
			cout << endl;
		}
		cout << endl;
	}


	void swapUsingPointers(int* p1, int* p2) {
		int temp = 1;
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
	}

	void swapUsingReference(int& x, int& y) {
		int temp = 1;
		temp = x;
		x = y;
		y = temp;
	}


	void loadDataFromFileToVector(string fileName, vector <string>& vFileContent) {
		fstream myFile;

		myFile.open(fileName, ios::in);

		if (myFile.is_open()) {
			string line;

			while (getline(myFile, line)) {

				vFileContent.push_back(line);
			}

			myFile.close();
		}
	}

	void printFileContent(string fileName) {
		fstream myFile;
		myFile.open(fileName, ios::in);

		if (myFile.is_open()) {
			string line;
			while (getline(myFile, line)) {
				cout << line << endl;

			}
			myFile.close();
		}
	}

	void saveVectorToFile(string fileName, vector <string> vFileContent) {
		fstream myFile;

		myFile.open(fileName, ios::out);

		if (myFile.is_open()) {
			for (string& line : vFileContent) {
				if (line != "") {
					myFile << line << endl;
				}
			}
		}
	}

	void deleteRecordFromFile(string fileName, string record) {
		vector <string> vFileContent;

		loadDataFromFileToVector(fileName, vFileContent);

		for (string& line : vFileContent) {
			if (line == record) {
				line = "";
			}
		}

		saveVectorToFile(fileName, vFileContent);
	}

	void updateRecordInFile(string fileName, string record, string updateTo) {
		vector <string> vFileContent;

		loadDataFromFileToVector(fileName, vFileContent);

		for (string& line : vFileContent) {
			if (line == record) {
				line = updateTo;
			}
		}

		saveVectorToFile(fileName, vFileContent);
	}

	void addRecordToFile(string fileName, string record) {
		fstream myFile;
		myFile.open(fileName, ios::app);
		myFile << record << endl;
		myFile.close();
	}

	void fibonacciSeriesUsingForLoop(short num) {
		int previous2 = 0;
		int previous1 = 1;
		int current = 1;

		for (short i = 0; i < num; i++) {
			cout << setw(4) << current << endl;
			current = previous2 + previous1;
			previous2 = previous1;
			previous1 = current;
		}
	}


	void fibonacciSeriesUsingRecursion(short num, int previous1, int previous2, int current) {

		if (num > 0) {
			cout << current << endl;
			current = previous2 + previous1;
			previous2 = previous1;
			previous1 = current;
			fibonacciSeriesUsingRecursion(num - 1, previous1, previous2, current);
		}


	}






	// moved to clsUtil
	string numberToText(int number) {

		if (number == 0) {
			return "";
		}

		if (number >= 1 && number <= 19) {
			string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

			return arr[number] + " ";
		}

		if (number >= 20 && number <= 99) {

			string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

			return arr[number / 10] + " " + numberToText(number % 10);

		}

		if (number >= 100 && number <= 199) {

			return "One Hundred " + numberToText(number % 100);

		}

		if (number >= 200 && number <= 999) {

			return numberToText(number / 100) + "Hundreds " + numberToText(number % 100);

		}

		if (number >= 1000 && number <= 1999) {

			return "One Thousand " + numberToText(number % 1000);

		}

		if (number >= 2000 && number <= 999999) {

			return numberToText(number / 1000) + "Thousands " + numberToText(number % 1000);

		}

		if (number >= 1000000 && number <= 1999999) {

			return "One Million " + numberToText(number % 1000000);

		}

		if (number >= 2000000 && number <= 999999999) {

			return numberToText(number / 1000000) + "Millions " + numberToText(number % 1000000);

		}

		if (number >= 1000000000 && number <= 1999999999) {

			return "One Billion " + numberToText(number % 1000000000);

		}
		else {

			return numberToText(number / 1000000000) + "Billions " + numberToText(number % 1000000000);

		}

	}





}