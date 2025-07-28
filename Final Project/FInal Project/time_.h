#include <iostream>
using namespace std;

class time_ {
	friend istream& operator>>(istream&, time_&);
	friend ostream& operator<<(ostream&, time_&);
private:
	int hours, minutes;
public:
	time_(int t = 0) : hours(0), minutes(0) {}
	//setter function for hours
	void set_hours(int h) {
		hours = h;
	}
	//setter function for minutes
	void set_minutes(int m) {
		minutes = m;
	}
	//getter function for hours
	int get_hours() {
		return hours;
	}
	//getter function for minutes
	int get_minutes() {
		return minutes;
	}
};

istream& operator>>(istream& in, time_& tm) {
	do {
		cout << "Time (H/M) -> ";
		in >> tm.hours >> tm.minutes;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (tm.hours < 0 || tm.hours > 23 || tm.minutes < 0 || tm.minutes>59 || cin.fail());
	return in;
}

ostream& operator<<(ostream& out, time_& tm) {
	out << (tm.hours < 10 ? "0" : "") << tm.hours << ":";
	out << (tm.minutes < 10 ? "0" : "") << tm.minutes << ":";
	out << "00";
	return out;
}