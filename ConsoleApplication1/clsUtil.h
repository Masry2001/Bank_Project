#pragma once

#include <iostream>
#include <string>
#include <ctime> 
#include <cstdlib>
#include "clsDate.h"

using namespace std;

class clsUtil
{

public:
	static void Srand() {
		srand((unsigned)time(0));

	}

	static string encryptText(string text, short encryptionKey = 2) {

		for (short i = 0; i < text.length(); i++) {

			text[i] = char((short)text[i] + encryptionKey);
		}
		return text;
	}

	static string decryptText(string encryptedText, short encryptionKey = 2) {

		for (short i = 0; i < encryptedText.length(); i++) {

			encryptedText[i] = char((short)encryptedText[i] - encryptionKey);
		}
		return encryptedText;
	}

	static short generateRandomNum(short from, short to) {
		short random = rand() % (to - from + 1) + from;
		return random;
	}

	static short generateRandomNumORChar() {
		// Create a randomCharOrNum digits, uppercase, and lowercase letters
		const char randomCharOrNum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		// Get the size of the randomCharOrNum
		const int randomCharOrNumSize = strlen(randomCharOrNum); // get length
		// Generate a random index within the range of the pool
		int randomIndex = generateRandomNum(0, randomCharOrNumSize - 1);

		// Return the randomly selected character from the pool
		return randomCharOrNum[randomIndex];
	}
	static enum enCharType {
		smallChar,
		capChar,
		number,
		specialChar,
		mixChars
	};

	static char getRandomChar(enCharType charType) {
		switch (charType) {
		case specialChar:
			return char(generateRandomNum(32, 47));
		case number:
			return generateRandomNum(48, 57);
		case capChar:
			return char(generateRandomNum(65, 90));
		case smallChar:
			return char(generateRandomNum(97, 122));
		case mixChars:
			return char(generateRandomNumORChar());
		}
	}

	static string generateWord(enCharType charType, short wordLength) {
		string word;
		for (int i = 1; i <= wordLength; i++) {
			word = word + getRandomChar(charType);
		}
		return word;
	}

	static string generateKey(short wordLength) {
		string key = "";
		for (int i = 1; i <= 3; i++) {
			key = key + generateWord(enCharType::capChar, wordLength) + "-";
		}
		return key + generateWord(enCharType::capChar, wordLength);
	}

	static void generateKeys(short numberOfKeys, short wordLength) {
		for (int i = 1; i <= numberOfKeys; i++) {
			cout << "Key [" << i << "]: ";
			cout << generateKey(wordLength) << endl;
		}
	}

	static string numberToText(int number) {

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

	static void swap(int& num1, int& num2) {
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void swap(short& num1, short& num2) {
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void swap(float& num1, float& num2) {
		float temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void swap(clsDate& date1, clsDate& date2) {
		clsDate tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}

	static void swap(string& s1, string& s2) {
		string temp = s1;
		s1 = s2;
		s2 = temp;
	}

	static void shuffleArray(short arr[100], short arrLength) {
		for (short i = 0; i < arrLength; i++) {
			swap(arr[i], arr[generateRandomNum(0, arrLength - 1)]);
		}
	}

	static void shuffleArray(string arr[100], short arrLength) {
		for (short i = 0; i < arrLength; i++) {
			swap(arr[i], arr[generateRandomNum(0, arrLength - 1)]);
		}
	}

	static void printArrOfNums(short arr[100], short arrLength) {
		for (short i = 0; i < arrLength; i++) {
			cout << arr[i] << " ";
		}
	}

	static void printArrOfString(string arr[100], short arrLength) {

		for (short i = 0; i < arrLength; i++) {
			cout << "arr[" << i << "]: " << arr[i] << endl;
		}
	}

	static void fillArrWithRandomNums(short arr[100], short arrLength, short from, short to) {
		for (short i = 0; i < arrLength; i++) {
			arr[i] = generateRandomNum(from, to);
		}
	}

	static void fillArrWithRandomWords(string arr[100], short numberOfKeys, enCharType charType, short wordLength) {
		for (short i = 0; i < numberOfKeys; i++) {
			arr[i] = generateWord(charType, wordLength);
		}
	}	
	
	static void fillArrWithRandomKeys(string arr[100], short numberOfKeys) {
		for (short i = 0; i < numberOfKeys; i++) {
			arr[i] = generateKey(4);
		}
	}

	static string tabs(short numOfTabs) {
		string tabs = "";
		for (short i = 1; i <= numOfTabs; i++) {
			tabs += "	";
		}
		return tabs;
	}


};

