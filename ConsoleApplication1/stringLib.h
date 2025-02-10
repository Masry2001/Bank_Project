#pragma once


#include <iostream>
#include <vector>
#include <string>
#include "myLibrary.h"

using namespace std;

namespace stringLib {

	// moved to clsString
	string readString(const string& message) {
		cout << message << ": ";

		const int bufferSize = 256; // Adjust buffer size as needed
		char buffer[bufferSize];
		cin.getline(buffer, bufferSize);

		return string(buffer);
	}



	// moved to clsString
	void printFirstCharOfEachWord(string name) {
		cout << name[0] << endl;
		for (short i = 0; i < name.length(); i++) {
			if (name[i] == ' ') {

				cout << name[i + 1] << endl;
			}
		}
	}


	// moved to clsString
	string capFirstCharOfString(string name) {
		name[0] = toupper(name[0]);
		for (short i = 0; i < name.length(); i++) {
			if (name[i] == ' ') {

				name[i + 1] = toupper(name[i + 1]);
			}
		}
		return name;
	}


	// moved to clsString
	string lowerFirstCharOfString(string name) {
		name[0] = tolower(name[0]);
		for (short i = 0; i < name.length(); i++) {
			if (name[i] == ' ') {
				name[i + 1] = tolower(name[i + 1]);
			}
		}
		return name;
	}


	// moved to clsString
	string upperAllLetters(string name) {
		for (short i = 0; i < name.length(); i++) {
			name[i] = toupper(name[i]);
		}
		return name;
	}

	// moved to clsString
	string lowerAllLetters(string name) {
		for (short i = 0; i < name.length(); i++) {
			name[i] = tolower(name[i]);
		}
		return name;
	}

	// moved to clsString
	char readChar(string message) {
		char ch;
		cout << message << endl;
		cin >> ch;
		return ch;
	}

	// moved to clsString
	char invertCharCase(char ch) {
		return (isupper(ch) ? tolower(ch) : toupper(ch));
	}

	// moved to clsString
	string invertAllStringLetters(string st) {
		for (short i = 0; i < st.length(); i++) {
			st[i] = invertCharCase(st[i]);
		}
		return st;
	}

	// moved to clsString
	short countSmallLetters(string st) {
		short smallLetters = 0;
		for (short i = 0; i < st.length(); i++) {
			if (islower(st[i])) {
				smallLetters++;
			}
		}
		return smallLetters;
	}


	// moved to clsString
	short countCapLetters(string st) {
		short capLetters = 0;
		for (short i = 0; i < st.length(); i++) {
			if (isupper(st[i])) {
				capLetters++;
			}
		}
		return capLetters;
	}

	// moved to clsString
	short countOfSpecificCharInString(string st, char ch, bool matchcase = false) {
		short count = 0;
		for (short i = 0; i < st.length(); i++) {
			if (matchcase) {
				if (st[i] == ch) {
					count++;
				}
			}
			else if (tolower(ch) == tolower(st[i])) {
				count++;
			}

		}
		return count;
	}



	// moved to clsString
	bool isVowel(char ch) {
		ch = tolower(ch);
		return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
	}


	// moved to clsString
	short countVowels(string st) {
		short count = 0;
		for (short i = 0; i < st.length(); i++) {
			if (isVowel(st[i])) {
				count++;
			}
		}
		return count;

	}

	// moved to clsString
	void printVowelsInString(string st) {

		cout << "Vowels are " << endl;
		for (short i = 0; i < st.length(); i++) {
			if (isVowel(st[i])) {
				cout << st[i] << "    ";
			}
		}
	}

	// moved to clsString
	void printEachWordInString(string st) {
		// if you use find() function to search for a substring and the substring is not found, std::string::npos is returned.

		cout << "Words Are: " << endl;
		string delimiter = " ";
		string singleWord;
		short pos;

		while ((pos = st.find(delimiter)) != std::string::npos) {

			singleWord = st.substr(0, pos);
			if (singleWord != "") {
				cout << singleWord << endl;
			}

			st.erase(0, pos + delimiter.length());

		}

		if (st != "") {
			cout << st << endl;
		}

	}

	// moved to clsString
	short countNumberOfWordsInString(string st) {
		string delimiter = " ";
		string singleWord;
		short pos;
		short counter = 0;

		while ((pos = st.find(delimiter)) != std::string::npos) {

			singleWord = st.substr(0, pos);
			if (singleWord != "") {
				counter++;
			}

			st.erase(0, pos + delimiter.length());

		}

		if (st != "") {
			counter++;
		}
		return counter;
	} // done

	// moved to clsString
	vector <string> splitEachWordOfStringInToVector(string st, string delimiter) {
		// if you use find() function to search for a substring and the substring is not found, std::string::npos is returned.
		vector <string> vString;
		string singleWord;
		short pos;

		while ((pos = st.find(delimiter)) != std::string::npos) {

			singleWord = st.substr(0, pos);
			if (singleWord != "") {
				vString.push_back(singleWord);
			}

			st.erase(0, pos + delimiter.length());

		}

		if (st != "") {
			vString.push_back(st);
		}
		return vString;
	}

	// moved to clsString
	void printVectorString(vector <string>& vString) {
		cout << "Tokens = " << vString.size() << endl;
		for (string& st : vString) {
			cout << st << endl;
		}
	}



	// moved to clsString
	string trimLeft(string st) {

		for (short i = 0; i < st.length(); i++) {
			if (st[i] != ' ') {
				st.erase(0, i);
				return st;
			}
		}
		return "";
	}

	// moved to clsString
	string trimRight(string st) {
		for (short i = st.length() - 1; i >= 0; i--) {
			if (st[i] != ' ') {
				return st.substr(0, i + 1);

			}
		}
		return "";
	}

	// moved to clsString
	string trim(string st) {
		st = trimLeft(st);
		st = trimRight(st);
		return st;
	}

	// moved to clsString
	string joinAllWordsInVector(vector<string>& vString, string delimiter) {

		string sentence = "";
		for (string& st : vString) {
			sentence += st + delimiter;
		}

		if (!sentence.empty()) {

			sentence.pop_back(); // removing the last delimeter
			
		}

		return sentence;
	}

	// moved to clsString
	string joinAllWordsInArr(string arr[], int arrLength, string delimiter) {

		string word = "";
		for (short i = 0; i < arrLength; i++) {
			word += arr[i] + delimiter;
		}

		if (!word.empty()) {
			word = word.erase(word.length() - delimiter.length(), delimiter.length());
		}

		return word;
	}

	// moved to clsString
	string reverseWords(string st) {
		vector <string> vString;
		string s2 = "";
		vString = splitEachWordOfStringInToVector(st, " ");

		// declare iterator 
		vector <string>::iterator iter = vString.end();
		while (iter != vString.begin()) {
			iter--;
			s2 = s2 + *iter + " ";
		}
		s2 = s2.substr(0, s2.length() - 1); // remove last space
		return s2;
	}

	// moved to clsString
	string replaceWords(string st, string wordToReplace, string wordToPut) {
		vector<string> vString;
		string st2 = "";
		vString = splitEachWordOfStringInToVector(st, " ");

		vector<string>::iterator iter;
		iter = vString.begin();
		while (iter != vString.end()) {
			if (*iter == wordToReplace) {
				*iter = wordToPut;
			}
			st2 = st2 + *iter + " ";
			iter++;
		}
		st2 = st2.substr(0, st2.length() - 1);
		return st2;

	}

	// moved to clsString
	string replaceWordsNoCaseSensitive(string st, string wordToReplace, string wordToPut) {
		vector<string> vString;
		string st2 = "";
		vString = splitEachWordOfStringInToVector(st, " ");

		vector<string>::iterator iter;
		iter = vString.begin();

		while (iter != vString.end()) {
			if (lowerAllLetters(*iter) == lowerAllLetters(wordToReplace)) {
				*iter = wordToPut;

			}
			st2 = st2 + *iter + " ";
			iter++;
		}
		st2 = st2.substr(0, st2.length() - 1);
		return st2;
	}

	// moved to clsString
	string replaceWordsWithCaseSensitiveOption(string st, string wordToReplace, string wordToPut, bool caseSensitive = false) {
		vector<string> vString;
		string st2 = "";
		vString = splitEachWordOfStringInToVector(st, " ");

		vector<string>::iterator iter;
		iter = vString.begin();

		if (caseSensitive) {
			while (iter != vString.end()) {
				if (*iter == wordToReplace) {
					*iter = wordToPut;
				}
				st2 = st2 + *iter + " ";
				iter++;
			}
		}
		else {
			while (iter != vString.end()) {
				if (lowerAllLetters(*iter) == lowerAllLetters(wordToReplace)) {
					*iter = wordToPut;
				}
				st2 = st2 + *iter + " ";
				iter++;
			}
		}


		st2 = st2.substr(0, st2.length() - 1);
		return st2;
	}

	// moved to clsString
	string replaceWordsUsingRepalceFunc(string st, string wordToReplace, string wordToPut) {
		short pos = st.find(wordToReplace);
		while (pos != std::string::npos) {
			st = st.replace(pos, wordToReplace.length(), wordToPut);
			pos = st.find(wordToReplace);
		}
		return st;
	}

	// moved to clsString
	string removePunctuationsFromString(string st) {
		string result = "";
		for (short c = 0; c < st.length(); c++) {
			if (!ispunct(st[c])) {
				result = result + st[c];
			}
		}
		return result;
	}

	// moved to clsString
	void clearIpnutStream() {
		// Clear input stream
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}



}