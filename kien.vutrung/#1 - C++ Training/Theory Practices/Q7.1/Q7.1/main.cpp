#include <iostream>
#include <stdio.h>
#include <Windows.h>
using namespace std;

struct Date
{
	unsigned char cDayOfWeek;
	unsigned char cDay;
	unsigned char cMonth;
	unsigned int iYear;

	Date();
	Date(unsigned char dow, unsigned char day, unsigned char month, unsigned int year);
	~Date();
	void GetLocalDate();
	unsigned char DayOfWeek(unsigned char day, unsigned char month, unsigned int year);
	bool CheckValidDate(unsigned char dow, unsigned char day, unsigned char month, unsigned int year);
	void Print(const char * format);
};

int main()
{
	Date date1;
	Date date2(2, 3, 4, 5);
	date1.Print("dow, dd-mm-yyyy");
	date2.Print("dow dd.mm.yy");
	system("pause");
	return 0;
}

Date::Date()
{
	GetLocalDate();
}

Date::Date(unsigned char dow, unsigned char day, unsigned char month, unsigned int year)
{
	if (CheckValidDate(dow, day, month, year))
	{
		cDayOfWeek = dow;
		cDay = day;
		cMonth = month;
		iYear = year;
	}
	else
	{
		printf("Invalid date, initialize with current date instead.\n");
		GetLocalDate();
	}
}

Date::~Date()
{
	printf("Date has been destroyed.");
}

void Date::GetLocalDate()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	cDay = time.wDay;
	cDayOfWeek = time.wDayOfWeek;
	cMonth = time.wMonth;
	iYear = time.wYear;
}

unsigned char Date::DayOfWeek(unsigned char day, unsigned char month, unsigned int year)
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	year -= month < 3;
	return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

bool Date::CheckValidDate(unsigned char dow, unsigned char day, unsigned char month, unsigned int year)
{
	int iDayInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	bool yearOk = (year >= 1);
	if (yearOk)
	{
		bool monthOk = (month >= 1) && (month <= 12);
		if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
		{
			iDayInMonth[1] = 29;
		}
		if (monthOk) 
		{
			bool dayOk = (day >= 1) && (day <= iDayInMonth[month - 1]);
			if (dayOk)
			{
				return dow == DayOfWeek(day, month, year);
			}
		}
	}
	return false;
}

void Date::Print(const char * format)
{
	const char* dayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	if (!strcmp(format, "dow, dd-mm-yyyy"))
	{
		printf("%s, %02d-%02d-%04d\n", dayNames[cDayOfWeek], cDay, cMonth, iYear);
	}
	else if (!strcmp(format, "dd/mm/yyyy"))
	{
		printf("%02d/%02d/%04d\n", cDay, cMonth, iYear);
	}
	else if (!strcmp(format, "mm-dd-yyyy"))
	{
		printf("%02d-%02d-%04d\n", cDay, cMonth, iYear);
	}
	else if (!strcmp(format, "dow dd.mm.yy"))
	{
		printf("%s, %02d.%02d.%02d\n", dayNames[cDayOfWeek], cDay, cMonth, iYear);
	}
	else {
		printf("Format is not supported.\n");
	}
}
