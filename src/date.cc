
/**************************************************************************
 * Copyright (C) 2007-2008 Ruben Pollan Bella <meskio@amedias.org>        *
 *                                                                        *
 *  This file is part of TuDu.                                            *
 *                                                                        *
 *  TuDu is free software; you can redistribute it and/or modify          *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation; either version 3 of the License.        *
 *                                                                        *
 *  TuDu is distributed in the hope that it will be useful,               *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 **************************************************************************/

#include "date.h"

Date::Date(int day, int month, int year): _day(day), _month(month), _year(year) {}

int& Date::day(int d)
{
	if (d) _day = d;
	return _day;
}

int& Date::month(int m)
{
	if (m) _month = m;
	return _month;
}

int& Date::year(int y)
{
	if (y) _year = y;
	return _year;
}

bool Date::valid()
{
	return (1900 != _year);
}

bool Date::correct()
{
	bool correct;

	switch (_month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if ((_day < 1) || (_day > 31))
				correct = false;
			else
				correct = true;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if ((_day < 1) || (_day > 30))
				correct = false;
			else
				correct = true;
			break;
		case 2:
			/* if leap year */
			if ((_year % 4 == 0) && !((_year % 100 == 0) && (_year % 1000 != 0)))
			{
				if ((_day < 1) || (_day > 29))
					correct = false;
				else
					correct = true;
			}
			else
			{
				if ((_day < 1) || (_day > 28))
					correct = false;
				else
					correct = true;
			}
			break;
		default:
			correct = false;
			break;
	}
	return correct;
}

#define SECONDS_IN_A_DAY (60*60*24)
int Date::daysLeft()
{
	time_t rawtime;
	time_t today;
	struct tm * timeinfo;
	int daysleft;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_mday = _day;
	timeinfo->tm_mon = _month - 1;
	timeinfo->tm_year = _year - 1900;
	rawtime = mktime(timeinfo);
	today = time(NULL);
	daysleft = difftime(rawtime,today)/SECONDS_IN_A_DAY;
	return daysleft;
}

Date Date::operator-(int days)
{
	Date d(_day, _month, _year);

	d._day -= days;
	while (d._day <= 0)
	{
		d._month--;
		if (d._month == 0)
		{
			d._month = 12;
			d._year--;
		}

		switch (d._month)
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				d._day += 31;
			case 4:
			case 6:
			case 9:
			case 11:
				d._day += 30;
			case 2:
				/* if leap year */
				if ((d._year % 4 == 0) && !((d._year % 100 == 0) && (d._year % 1000 != 0)))
				{
					d._day += 29;
				}
				else
				{
					d._day += 28;
				}
				break;
		}
	}

	return d;
}

bool Date::operator<(Date d)
{
	if (d._year < _year)
		return false;
	else if (d._year > _year)
		return true;
	else if (d._month < _month)
		return false;
	else if (d._month > _month)
		return true;
	else if (d._day < _day)
		return false;
	else
		return true;
}

bool Date::operator>(Date d)
{
	if (d._year > _year)
		return true;
	else if (d._year < _year)
		return false;
	else if (d._month > _month)
		return true;
	else if (d._month < _month)
		return false;
	else if (d._day > _day)
		return true;
	else
		return false;
}

bool Date::operator!=(Date d)
{
	if (d._year !=  _year)
		return true;
	else if (d._month !=  _month)
		return true;
	else if (d._day != _day)
		return true;
	else
		return false;
}
