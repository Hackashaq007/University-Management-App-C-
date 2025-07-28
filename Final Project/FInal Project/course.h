#include "time_.h"
#include <iomanip>

class course {
	//function to set a courses end time depending on number of credits
	friend void set_end_time(course*);

	//alternate printing mode for course objects (used for testing)
	friend void alternate_print_course(course*);

	//function udes to check for time comflicts between two courses 
	friend bool period_comp(course*, course, int, int&);

	//function to compare two course periods (newest and oldest)
	friend int time_comp(course*, course*);

	//function to compare a course's end and another's starting period
	friend int end_comp(course*, course*);
	friend istream& operator>>(istream&, course&);
	friend ostream& operator<<(ostream&, course&);
private:
	char code[7], days[4];
	time_ period, ends;
	int credits;
public:
	course() { strcpy_s(code, sizeof(code), "N/A"); strcpy_s(days, sizeof(days), "N/A"); credits = 0; }
	//getter returning course code
	char* get_code() {
		return code;
	}
	//getter returning course days
	char* get_days() {
		return days;
	}
	//getter returning the number of credits of a course
	int get_credits() {
		return credits;
	}
};

istream& operator>>(istream& in, course& crs) {
	cout << "Course code: ";
	in >> crs.code;
	cout << "Course period: ";
	in >> crs.period;
	do {
		cout << "Course days(MW/TTH/F): ";
		in >> crs.days;
	} while (strcmp(crs.days, "MW") != 0 && strcmp(crs.days, "TTH") != 0 && strcmp(crs.days, "F"));

	do {
		cout << "Course credits: ";
		in >> crs.credits;
	} while (crs.credits < 1 || crs.credits > 3);
	return in;
}

void set_end_time(course* crs) {
	switch (crs->credits) {
	case 1:
		crs->ends.set_hours((crs->period.get_hours() + 3));
		crs->ends.set_minutes(crs->period.get_minutes());
		break;
	case 2: case 3:
		if (crs->period.get_minutes() < 30) {
			crs->ends.set_hours((crs->period.get_hours() + 1));
			crs->ends.set_minutes((crs->period.get_minutes() + 30));
		}
		else {
			crs->ends.set_hours((crs->period.get_hours() + 2));
			crs->ends.set_minutes((crs->period.get_minutes() - 30));
		}
		break;
	}
}

ostream& operator<<(ostream& out, course& crs) {
	out << left << crs.period;
	if (strcmp(crs.days, "MW") == 0) {
		out << "\t" << setw(30) << crs.code << crs.code << endl;
	}
	if (strcmp(crs.days, "TTH") == 0) {
		out << "\t\t\t" << setw(30) << crs.code << crs.code << endl;
	}
	if (strcmp(crs.days, "F") == 0) {
		out << setw(61) << "\t" << crs.code << endl;
	}
	return out;
}

int time_comp(course* t1, course* t2) {
	if (t1->period.get_hours() > t2->period.get_hours())
		return 1;
	else
		if (t1->period.get_hours() < t2->period.get_hours())
			return -1;
		else
			if (t1->period.get_minutes() > t2->period.get_minutes())
				return 1;
			else
				if (t1->period.get_minutes() < t2->period.get_minutes())
					return -1;
				else
					return 0;
}

int end_comp(course* t1, course* t2) {
	if (t1->period.get_hours() > t2->ends.get_hours())
		return 1;
	else
		if (t1->period.get_hours() < t2->ends.get_hours())
			return -1;
		else
			if (t1->period.get_minutes() > t2->ends.get_minutes())
				return 1;
			else
				if (t1->period.get_minutes() < t2->ends.get_minutes())
					return -1;
				else
					return 0;
}

bool period_comp(course* courses, course index, int pos, int& acctual) {
	bool check = false;
	for (int i = pos - 1; i >= 0; i--) {
		if ((strcmp(index.days, courses[i].days) == 0) && (time_comp(&(index), &(courses[i])) >= 0) && (end_comp(&(index), &(courses[i])) == -1)) {
			check = true;
			acctual = i;
			break;
		}
		if ((strcmp(index.days, courses[i].days) == 0) && (time_comp(&(index), &(courses[i])) <= 0) && (end_comp(&(courses[i]), &(index)) == -1)) {
			check = true;
			acctual = i;
			break;
		}
	}
	return check;
}

void alternate_print_course(course* crs) {
	cout << crs->get_code() << " -> " << crs->period << " (" << crs->credits << (crs->credits == 1 ? " credit)" : " credits)") << endl;
}