#pragma once


#include <iostream>
#include "myLibrary.h"
#include "stringLib.h"

namespace dateLib {


	//  moved to clsDate
	bool isLeapYear(short year) {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	//  moved to clsDate
	short numberOfDaysInYear(short year) {
		return isLeapYear(year) ? 366 : 365;
	}


	//  moved to clsDate
	short numberOfHoursInYear(short year) {
		return numberOfDaysInYear(year) * 24;
	}

	//  moved to clsDate
	int numberOfMinutesInYear(short year) {
		return numberOfDaysInYear(year) * 24 * 60;
	}


	//  moved to clsDate
	int numberOfSecondsInYear(short year) {
		return numberOfDaysInYear(year) * 24 * 60 * 60;
	}

	//  moved to clsDate
	void numberOfDHMSinYear(short year) {
		cout << "\nNumber of Days in Year [" << year << "] is " << numberOfDaysInYear(year) << endl;
		cout << "Number of Hours in Year [" << year << "] is " << numberOfHoursInYear(year) << endl;
		cout << "Number of Minutes in Year [" << year << "] is " << numberOfMinutesInYear(year) << endl;
		cout << "Number of Seconds in Year [" << year << "] is " << numberOfSecondsInYear(year) << endl;
	}


	// moved to clsDate
	short numberOfDaysInMonth(short year, short month) {
		if (month < 1 || month > 12)
			return 0;
		int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (month == 2) ? (isLeapYear(year) + 28) : daysInMonth[month - 1];

	}

	// moved to clsDate
	short numberOfHoursInMonth(short year, short month) {
		return numberOfDaysInMonth(year, month) * 24;
	}

	// moved to clsDate
	int numberOfMinutesInMonth(short year, short month) {
		return numberOfDaysInMonth(year, month) * 24 * 60;
	}

	// moved to clsDate
	int numberOfSecondsInMonth(short year, short month) {
		return numberOfDaysInMonth(year, month) * 24 * 60 * 60;
	}

	// moved to clsDate
	void numberOfDHMSInMonth(short year, short month) {
		cout << "\nNumber of Days in Month [" << month << "] is " << numberOfDaysInMonth(year, month) << endl;
		cout << "Number of Hours in Month [" << month << "] is " << numberOfHoursInMonth(year, month) << endl;
		cout << "Number of Minutes in Month [" << month << "] is " << numberOfMinutesInMonth(year, month) << endl;
		cout << "Number of Seconds in Month [" << month << "] is " << numberOfSecondsInMonth(year, month) << endl;
	}

	// moved to clsDate
	short dayOrderInWeek(short year, short month, short day) {
		// equation name Zeller's congruence;
		// 0 to 6 (sunday to saturday)
		short a = ((14 - month) / 12);
		short y = year - a;
		short m = month + (12 * a) - 2;

		short dayOrder = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return dayOrder;
	}

	// moved to clsDate
	void dateDetails(short year, short month, short day) {

		string days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		short dayOrder = dayOrderInWeek(year, month, day);

		cout << "\nDate		:" << day << "/" << month << "/" << year << endl;
		cout << "Day Order	:" << dayOrder << endl;
		cout << "Day Name	:" << days[dayOrder] << endl;
	}

	// moved to clsDate
	string monthName(short monthNumber) {
		string months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return months[monthNumber - 1];
	}

	// moved to clsDate
	void monthCalander(short year, short month) {

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

	// moved to clsDate
	void yearClander(short year) {

		cout << endl << std::string(40, '_') << endl;
		printf("\n	Calander - %d\n", year);
		cout << endl << std::string(40, '_') << endl;

		for (short month = 1; month <= 12; month++) {
			monthCalander(year, month);
		}
	}

	// moved to clsDate
	short dayOrderInYear(short day, short month, short year) {

		short dayOrder = day;

		for (short i = 1; i < month; i++) {

			dayOrder += numberOfDaysInMonth(year, i);;
		}

		return dayOrder;
	}

	struct stDate {
		short year;
		short month;
		short day;
	};


	// moved to clsDate
	stDate dateFromDayOrder(short dayOrder, short year) {

		stDate date;
		date.month = 1;
		date.year = year;
		short remainingDays = dayOrder;

		for (short i = 1; i <= 12; i++) {

			remainingDays = remainingDays - numberOfDaysInMonth(year, i);

			if (remainingDays <= 0) {

				date.day = remainingDays + numberOfDaysInMonth(year, i);
				break;

			}
			else {
				date.month++;
			}
		}
		return date;
	}


	// moved to clsDate
	stDate increaseDateByXDay(short day, short month, short year, short days) {

		stDate date;

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

		date.day = day;
		date.month = month;
		date.year = year;

		return date;
	}

	// moved to clsDate
	stDate readDate() {
		stDate date;
		date.day = myLibrary::readNumber("Enter A day? ");
		date.month = myLibrary::readNumber("Enter A month? ");
		date.year = myLibrary::readNumber("Enter A year? ");
		return date;
	}


	// moved to clsDate
	 void compareTwoDates(stDate date1, stDate date2) {
		cout << "\nDate1 is: " << date1.day << "/" << date1.month << "/" << date1.year << endl;
		cout << "\nDate2 is: " << date2.day << "/" << date2.month << "/" << date2.year << endl;

		if (date1.year < date2.year) {
			cout << "Yes, Date1 is less than Date2." << endl;
		}
		else if (date1.year > date2.year) {
			cout << "Date1 is bigger than Date2." << endl;
		}
		else { // If years are equal
			if (date1.month < date2.month) {
				cout << "Yes, Date1 is less than Date2." << endl;
			}
			else if (date1.month > date2.month) {
				cout << "Date1 is bigger than Date2." << endl;
			}
			else { // If months are equal
				if (date1.day < date2.day) {
					cout << "Yes, Date1 is less than Date2." << endl;
				}
				else if (date1.day > date2.day) {
					cout << "Date1 is bigger than Date2." << endl;
				}
				else { // If days are equal
					cout << "Date1 is equal to Date2." << endl;
				}
			}
		}
	}

	// moved to clsDate
	bool istDate1BeforeDate2(stDate date1, stDate date2) {
		return (date1.year < date2.year) ? true :
			(date1.year > date2.year) ? false :
			(date1.month < date2.month) ? true :
			(date1.month > date2.month) ? false :
			(date1.day < date2.day);
	}

	// moved to clsDate
	bool istDate1EqualToDate2(stDate date1, stDate date2) {
		return (date1.year == date2.year ? (date1.month == date2.month ? (date1.day == date2.day ? true : false) : false) : false);
	}

	// moved to clsDate
	bool isItLastDayInMonth(stDate date) {
		return (date.day == numberOfDaysInMonth(date.year, date.month));
	}


	// moved to clsDate
	bool isItLastMonthInYear(short month) {
		return (month == 12);
	}

	// moved to clsDate
	stDate increaseDateByOneDay(stDate date) {

		if (isItLastDayInMonth(date)) {

			if (isItLastMonthInYear(date.month)) {

				date.year++;
				date.month = 1;
				date.day = 1;
			}
			else {
				date.day = 1;
				date.month++;
			}

		}
		else {
			date.day++;
		}

		return date;

	}

	// moved to clsDate
	void swapDates(stDate& date1, stDate& date2) {
		stDate tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}

	// moved to clsDate
	short differenceBetweenDates(stDate date1, stDate date2, bool includeEndDay = false) {

		short days = 0;
		short swapFlag = 1;


		if (!istDate1BeforeDate2(date1, date2)) {
			swapDates(date1, date2);
			swapFlag = -1;
		}

		while (istDate1BeforeDate2(date1, date2)) {
			days++;
			date1 = increaseDateByOneDay(date1);
		}



		return (includeEndDay ? ++days * swapFlag : days * swapFlag);

	}



	// moved to clsDate
	stDate getSystemDate() {

		stDate systemDate;

		time_t timeNow = time(0); // get time now sice 1 jan 1970 in ms.
		tm* now = localtime(&timeNow);

		systemDate.year = now->tm_year + 1900;
		systemDate.month = now->tm_mon + 1;
		systemDate.day = now->tm_mday;

		return systemDate;


	}

	// moved to clsDate
	int ageInDays(stDate dateOfBirth, stDate systemDate) { // 6/11/1977


		int numOfDays = differenceBetweenDates(dateOfBirth, systemDate);

		return numOfDays;

	}


	// moved to clsDate
	stDate increaseDateByOneWeek(stDate date) {

		date = increaseDateByXDay(date.day, date.month, date.year, 7);
		return date;

	}

	// moved to clsDate
	stDate increaseDateByXWeek(stDate date) {

		short days = myLibrary::readNumber("numberOfWeeks? ") * 7;
		date = increaseDateByXDay(date.day, date.month, date.year, days);
		return date;

	}

	// moved to clsDate
	stDate increaseDateByOneMonth(stDate date) {

		date.month++;

		if (date.month > 12) {
			date.year++;
			date.month = date.month - 12;
		}

		if (date.day > numberOfDaysInMonth(date.year, date.month)) {
			date.day = numberOfDaysInMonth(date.year, date.month);
		}

		return date;
	}

	// moved to clsDate
	stDate increaseDateByXMonth(stDate date) {

		short months = myLibrary::readNumber("number of months? ");

		for (short month = 1; month <= months; month++) {
			date = increaseDateByOneMonth(date);
		}

		return date;
	}

	// moved to clsDate
	stDate increaseDateByOneYear(stDate date) {

		date.year++;
		return date;
	}

	// moved to clsDate
	stDate increaseDateByXYear(stDate date) {

		date.year += myLibrary::readNumber("How many years? ");
		return date;

	}

	// moved to clsDate
	stDate increaseDateByOneDecade(stDate date) {
		date.year += 10;
		return date;
	}

	// moved to clsDate
	stDate increaseDateByXDecade(stDate date) {

		date.year += 10 * myLibrary::readNumber("how many decades? ");
		return date;

	}

	// moved to clsDate
	stDate increaseDateByOneCentury(stDate date) {

		date.year += 100;
		return date;
	}

	// moved to clsDate
	stDate increaseDateByOneMillennium(stDate date) {

		date.year += 1000;
		return date;
	}

	// moved to clsDate
	stDate decreaseDateByOneDay(stDate date) {

		if (date.day == 1) {

			if (date.month == 1) {

				date.year--;
				date.month = 12;
				date.day = 31;
			}
			else {
				date.month--;
				date.day = numberOfDaysInMonth(date.year, date.month);
			}

		}
		else {
			date.day--;
		}

		return date;

	}

	// moved to clsDate
	stDate decreaseDateByXDay(stDate date, short numberOfDays) {

		for (short day = 1; day <= numberOfDays; day++) {

			date = decreaseDateByOneDay(date);

		}
		return date;
	}

	// moved to clsDate
	stDate decreaseDateByOneWeek(stDate date) {

		for (short day = 1; day <= 7; day++) {

			date = decreaseDateByOneDay(date);

		}
		return date;

	}

	// moved to clsDate
	stDate decreaseDateByXWeek(stDate date, short numberOfWeeks) {

		for (short week = 1; week <= numberOfWeeks * 7; week++) {

			date = decreaseDateByOneDay(date);

		}
		return date;

	}

	// moved to clsDate
	stDate decreaseDateByOneMonth(stDate date) {

		date.month--;

		if (date.month < 1) {
			date.year--;
			date.month = 12;
		}

		if (date.day > numberOfDaysInMonth(date.year, date.month)) {
			date.day = numberOfDaysInMonth(date.year, date.month);
		}

		return date;

	}

	// moved to clsDate
	stDate decreaseDateByXMonth(stDate date, short numberOfMonths) {

		for (short month = 1; month <= numberOfMonths; month++) {
			date = decreaseDateByOneMonth(date);
		}
		return date;

	}

	// moved to clsDate
	stDate decreaseDateByXyear(stDate date, short numberOfYears = 1) {
		date.year -= numberOfYears;
		return date;
	}

	// moved to clsDate
	stDate decreaseDateByXDecade(stDate date, short numberOfDecades = 1) {
		date.year -= (numberOfDecades * 10);
		return date;
	}

	// moved to clsDate
	stDate decreaseDateByOneCentury(stDate date) {
		date.year -= 100;
		return date;
	}

	// moved to clsDate
	stDate decreaseDateByOneMillennium(stDate date) {
		date.year -= 1000;
		return date;
	}

	// moved to clsDate
	short dayOrderInWeek(stDate date) {
		// 0 to 6 (sunday to saturday)
		return dayOrderInWeek(date.year, date.month, date.day);
	}

	// moved to clsDate
	string dayName(stDate date) {

		short dayOrder = dayOrderInWeek(date);
		string days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return days[dayOrder];

	}

	// moved to clsDate
	bool isItEndOfWeek(stDate date) {
		// sat
		return (dayOrderInWeek(date) == 6);

	}

	// moved to clsDate
	bool isItWeekEnd(stDate date) {
		short dayOrder = dayOrderInWeek(date);
		return (dayOrder == 6 || dayOrder == 5); // sat || fri

	}

	// moved to clsDate
	bool isItBusinessDay(stDate date) {
		return !isItWeekEnd(date);
	}

	// moved to clsDate
	short daysUntilEndOfWeek(stDate date) {
		return (6 - dayOrderInWeek(date));
	}

	// moved to clsDate
	short daysUntilEndOfMonth(stDate date) {
		return (numberOfDaysInMonth(date.year, date.month) - date.day);
	}

	// moved to clsDate
	short daysUntilEndOfYear(stDate date) {
		return ((365 - dayOrderInYear(date.day, date.month, date.year)) + isLeapYear(date.year));
	}

	// moved to clsDate
	short actualVacationDays(stDate vacationStart, stDate vacationEnd) {

		short actuallVacationDays = 0;

		while (istDate1BeforeDate2(vacationStart, vacationEnd)) {

			if (isItBusinessDay(vacationStart)) {
				actuallVacationDays++;
			}
			vacationStart = increaseDateByOneDay(vacationStart);
		}

		return actuallVacationDays;
	}

	// moved to clsDate
	stDate vacationRetrunDate(stDate vacationStart, short vacationDays) {

		stDate vacationEnd = vacationStart;


		while (vacationDays > 0) {

			if (isItBusinessDay(vacationEnd)) {
				vacationDays--;
			}
			vacationEnd = increaseDateByOneDay(vacationEnd);
		}

		return vacationEnd;
	}

	// moved to clsDate
	bool istDate1AfterDate2(stDate date1, stDate date2) {

		return (!istDate1BeforeDate2(date1, date2) && !istDate1EqualToDate2(date1, date2));
	}

	// moved to clsDate
	enum enDateCompare {
		before = -1,
		equal = 0,
		after = 1
	};

	// moved to clsDate
	enDateCompare compareDates(stDate date1, stDate date2) {

		if (istDate1BeforeDate2(date1, date2)) {
			return enDateCompare::before;
		}
		else if (istDate1EqualToDate2(date1, date2)) {
			return enDateCompare::equal;
		}

		return enDateCompare::after;

	}

	// moved to clsDate
	struct stPeriod {
		stDate startDate;
		stDate endDate;
	};

	// moved to clsDate
	stPeriod readPeriod() {

		stPeriod period;

		cout << "enter start date: " << endl;
		period.startDate = readDate();

		cout << "\nenter end date:" << endl;
		period.endDate = readDate();

		return period;
	}

	// moved to clsDate
	bool isPeriodsOverlap(stPeriod period1, stPeriod period2) {

		if ((compareDates(period1.startDate, period2.endDate) == enDateCompare::after)
			|| (compareDates(period1.endDate, period2.startDate) == enDateCompare::before)
			) {
			return false;
		}

		return true;

	}

	// moved to clsDate
	short periodLenghtInDays(stPeriod period, bool includeEndDay = false) {

		return differenceBetweenDates(period.startDate, period.endDate, includeEndDay);

	}

	// moved to clsDate
	bool istDateWithinPeriod(stDate date, stPeriod period) {

		return (compareDates(date, period.startDate) >= 0 && compareDates(date, period.endDate) <= 0);

	}

	// moved to clsDate
	stDate smallDate(stDate date1, stDate date2) {

		return ((compareDates(date1, date2) <= 0) ? date1 : date2);
	}

	// moved to clsDate
	stDate bigDate(stDate date1, stDate date2) {

		return ((compareDates(date1, date2) >= 0) ? date1 : date2);

	}

	// moved to clsDate
	short overlapDaysWithinTwoPeriod(stPeriod period1, stPeriod period2) {

		short overlapDays = 0;

		if (!isPeriodsOverlap(period1, period2)) {
			return overlapDays;
		}

		stDate bigStartDate = bigDate(period1.startDate, period2.startDate);
		stDate smallEndDate = smallDate(period1.endDate, period2.endDate);

		return differenceBetweenDates(bigStartDate, smallEndDate);

	}

	// moved to clsDate
	stPeriod overlapPeriod(stPeriod period1, stPeriod period2) {

		stPeriod overlapPeriod;
		overlapPeriod.startDate.day = 0;
		overlapPeriod.startDate.month = 0;
		overlapPeriod.startDate.year = 0;
		overlapPeriod.endDate = overlapPeriod.startDate;


		if (!isPeriodsOverlap(period1, period2)) {
			return overlapPeriod;
		}

		stDate bigStartDate = bigDate(period1.startDate, period2.startDate);
		stDate smallEndDate = smallDate(period1.endDate, period2.endDate);

		overlapPeriod.startDate = bigStartDate;
		overlapPeriod.endDate = smallEndDate;

		return overlapPeriod;

	}

	// moved to clsDate
	bool isValidDate(stDate date) {

		return (date.month >= 1 && date.month <= 12) && (date.day >= 1 && date.day <= numberOfDaysInMonth(date.year, date.month));

	}

	// moved to clsDate
	string readStringDate() {
		string date;
		cout << "inter a date (dd/mm/yyyy)? ";
		getline(cin >> ws, date);
		return date;
	}
	// moved to clsDate
	stDate stringToDate(string dateString) {

		vector <string> vDate = stringLib::splitEachWordOfStringInToVector(dateString, "/");

		stDate dateStruct;
		dateStruct.day = stoi(vDate[0]);
		dateStruct.month = stoi(vDate[1]);
		dateStruct.year = stoi(vDate[2]);

		return dateStruct;

	}

	// moved to clsDate
	string dateToString(stDate dateStruct) {

		return (to_string(dateStruct.day) + "/" + to_string(dateStruct.month) + "/" + to_string(dateStruct.year));
	}

	// moved to clsDate
	string formatDate(stDate dateStruct, string format = "dd/mm/yyyy") {

		string formatedDate = "";
		formatedDate = stringLib::replaceWordsUsingRepalceFunc(format, "dd", to_string(dateStruct.day));
		formatedDate = stringLib::replaceWordsUsingRepalceFunc(formatedDate, "mm", to_string(dateStruct.month));
		formatedDate = stringLib::replaceWordsUsingRepalceFunc(formatedDate, "yyyy", to_string(dateStruct.year));

		return formatedDate;

	}

}