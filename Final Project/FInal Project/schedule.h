//including course.h header file
#include "course.h"
#include <windows.h>
#include <iomanip>
#include <fstream>

class schedule {
	//function to read from schedule text file
	friend bool read_from_file(char[]);

	//function to input a students schdule and record it into a text file
	friend void text_schedule(schedule, char[]);

	//function to arrange courses by time taken
	friend void arrange_by_time(schedule*);
	friend istream& operator>>(istream&, schedule&);
	friend ostream& operator<<(ostream&, schedule&);

	//alernate print mode for schedule objects (used for testing)
	friend void alternate_print_schedule(schedule*);
private:
	int num_courses;
	course* courses;
public:
	//schedule class constructor
	schedule() {
		num_courses = 1;
		courses = 0;
	}
	//schedule class destructor
	//~schedule() { delete[]courses; }
};

//display main menu
void main_menu();
void sch_menu();

istream& operator>>(istream& in, schedule& sch) {
	int acc = -1;
	int count = 0;
	course input;
	cout << "Enter number of courses: ";
	in >> sch.num_courses;
	sch.courses = new course[sch.num_courses];
	cout << "\nRead all courses: " << endl;
	cout << "---------------------\n" << endl;
	for (int i = 0; i < sch.num_courses; i++) {
		cout << "Course " << i + 1 << ": " << endl;
		in >> input;
		set_end_time(&input);
		if (count >= 1) {
			while (period_comp(sch.courses, input, i, acc)) {
				cout << "\aTime conflict between this course and the " << sch.courses[acc].get_code() << " course" << endl;
				cout << "Course " << i + 1 << ": " << endl;
				in >> input;
				set_end_time(&input);
			}
		}
		sch.courses[i] = input;
		++count;
		cout << "\n";
	}
	return in;
}

ostream& operator<<(ostream& out, schedule& sch) {
	out << "\n\n";
	out << sch.num_courses << (sch.num_courses != 1 ? " courses" : " course") << endl;
	out << "\n";
	out << "\t\t" << left << setw(15) << "Monday" << setw(15) << "Tuesday" << setw(15) << "Wednesday" <<
		setw(15) << "Thursday" << "Friday\n";
	out << "\t\t" << left << "------------------------------------------------------------------\n\n";
	arrange_by_time(&sch);
	for (int i = 0; i < sch.num_courses; i++) {
		out << sch.courses[i] << endl;
	}
	return out;
}

void arrange_by_time(schedule* sch) {
	course temp;
	for (int i = 0; i < sch->num_courses - 1; i++) {
		for (int j = 0; j < sch->num_courses - 1; j++) {
			if (time_comp(&(sch->courses[j]), &(sch->courses[j + 1])) == 1) {
				temp = sch->courses[j];
				sch->courses[j] = sch->courses[j + 1];
				sch->courses[j + 1] = temp;
			}
		}
	}
}

void alternate_print_schedule(schedule* sch) {
	arrange_by_time(sch);
	int countMW = 0, countTTH = 0, countF = 0;
	for (int i = 0; i < sch->num_courses; i++) {
		if (strcmp(sch->courses[i].get_days(), "MW") == 0)
			countMW++;
		if (strcmp(sch->courses[i].get_days(), "TTH") == 0)
			countTTH++;
		if (strcmp(sch->courses[i].get_days(), "F") == 0)
			countF++;
	}
	if (countMW > 0) {
		cout << "\nMW courses: \n";
		cout << "--------------\n";
		int inc1 = 0;
		for (int i = 0; i < sch->num_courses; i++) {
			if (strcmp(sch->courses[i].get_days(), "MW") == 0) {
				cout << "Course " << inc1 + 1 << ": ";
				alternate_print_course(&(sch->courses[i]));
				++inc1;
			}
		}
	}
	else
		cerr << "\nNo courses registered on mondays and wednesdays" << endl;
	if (countTTH > 0) {
		cout << "\nTTH courses: \n";
		cout << "--------------\n";
		int inc2 = 0;
		for (int i = 0; i < sch->num_courses; i++) {
			if (strcmp(sch->courses[i].get_days(), "TTH") == 0) {
				cout << "Course " << inc2 + 1 << ": ";
				alternate_print_course(&(sch->courses[i]));
				++inc2;
			}
		}
	}
	else
		cerr << "\nNo courses registered on tuesdays and thursdays" << endl;
	if (countF > 0) {
		cout << "\nF courses: \n";
		cout << "-------------\n";
		int inc3 = 0;
		for (int i = 0; i < sch->num_courses; i++) {
			if (strcmp(sch->courses[i].get_days(), "F") == 0) {
				cout << "Course " << inc3 + 1 << ": ";
				alternate_print_course(&(sch->courses[i]));
				++inc3;
			}
		}
	}
	else
		cerr << "\nNo courses registered on fridays" << endl;
}

void sch_menu() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xD);
	cout << "Schedule management: " << endl;
	cout << "-------------------\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
	cout << "1) Set student schedule" << endl;
	cout << "2) Set teacher schedule" << endl;
	cout << "3) Display schedule" << endl;
	cout << "B) Go back" << endl;
}

void main_menu() {
	cout << "1) Manage students" << endl;
	cout << "2) Manage teachers" << endl;
	cout << "3) Manage schedules" << endl;
	cout << "T) ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x4);
	cout << "End execution" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
}

void text_schedule(schedule sch, char name[]) {
	ofstream file;
	char file_name[80];
	strcpy_s(file_name, name);
	strcat_s(file_name, "'s_schedule.txt");
	file.open(file_name);
	file << sch << endl;
	file.close();
}

bool read_from_file(char name[]) {
	char line[200];
	ifstream file;
	char file_name[40];
	strcpy_s(file_name, name);
	strcat_s(file_name, "'s_schedule.txt");
	file.open(file_name);
	if (file.fail()) {
		return false;
	}
	else {
		file.ignore();
		file.getline(line, 200);
		while (!file.eof()) {
			cout << line << endl;
			file.getline(line, 200);
		}
		file.close();
	}
	return true;
}