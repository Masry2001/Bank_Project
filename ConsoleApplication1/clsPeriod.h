#pragma once
#include <iostream>;
#include "clsDate.h";

using namespace std;

class clsPeriod
{
public:

    clsDate startDate;
    clsDate endDate;

    clsPeriod()
    {
        startDate.decreaseDateByOneMonth();
        //notice that clsDate contructor will put system date in start date and end date
    }

    clsPeriod(clsDate startDate, clsDate endDate)
    {
        this->startDate = startDate;
        this->endDate = endDate;
        
    }



    static bool IsOverlapPeriods(clsPeriod period1, clsPeriod period2)
    {

        if (
            clsDate::compareDates(period2.endDate, period1.startDate) == clsDate::enDateCompare::before
            ||
            clsDate::compareDates(period2.startDate, period1.endDate) == clsDate::enDateCompare::after
            )
            return false;
        else
            return true;

    }


    bool IsOverLapWith(clsPeriod period2)
    {
        return IsOverlapPeriods(*this, period2);
    }

    void Print()
    {
        cout << "Period Start: ";
        startDate.print();


        cout << "Period End: ";
        endDate.print();


    }

	
	static clsPeriod readPeriod() {

		clsPeriod period;

		cout << "enter start date: " << endl;
		period.startDate = clsDate::readDate();

		cout << "\nenter end date:" << endl;
		period.endDate = clsDate::readDate();

		return period;
	}



	static short periodLenghtInDays(clsPeriod period, bool includeEndDay = false) {

		return clsDate::differenceBetweenDates(period.startDate, period.endDate, includeEndDay);

	}

	static bool isDateWithinPeriod(clsDate date, clsPeriod period) {
		return (clsDate::compareDates(date, period.startDate) >= 0 && clsDate::compareDates(date, period.endDate) <= 0);
	}


	static short overlapDaysWithinTwoPeriod(clsPeriod period1, clsPeriod period2) {

		short overlapDays = 0;

		if (!IsOverlapPeriods(period1, period2)) {
			return overlapDays;
		}

		clsDate bigStartDate = clsDate::bigDate(period1.startDate, period2.startDate);
		clsDate smallEndDate = clsDate::smallDate(period1.endDate, period2.endDate);

		return clsDate::differenceBetweenDates(bigStartDate, smallEndDate);

	}

	static clsPeriod overlapPeriod(clsPeriod period1, clsPeriod period2) {

		clsPeriod overlapPeriod;

		if (!IsOverlapPeriods(period1, period2)) {
			return overlapPeriod;
		}

		clsDate bigStartDate = clsDate::bigDate(period1.startDate, period2.startDate);
		clsDate smallEndDate = clsDate::smallDate(period1.endDate, period2.endDate);

		overlapPeriod.startDate = bigStartDate;
		overlapPeriod.endDate = smallEndDate;

		return overlapPeriod;

	}

};
