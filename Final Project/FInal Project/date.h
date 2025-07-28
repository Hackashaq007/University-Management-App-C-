#include <iostream>
using namespace std;

class date {
	//function to set the number of days per month
	friend int set_days(int);

	//function to compare 2 dates (newest and oldest)
	friend int date_comp(date*, date*);
	friend istream& operator>>(istream&, date&);
	friend ostream& operator<<(ostream&, const date&);
private:
	int day, month, year;
public:
	date(int zero = 0) : day(zero), month(zero), year(zero) {}
};

int set_days(int month) {
	int days = 0;
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		days = 31;
		break;
	case 4: case 6: case 11: case 9:
		days = 30;
		break;
	case 2:
		days = 28;
		break;
	}
	return days;
}

int date_comp(date* d1, date* d2) {
	if (d1->year > d2->year)
		return 1;
	else
		if (d1->year < d2->year)
			return -1;
		else
			if (d1->month > d2->month)
				return 1;
			else
				if (d1->month < d2->month)
					return -1;
				else
					if (d1->day > d2->day)
						return 1;
					else
						if (d1->day < d2->day)
							return -1;
						else
							return 0;
}

istream& operator>>(istream& in, date& d) {
	int days;
	cout << "Month(1-12): "; in >> d.month;
	while (in.fail() || d.month < 1 || d.month >12) {
		in.clear(); in.ignore(INT_MAX, '\n');
		cout << "Month(1-12): "; in >> d.month;
	}
	days = set_days(d.month);
	cout << "Day(1-" << days << "): "; in >> d.day;
	while (in.fail() || d.day < 1 || d.day > days) {
		in.clear(); in.ignore(INT_MAX, '\n');
		cout << "Day(1-" << days << "): "; in >> d.day;
	}
	cout << "Year(1950-present): "; in >> d.year;
	while (in.fail() || d.year < 1950 || d.year > 2023) {
		in.clear(); in.ignore(INT_MAX, '\n');
		cout << "Year(1950-present): "; in >> d.year;
	}
	return in;
}

ostream& operator<<(ostream& out, const date& d) {
	out << (d.day < 10 ? "0" : "") << d.day << "/" << (d.month < 10 ? "0" : "") << d.month << "/" << d.year << "\n";
	return out;
}