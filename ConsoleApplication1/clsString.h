#pragma once
#include <iostream>;
#include <vector>;
using namespace std;

class clsString
{

private:
	string _Value;



public:
	// constructor (no parameter needed)
	clsString() {
		_Value = "";
	}
	// paramaterized constructor
	clsString(string value) {
		_Value = value;
	}

	// get value
	string getValue() {
		return _Value;
	}

	//set value
	void setValue(string newValue ) {
		_Value = newValue;
	}

	__declspec(property(get = getValue, put = setValue)) string value;

	static short countWords(string st) {
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
	}
	short countWords() {
		return countWords(_Value);
	}

	// moved to clsInputValidate
	static string readString(const string& message) {
		cout << message << ": ";

		const int bufferSize = 256; // Adjust buffer size as needed
		char buffer[bufferSize];
		cin.getline(buffer, bufferSize);

		return string(buffer);
	}

	static void printFirstCharOfEachWord(string name) {
		cout << name[0] << endl;
		for (short i = 0; i < name.length(); i++) {
			if (name[i] == ' ') {

				cout << name[i + 1] << endl;
			}
		}
	}
	void printFirstCharOfEachWord() {
		printFirstCharOfEachWord(_Value);
	}

	static string capFirstCharOfEachWord(string name) {
		name[0] = toupper(name[0]);
		for (short i = 0; i < name.length(); i++) {
			if (name[i] == ' ') {

				name[i + 1] = toupper(name[i + 1]);
			}
		}
		return name;
	}
	void capFirstCharOfEachWord() {
		_Value = capFirstCharOfEachWord(_Value);
	}

	static string lowerFirstCharOfString(string name) {
		name[0] = tolower(name[0]);
		for (short i = 0; i < name.length(); i++) {
			if (name[i] == ' ') {
				name[i + 1] = tolower(name[i + 1]);
			}
		}
		return name;
	}
	void lowerFirstCharOfString() {
		_Value = lowerFirstCharOfString(_Value);
	}

	static string upperAllLetters(string name) {
		for (short i = 0; i < name.length(); i++) {
			name[i] = toupper(name[i]);
		}
		return name;
	}
	void upperAllLetters() {
		_Value =  upperAllLetters(_Value);
	}

	static string lowerAllLetters(string name) {
		for (short i = 0; i < name.length(); i++) {
			name[i] = tolower(name[i]);
		}
		return name;
	}
	void lowerAllLetters() {
		_Value = lowerAllLetters(_Value);
	}

	static char readChar(string message) {
		char ch;
		cout << message << endl;
		cin >> ch;
		return ch;
	}

	static char invertCharCase(char ch) {
		return (isupper(ch) ? tolower(ch) : toupper(ch));
	}

	static string invertAllStringLetters(string st) {
		for (short i = 0; i < st.length(); i++) {
			st[i] = invertCharCase(st[i]);
		}
		return st;
	}
	void invertAllStringLetters() {
		_Value = invertAllStringLetters(_Value);
	}

	static short countSmallLetters(string st) {
		short smallLetters = 0;
		for (short i = 0; i < st.length(); i++) {
			if (islower(st[i])) {
				smallLetters++;
			}
		}
		return smallLetters;
	}
	short countSmallLetters() {
		return countSmallLetters(_Value);
	}

	static short countCapLetters(string st) {
		short capLetters = 0;
		for (short i = 0; i < st.length(); i++) {
			if (isupper(st[i])) {
				capLetters++;
			}
		}
		return capLetters;
	}
	short countCapLetters() {
		return countCapLetters(_Value);
	}

	static short countSpaces(string st) {
		short spaces = 0;
		for (short i = 0; i < st.length(); i++) {
			if (st[i] == ' ') {
				spaces++;
			}
		}
		return spaces;
	}
	short countSpaces() {
		return countSpaces(_Value);
	}

	static short countrAllLetters(string st) {
		return ( countSmallLetters(st) + countCapLetters(st) + countSpaces(st));
	}
	short countrAllLetters() {
		return countrAllLetters(_Value);
	}

	static short countSpecificLetter(string st, char ch, bool matchcase = false) {
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
	short countSpecificLetter(char ch, bool matchcase = false) {
		return countSpecificLetter(_Value, ch, matchcase = false);
	}

	static bool isVowel(char ch) {
		ch = tolower(ch);
		return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
	}

	static short countVowels(string st) {
		short count = 0;
		for (short i = 0; i < st.length(); i++) {
			if (isVowel(st[i])) {
				count++;
			}
		}
		return count;

	}
	short countVowels() {
		return countVowels(_Value);
	}

	static void printVowels(string st) {

		cout << "\nVowels in " << st << " are: " << endl;
		for (short i = 0; i < st.length(); i++) {
			if (isVowel(st[i])) {
				cout << st[i] << "    ";
			}
		}
	}
	void printVowels() {
		printVowels(_Value);
	}

	static void printEachWordInString(string st) {
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
	void printEachWordInString() {
		printEachWordInString(_Value);
	}

	static vector <string> splitEachWordOfStringInToVector(string st, string delimiter) {
		// if you use find() function to search for a substring and the substring is not found, std::string::npos is returned.
		vector <string> vString;
		string singleWord;
		short pos = 0;

		while ((pos = st.find(delimiter)) != std::string::npos) {

			singleWord = st.substr(0, pos);
			//if (singleWord != "") { // Abu-hadhoud removed this condition
				vString.push_back(singleWord);
		//	}

			st.erase(0, pos + delimiter.length());

		}

		if (st != "") {
			vString.push_back(st);
		}
		return vString;
	}
	vector <string> splitEachWordOfStringInToVector(string delimiter) {
		return splitEachWordOfStringInToVector(_Value, delimiter);
	}

	static void printVectorString(vector <string>& vString) {
		cout << "Tokens = " << vString.size() << endl;
		for (string& st : vString) {
			cout << st << endl;
		}
	}

	static string trimLeft(string st) {

		for (short i = 0; i < st.length(); i++) {
			if (st[i] != ' ') {
				st.erase(0, i);
				return st;
			}
		}
		return "";
	}
	void trimLeft() {
		_Value = trimLeft(_Value);
	}

	static string trimRight(string st) {
		for (short i = st.length() - 1; i >= 0; i--) {
			if (st[i] != ' ') {
				return st.substr(0, i + 1);

			}
		}
		return "";
	}
	void trimRight() {
		_Value = trimRight(_Value);
	}

	static string trim(string st) {
		st = trimLeft(st);
		st = trimRight(st);
		return st;
	}
	void trim() {
		_Value = trim(_Value);
	}

	static string joinAllWordsInVector(vector<string>& vString, string delimiter) {

		string sentence = "";
		for (string& st : vString) {
			sentence += st + delimiter;
		}

		if (!sentence.empty()) {

			sentence.pop_back(); // removing the last delimeter

		}

		return sentence;
	}

	static string joinAllWordsInArr(string arr[], short arrLength, string delimiter) {

		string word = "";
		for (short i = 0; i < arrLength; i++) {
			word += arr[i] + delimiter;
		}

		if (!word.empty()) {
			word = word.erase(word.length() - delimiter.length(), delimiter.length());
		}

		return word;
	}

	static string reverseWords(string st) {
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
	void reverseWords() {
		_Value = reverseWords(_Value);
	}

	static string replaceWords(string st, string wordToReplace, string wordToPut) {
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
	void replaceWords(string wordToReplace, string wordToPut) {
		_Value = replaceWords(_Value, wordToReplace, wordToPut);
	}

	static string replaceWordsNoCaseSensitive(string st, string wordToReplace, string wordToPut) {
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
	void replaceWordsNoCaseSensitive(string wordToReplace, string wordToPut) {
		_Value = replaceWordsNoCaseSensitive(_Value, wordToReplace, wordToPut);
	}

	static string replaceWordsWithCaseSensitiveOption(
		string st, string wordToReplace, string wordToPut, bool caseSensitive = false) {


		if (caseSensitive) {
			return replaceWords(st, wordToReplace, wordToPut);
		}
		else {
			return replaceWordsNoCaseSensitive(st, wordToReplace, wordToPut);
		}



	}
	void replaceWordsWithCaseSensitiveOption(string wordToReplace, string wordToPut, bool caseSensitive = false) {
		_Value = replaceWordsWithCaseSensitiveOption(_Value, wordToReplace, wordToPut, caseSensitive = false);
	}

	static string replaceWordsUsingRepalceFunc(string st, string wordToReplace, string wordToPut) {
		short pos = st.find(wordToReplace);
		while (pos != std::string::npos) {
			st = st.replace(pos, wordToReplace.length(), wordToPut);
			pos = st.find(wordToReplace);
		}
		return st;
	}
	void replaceWordsUsingRepalceFunc(string wordToReplace, string wordToPut) {
		_Value = replaceWordsUsingRepalceFunc(_Value, wordToReplace, wordToPut);
	}

	static string removePunctuationsFromString(string st) {
		string result = "";
		for (short c = 0; c < st.length(); c++) {
			if (!ispunct(st[c])) {
				result = result + st[c];
			}
		}
		return result;
	}
	void removePunctuationsFromString() {
		_Value = removePunctuationsFromString(_Value);
	}

	static 	void clearIpnutStream() {
		// Clear input stream
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	static short length(string s1) {
		return s1.length();
	}
	short length() {
		return length(_Value);
	}
	

};

