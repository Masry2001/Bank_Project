#pragma warning(disable: 4996)
#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "stringLib.h"

using namespace std;

// non-static function can access non-static function and static funcion.
// static function can only access static function.

class clsDate
{

private:

	short _Day, _Month, _Year;

public:

	clsDate() {
		time_t timeNow = time(0); // get time now sice 1 jan 1970 in ms.
		tm* now = localtime(&timeNow);

		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;
	}

	clsDate(string dateString) {
		clsDate date = stringToDate(dateString);
		_Day = date._Day;
		_Month = date._Month;
		_Year = date._Year;
	}

	clsDate(short day, short month, short year) {
		_Day = day;
		_Month = month;
		_Year = year;
	}

	clsDate(short dayFromBegingOfYear, short year) {
		clsDate date = dateFromDayOrder(dayFromBegingOfYear, year);
		_Day = date._Day;
		_Month = date._Month;
		_Year = date._Year;
	}

	// get and set
	short day() {
		return _Day;
	}
	void setDay(short day) {
		_Day = day;
	}
	__declspec(property(get = day, put = setDay)) short Day;

	short month() {
		return _Month;
	}
	void setMonth(short month) {
		_Month = month;
	}
	__declspec(property(get = month, put = setMonth)) short Month;

	short year() {
		return _Year;
	}
	void setYear(short year) {
		_Year = year;
	}
	__declspec(property(get = year, put = setYear)) short Year;

	void print() {
		cout << dateToString() << endl;
	}

	static string dateToString(clsDate date) {
		return (to_string(date._Day) + "/" + to_string(date._Month) + "/" + to_string(date._Year));
	}
	string dateToString() {
		return dateToString(*this);
	}

	static clsDate stringToDate(string dateString) {

		vector <string> vDate = clsString::splitEachWordOfStringInToVector(dateString, "/");
		clsDate date;
		date._Day = stoi(vDate[0]);
		date._Month = stoi(vDate[1]);
		date._Year = stoi(vDate[2]);
		return date;
	}
	clsDate stringToDate() {
		string dateString = dateToString();
		return stringToDate(dateString);
	}

	static clsDate getSystemDate() {

		clsDate systemDate;

		return systemDate;


	}

	static tm timeNow() {
		time_t timeNow = time(0); // get time now sice 1 jan 1970 in ms.
		tm* now = localtime(&timeNow);
		return *now;
	}

	static short getSystemHour() {
		return timeNow().tm_hour;
	}
	static short getSystemMin() {
		return timeNow().tm_min;
	}	
	static short getSystemSec() {
		return timeNow().tm_sec;
	}

	static string getSystemHourMinSec() { // hour-minute-second
		
		return (to_string(getSystemHour()) + ":" + to_string(getSystemMin()) + ":" + to_string(getSystemSec()));

	}

	static string getSystemDateTimeString() {
		return (dateToString(getSystemDate()) + " - " + getSystemHourMinSec());
	}

	static clsDate dateFromDayOrder(short dayOrder, short year) {

		clsDate date;
		date._Month = 1;
		date._Year = year;
		short remainingDays = dayOrder;

		for (short i = 1; i <= 12; i++) {

			remainingDays = remainingDays - numberOfDaysInMonth(year, i);

			if (remainingDays <= 0) {

				date._Day = remainingDays + numberOfDaysInMonth(year, i);
				break;

			}
			else {
				date._Month++;
			}
		}
		return date;
	}
	clsDate dateFromDayOrder() {
		return dateFromDayOrder(this->_Day, this->_Year);
	}

	static bool isLeapYear(short year) {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	bool isLeapYear() {
		return isLeapYear(this->_Year);
	}

	static short numberOfDaysInMonth(short year, short month) {
		if (month < 1 || month > 12)
			return 0;
		int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (month == 2) ? (isLeapYear(year) + 28) : daysInMonth[month - 1];

	}
	short numberOfDaysInMonth() {
		return numberOfDaysInMonth(this->_Year, this->_Month);
	}

	static string monthName(short monthNumber) {
		string months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return months[monthNumber - 1];
	}
	string monthName() {
		return monthName(this->_Month);
	}

	static short dayOrderInWeek(short year, short month, short day) {
		// equation name Zeller's congruence;
		// 0 to 6 (sunday to saturday)
		short a = ((14 - month) / 12);
		short y = year - a;
		short m = month + (12 * a) - 2;

		short dayOrder = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return dayOrder;
	}
	short dayOrderInWeek() {
		return dayOrderInWeek(this->_Year, this->_Month, this->_Day);
	}
	static short dayOrderInWeek(clsDate date) {
		// 0 to 6 (sunday to saturday)
		return dayOrderInWeek(date._Year, date._Month, date._Day);
	}

	static void monthCalander(short year, short month) {

		string days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		cout << endl << std::string(19, '_') << monthName(month) << std::string(18, '_') << endl << endl;

		short numberOfDays = numberOfDaysInMonth(year, month);
		short dayOrder = dayOrderInWeek(year, month, 1);

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		for (short i = 0; i < dayOrder; i++) {
			printf("     ");
		}

		short counter = dayOrder;

		for (short day = 1; day <= numberOfDays; day++) {

			printf("%5d", day);

			counter++;
			if (counter == 7) {
				cout << endl;
				counter = 0;
			}
		}

		cout << endl << std::string(40, '_') << endl;

	}
	void monthCalander() {
		monthCalander( this->_Year,  this->_Month);
	}

	static void yearClander(short year) {

		cout << endl << std::string(40, '_') << endl;
		printf("\n	Calander - %d\n", year);
		cout << endl << std::string(40, '_') << endl;

		for (short month = 1; month <= 12; month++) {
			monthCalander(year, month);
		}
	}
	void yearClander() {
		 yearClander(this->_Year);
	}

	// moved to clsUtil
	static bool isValidDate(clsDate date) {

		return (date._Month >= 1 && date._Month <= 12) && (date._Day >= 1 && date._Day <= numberOfDaysInMonth(date._Year, date._Month));

	}
	bool isValidDate() {
		return isValidDate(*this);
	}

	// moved to clsUtil
	static void swapDates(clsDate& date1, clsDate& date2) {
		clsDate tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}

	static bool isItLastDayInMonth(clsDate date) {
		return (date._Day == numberOfDaysInMonth(date._Year, date._Month));
	}
	bool isItLastDayInMonth() {
		return isItLastDayInMonth(*this);
	}

	static bool isItLastMonthInYear(short month) {
		return (month == 12);
	}

	bool isItLastMonthInYear() {
		return isItLastMonthInYear(this->_Month);
	}
	
	static clsDate increaseDateByOneDay(clsDate date) {

		if (isItLastDayInMonth(date)) {

			if (isItLastMonthInYear(date._Month)) {

				date._Year++;
				date._Month = 1;
				date._Day = 1;
			}
			else {
				date._Day = 1;
				date._Month++;
			}

		}
		else {
			date._Day++;
		}

		return date;

	}
	clsDate increaseDateByOneDay() {
		return increaseDateByOneDay(*this);
	}

	static short differenceBetweenDates(clsDate date1, clsDate date2, bool includeEndDay = false) {

		short days = 0;
		short swapFlag = 1;


		if (!isDate1BeforeDate2(date1, date2)) {
			swapDates(date1, date2);
			swapFlag = -1;
		}

		while (isDate1BeforeDate2(date1, date2)) {
			days++;
			date1 = increaseDateByOneDay(date1);
		}



		return (includeEndDay ? ++days * swapFlag : days * swapFlag);

	}
	short differenceBetweenDates( clsDate date2, bool includeEndDay = false) {
		return differenceBetweenDates(*this, date2, includeEndDay = false);
	}

	static int ageInDays(clsDate dateOfBirth) { // 6/11/1977
		clsDate systemDate; // date from default constructor represent the systme date
		int numOfDays = differenceBetweenDates(dateOfBirth, systemDate);

		return numOfDays;

	}
	int ageInDays() {
		return ageInDays(*this);
	}

	static short numberOfDaysInYear(short year) {
		return isLeapYear(year) ? 366 : 365;
	}
	short numberOfDaysInYear() {
		return numberOfDaysInYear(this->_Year);
	}

	static short numberOfHoursInYear(short year) {
		return numberOfDaysInYear(year) * 24;
	}
	short numberOfHoursInYear() {
		return numberOfHoursInYear(this->_Year);
	}
	
	static int numberOfMinutesInYear(short year) {
		return numberOfDaysInYear(year) * 24 * 60;
	}
	int numberOfMinutesInYear() {
		return numberOfMinutesInYear(this->_Year);
	}

	static int numberOfSecondsInYear(short year) {
		return numberOfDaysInYear(year) * 24 * 60 * 60;
	}
	int numberOfSecondsInYear() {
		return numberOfSecondsInYear(this->_Year);
	}

	static void numberOfDHMSinYear(short year) {
		cout << "\nNumber of Days in Year [" << year << "] is " << numberOfDaysInYear(year) << endl;
		cout << "Number of Hours in Year [" << year << "] is " << numberOfHoursInYear(year) << endl;
		cout << "Number of Minutes in Year [" << year << "] is " << numberOfMinutesInYear(year) << endl;
		cout << "Number of Seconds in Year [" << year << "] is " << numberOfSecondsInYear(year) << endl;
	}
	void numberOfDHMSinYear() {
		 numberOfDHMSinYear(this->_Year);
	}

	static short numberOfHoursInMonth(short year, short month) {
		return numberOfDaysInMonth(year, month) * 24;
	}
	short numberOfHoursInMonth() {
		return numberOfHoursInMonth(this->_Year, this->_Month);
	}
	
	static int numberOfMinutesInMonth(short year, short month) {
		return numberOfDaysInMonth(year, month) * 24 * 60;
	}
	int numberOfMinutesInMonth() {
		return numberOfMinutesInMonth(this->_Month, this->_Year);
	}

	static int numberOfSecondsInMonth(short year, short month) {
		return numberOfDaysInMonth(year, month) * 24 * 60 * 60;
	}
	int numberOfSecondsInMonth() {
		return numberOfSecondsInMonth(this->_Year, this->_Month);
	}

	static void numberOfDHMSInMonth(short year, short month) {
		cout << "\nNumber of Days in Month [" << month << "] is " << numberOfDaysInMonth(year, month) << endl;
		cout << "Number of Hours in Month [" << month << "] is " << numberOfHoursInMonth(year, month) << endl;
		cout << "Number of Minutes in Month [" << month << "] is " << numberOfMinutesInMonth(year, month) << endl;
		cout << "Number of Seconds in Month [" << month << "] is " << numberOfSecondsInMonth(year, month) << endl;
	}
	void numberOfDHMSInMonth() {
		 numberOfDHMSInMonth(this->_Year, this->_Month);
	}

	static void dateDetails(short year, short month, short day) {

		string days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		short dayOrder = dayOrderInWeek(year, month, day);

		cout << "\nDate		:" << day << "/" << month << "/" << year << endl;
		cout << "Day Order	:" << dayOrder << endl;
		cout << "Day Name	:" << days[dayOrder] << endl;
	}
	void dateDetails() {
		 dateDetails(this->_Year, this->_Month, this->_Day);
	}

	static short dayOrderInYear(short day, short month, short year) {

		short dayOrder = day;

		for (short i = 1; i < month; i++) {

			dayOrder += numberOfDaysInMonth(year, i);;
		}

		return dayOrder;
	}
	short dayOrderInYear() {
		return dayOrderInYear(this->_Day, this->_Month, this->_Year);
	}

	static clsDate increaseDateByXDay(short day, short month, short year, short days) {

		clsDate date;

		while (days > 0) {

			if (day < numberOfDaysInMonth(year, month)) {
				day++;
				days--;
			}

			else {
				day = 0;
				month++;

				if (month > 12) {
					month = 1;
					year++;
				}

			}
		}

		date._Day = day;
		date._Month = month;
		date._Year = year;

		return date;
	}
	void increaseDateByXDay(short days) {
		*this = increaseDateByXDay(this->_Day, this->_Month, this->_Year, days);
	}

	static clsDate readDate() {
		clsDate date;
		date._Day = myLibrary::readShortNumber("Enter a Day? ");
		date._Month = myLibrary::readShortNumber("Enter A month? ");
		date._Year = myLibrary::readShortNumber("Enter A year? ");
		return date;
	}

	static void compareTwoDates(clsDate date1, clsDate date2) {
		cout << "\nDate1 is: " << date1._Day << "/" << date1._Month << "/" << date1._Year << endl;
		cout << "\nDate2 is: " << date2._Day << "/" << date2._Month << "/" << date2._Year << endl;

		if (date1._Year < date2._Year) {
			cout << "Yes, Date1 is less than Date2." << endl;
		}
		else if (date1._Year > date2._Year) {
			cout << "Date1 is bigger than Date2." << endl;
		}
		else { // If years are equal
			if (date1._Month < date2._Month) {
				cout << "Yes, Date1 is less than Date2." << endl;
			}
			else if (date1._Month > date2._Month) {
				cout << "Date1 is bigger than Date2." << endl;
			}
			else { // If months are equal
				if (date1._Day < date2._Day) {
					cout << "Yes, Date1 is less than Date2." << endl;
				}
				else if (date1._Day > date2._Day) {
					cout << "Date1 is bigger than Date2." << endl;
				}
				else { // If days are equal
					cout << "Date1 is equal to Date2." << endl;
				}
			}
		}
	}
	void compareTwoDates( clsDate date2) {
		 compareTwoDates(*this, date2);
	}

	static bool isDate1BeforeDate2(clsDate date1, clsDate date2) {
		return (date1._Year < date2._Year) ? true :
			(date1._Year > date2._Year) ? false :
			(date1._Month < date2._Month) ? true :
			(date1._Month > date2._Month) ? false :
			(date1._Day < date2._Day);
	}
	bool isDate1BeforeDate2( clsDate date2) {
		return isDate1BeforeDate2(*this, date2);
	}

	static bool isDate1EqualToDate2(clsDate date1, clsDate date2) {
		return (date1._Year == date2._Year ? (date1._Month == date2._Month ? (date1._Day == date2._Day ? true : false) : false) : false);
	}
	bool isDate1EqualToDate2( clsDate date2) {
		return isDate1EqualToDate2(*this,  date2);
	}

	static clsDate increaseDateByOneWeek(clsDate date) {

		date = increaseDateByXDay(date._Day, date._Month, date._Year, 7);
		return date;

	}
	void increaseDateByOneWeek() {
		*this =  increaseDateByOneWeek(*this);
	}

	static clsDate increaseDateByXWeek(clsDate date, short numOfWeeks) {

		short days = numOfWeeks * 7;
		date = increaseDateByXDay(date._Day, date._Month, date._Year, days);
		return date;

	}
	void increaseDateByXWeek( short numOfWeeks) {
		*this =  increaseDateByXWeek(*this,  numOfWeeks);
	}

	static clsDate increaseDateByOneMonth(clsDate date) {

		date._Month++;

		if (date._Month > 12) {
			date._Year++;
			date._Month = date._Month - 12;
		}

		if (date._Day > numberOfDaysInMonth(date._Year, date._Month)) {
			date._Day = numberOfDaysInMonth(date._Year, date._Month);
		}

		return date;
	}
	void increaseDateByOneMonth() {
		*this = increaseDateByOneMonth(*this);
	}

	static clsDate increaseDateByXMonth(clsDate date, short numOfMonths) {


		for (short month = 1; month <= numOfMonths; month++) {
			date = increaseDateByOneMonth(date);
		}

		return date;
	}
	void increaseDateByXMonth( short numOfMonths) {
		*this = increaseDateByXMonth(*this, numOfMonths);
	}

	static clsDate increaseDateByOneYear(clsDate date) {

		date._Year++;
		return date;
	}
	void increaseDateByOneYear() {
		*this = increaseDateByOneYear(*this);
	}

	static clsDate increaseDateByXYear(clsDate date, short numOfYears) {

		date._Year += numOfYears;
		return date;

	}
	void increaseDateByXYear( short numOfYears) {
		*this= increaseDateByXYear(*this, numOfYears);
	}

	static clsDate increaseDateByOneDecade(clsDate date) {
		date._Year += 10;
		return date;
	}
	void increaseDateByOneDecade() {
		*this =  increaseDateByOneDecade(*this);
	}

	static clsDate increaseDateByXDecade(clsDate date, short numOfDecades) {
		date._Year += 10 * numOfDecades;
		return date;
	}
	void increaseDateByXDecade( short numOfDecades) {
		*this =  increaseDateByXDecade(*this, numOfDecades);
	}

	static clsDate increaseDateByOneCentury(clsDate date) {
		date._Year += 100;
		return date;
	}
	void increaseDateByOneCentury() {
		*this =  increaseDateByOneCentury(*this);
	}

	static clsDate increaseDateByOneMillennium(clsDate date) {
		date._Year += 1000;
		return date;
	}
	void increaseDateByOneMillennium() {
		*this = increaseDateByOneMillennium(*this);
	}

	static clsDate decreaseDateByOneDay(clsDate date) {

		if (date._Day == 1) {

			if (date._Month == 1) {

				date._Year--;
				date._Month = 12;
				date._Day = 31;
			}
			else {
				date._Month--;
				date._Day = numberOfDaysInMonth(date._Year, date._Month);
			}

		}
		else {
			date._Day--;
		}

		return date;

	}
	void decreaseDateByOneDay() {
		*this  = decreaseDateByOneDay(*this);
	}

	static clsDate decreaseDateByXDay(clsDate date, short numberOfDays) {

		for (short day = 1; day <= numberOfDays; day++) {

			date = decreaseDateByOneDay(date);

		}
		return date;
	}
	void decreaseDateByXDay(short numberOfDays) {
		*this = decreaseDateByXDay(*this, numberOfDays);
	}

	static clsDate decreaseDateByOneWeek(clsDate date) {

		for (short day = 1; day <= 7; day++) {

			date = decreaseDateByOneDay(date);

		}
		return date;

	}
	void decreaseDateByOneWeek() {
		*this =  decreaseDateByOneWeek(*this);
	}

	static clsDate decreaseDateByXWeek(clsDate date, short numberOfWeeks) {

		for (short week = 1; week <= numberOfWeeks * 7; week++) {

			date = decreaseDateByOneDay(date);

		}
		return date;

	}
	void decreaseDateByXWeek(short numberOfWeeks) {
		*this = decreaseDateByXWeek(*this, numberOfWeeks);
	}

	static clsDate decreaseDateByOneMonth(clsDate date) {

		date._Month--;

		if (date._Month < 1) {
			date._Year--;
			date._Month = 12;
		}

		if (date._Day > numberOfDaysInMonth(date._Year, date._Month)) {
			date._Day = numberOfDaysInMonth(date._Year, date._Month);
		}

		return date;

	}
	void decreaseDateByOneMonth() {
		*this = decreaseDateByOneMonth(*this);
	}

	static clsDate decreaseDateByXMonth(clsDate date, short numberOfMonths) {

		for (short month = 1; month <= numberOfMonths; month++) {
			date = decreaseDateByOneMonth(date);
		}
		return date;

	}
	void decreaseDateByXMonth(short numberOfMonths) {
		*this = decreaseDateByXMonth(*this, numberOfMonths);
	}

	static clsDate decreaseDateByXyear(clsDate date, short numberOfYears = 1) {
		date._Year -= numberOfYears;
		return date;
	}
	void decreaseDateByXyear(short numberOfYears = 1) {
		*this = decreaseDateByXyear(*this,  numberOfYears = 1);
	}

	static clsDate decreaseDateByXDecade(clsDate date, short numberOfDecades = 1) {
		date._Year -= (numberOfDecades * 10);
		return date;
	}
	void decreaseDateByXDecade(short numberOfDecades = 1) {
		*this = decreaseDateByXDecade(*this, numberOfDecades = 1);
	}

	static clsDate decreaseDateByOneCentury(clsDate date) {
		date._Year -= 100;
		return date;
	}
	void decreaseDateByOneCentury() {
		*this =  decreaseDateByOneCentury(*this);
	}

	static clsDate decreaseDateByOneMillennium(clsDate date) {
		date._Year -= 1000;
		return date;
	}
	void decreaseDateByOneMillennium() {
		*this =  decreaseDateByOneMillennium(*this);
	}

	static string dayName(clsDate date) {

		short dayOrder = dayOrderInWeek(date);
		string days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return days[dayOrder];

	}
	string dayName() {
		return dayName( *this);
	}

	static bool isItEndOfWeek(clsDate date) {
		// sat is the end of week
		return (dayOrderInWeek(date) == 6);
	}
	bool isItEndOfWeek() {
		return isItEndOfWeek(*this);
	}

	static bool isItWeekEnd(clsDate date) {
		short dayOrder = dayOrderInWeek(date);
		return (dayOrder == 6 || dayOrder == 5); // sat || fri

	}
	bool isItWeekEnd() {
		return isItWeekEnd(*this);
	}

	static bool isItBusinessDay(clsDate date) {
		return !isItWeekEnd(date);
	}
	bool isItBusinessDay() {
		return isItBusinessDay(*this);
	}

	static short daysUntilEndOfWeek(clsDate date) {
		return (6 - dayOrderInWeek(date));
	}
	short daysUntilEndOfWeek() {
		return daysUntilEndOfWeek(*this);
	}

	static short daysUntilEndOfMonth(clsDate date) {
		return (numberOfDaysInMonth(date._Year, date._Month) - date._Day);
	}
	short daysUntilEndOfMonth() {
		return daysUntilEndOfMonth(*this);
	}

	static short daysUntilEndOfYear(clsDate date) {
		return ( (365 - dayOrderInYear(date._Day, date._Month, date._Year) ) + isLeapYear(date._Year) );
	}
	short daysUntilEndOfYear() {
		return daysUntilEndOfYear(*this);
	}

	static short actualVacationDays(clsDate vacationStart, clsDate vacationEnd) {

		short actuallVacationDays = 0;

		while (isDate1BeforeDate2(vacationStart, vacationEnd)) {

			if (isItBusinessDay(vacationStart)) {
				actuallVacationDays++;
			}
			vacationStart = increaseDateByOneDay(vacationStart);
		}

		return actuallVacationDays;
	}

	static short actuallBusinessDays(clsDate startDate, clsDate endDate) {
		return actualVacationDays(startDate, endDate);
	}

	static clsDate vacationRetrunDate(clsDate vacationStart, short vacationDays) {

		clsDate vacationEnd = vacationStart;


		while (vacationDays > 0) {

			if (isItBusinessDay(vacationEnd)) {
				vacationDays--;
			}
			vacationEnd = increaseDateByOneDay(vacationEnd);
		}

		return vacationEnd;
	}

	static bool isDate1AfterDate2(clsDate date1, clsDate date2) {

		return (!isDate1BeforeDate2(date1, date2) && !isDate1EqualToDate2(date1, date2));
	}
	bool isDate1AfterDate2(clsDate date2) {
		return isDate1AfterDate2(*this, date2);
	}

	enum enDateCompare {
		before = -1,
		equal = 0,
		after = 1
	};
	static enDateCompare compareDates(clsDate date1, clsDate date2) {

		if (isDate1BeforeDate2(date1, date2)) {
			return enDateCompare::before;
		}
		else if (isDate1EqualToDate2(date1, date2)) {
			return enDateCompare::equal;
		}

		return enDateCompare::after;

	}
	enDateCompare compareDates( clsDate date2) {
		return compareDates(*this, date2);
	}

	static string readStringDate() {
		string date;
		cout << "inter a date (dd/mm/yyyy)? ";
		getline(cin >> ws, date);
		return date;
	}

	static string formatDate(clsDate dateStruct, string format = "dd/mm/yyyy") {

		string formatedDate = "";
		formatedDate = stringLib::replaceWordsUsingRepalceFunc(format, "dd", to_string(dateStruct._Day));
		formatedDate = stringLib::replaceWordsUsingRepalceFunc(formatedDate, "mm", to_string(dateStruct._Month));
		formatedDate = stringLib::replaceWordsUsingRepalceFunc(formatedDate, "yyyy", to_string(dateStruct._Year));

		return formatedDate;

	}
	string formatDate(string format = "dd/mm/yyyy") {
		return formatDate(*this, format = "dd/mm/yyyy");
	}

	static clsDate smallDate(clsDate date1, clsDate date2) {

		return ((compareDates(date1, date2) <= 0) ? date1 : date2);
	}
	clsDate smallDate(clsDate date2) {
		return smallDate(*this, date2);
	}

	static clsDate bigDate(clsDate date1, clsDate date2) {
		return ((compareDates(date1, date2) >= 0) ? date1 : date2);
	}
	clsDate bigDate(clsDate date2) {
		return bigDate(*this, date2);
	}



};

