#ifndef _STUDENTS_H_
#define _STUDENTS_H_

#include "member.h"

class student : public member {
	//checks majors for binary file
	friend void check_major(char[], int&, int&, int&, int&, int&);

	//function to search for a student (by name) in the binary file
	friend bool search_std_binary(student*, char[]);

	//function to display all students in one major from a binary file
	friend void display_std_binary_major(student*, char[]);

	//function to enter students in a binary file depending on their major
	friend void input_std_binary_major(student*, int, char[]);

	//function to display all students present in the binary file
	friend void display_std_binary(student*);

	//function to update desired information of a student
	friend void update_std_info(student*, int);

	friend bool searchstd_by_name(student*, int, int&, char[]);
	friend bool searchstd_by_id(student*, int, int&, int);

	//function that groups students in the same major
	friend void group_by_major(student*, int);

	//function to group students that started in the same semester
	friend void group_by_year(student*, int);
	friend void sort_by_credits(student*, int);
	friend void sort_by_semester(student*, int);
	friend istream& operator>>(istream&, student&);
	friend ostream& operator<<(ostream&, const student&);
private:
	int credits;
	double gpa;
	char major[20];
public:
	student() : member() {
		credits = 0;
		gpa = 0;
		strcpy_s(major, "N/A");
	}
	//overloading += operator for student objects to add up student GPAs
	student& operator+=(const student&);
	//getter function returning student majors
	char* get_major() {
		return major;
	}
};

//display file options for students
void std_file_menu();
void std_menu();

//function to remove a student directly from the binary file
void remove_std_binary(student*);

//function counting number of students in the binary file
int student_file_counter(ifstream&);
void input_std_binary(student*, int);
void display_all_stds(student*, int);
void input_all_stds(student* students, int n);
void swap_stds(student*, student*);
void add_std(student*, int, int&);
void remove_std(student*, int, int&);

student& student::operator+=(const student& st) {
	gpa += st.gpa;
	return *this;
}

istream& operator>>(istream& in, student& st) {
	cout << "\nStudent information : \n";
	cout << "--------------------\n\n";
	cout << "Full name: "; in.ignore(); in.getline(st.name, 40);
	do {
		cout << "Student ID: ";
		in >> st.id;
	} while (st.id <= 0);
	do {
		cout << "Gender(M/F): ";
		in >> st.gender;
	} while (st.gender != 'M' && st.gender != 'F');
	cout << "Date of birth: " << endl;
	in >> st.birth;
	cout << "\nAvailable majors (CCE-MCE-CME-BFE-BME)" << endl;
	cout << "Major: "; in.ignore(); in.getline(st.major, 20);
	while (strcmp(st.major, "CCE") != 0 && strcmp(st.major, "MCE") != 0 && strcmp(st.major, "BME") != 0
		&& strcmp(st.major, "BFE") != 0 && strcmp(st.major, "CME") != 0) {
		cout << "Major: "; in.getline(st.major, 20);
	}
	do {
		cout << "Starting semester: ";
		in >> st.started.season >> st.started.year;
	} while (st.started.year < 2000 || st.started.year > 2023);
	do {
		cout << "GPA: ";
		in >> st.gpa;
	} while (st.gpa < 0.00 || st.gpa> 4.00);
	do {
		cout << "Credits completed: ";
		in >> st.credits;
	} while (st.credits < 0);
	return in;
}

ostream& operator<<(ostream& out, const student& st) {
	out << st.name << "-" << st.id << " (" << st.major << ")\n";
	out << "Gender: " << st.gender << endl;
	out << "Date of birth: " << st.birth << endl;
	out << "Starting semester: " << st.started.season << " " << st.started.year << endl;
	out << "Credits completed: " << st.credits << endl;
	out << "GPA: " << setprecision(2) << fixed << showpoint << st.gpa << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x4);
	out << "----------------------------------------------------------\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
	return out;
}

void display_all_stds(student* students, int n) {
	cout << "Displaying all students...\n";
	cout << "--------------------------\n\n";
	for (int i = 0; i < n; i++) {
		cout << students[i] << "\n";
	}
	cout << "\n";
}

void input_all_stds(student* students, int n) {
	cout << "Input all students...\n";
	cout << "--------------------------\n";
	for (int i = 0; i < n; i++) {
		cin >> students[i];
	}
	cout << "\n";
}

void swap_stds(student* s1, student* s2) {
	student temp;
	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void sort_by_credits(student* students, int n) {
	char choice;
	do {
		cout << "Do you want to sort in ascending(a) or descending(d) order? ";
		cin >> choice;
	} while (choice != 'a' && choice != 'd');
	switch (choice) {
	case 'a':
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				if (students[j].credits > students[j + 1].credits)
					swap_stds(&(students[j]), &(students[j + 1]));
			}
		}
		break;
	case 'd':
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				if (students[j].credits < students[j + 1].credits)
					swap_stds(&(students[j]), &(students[j + 1]));
			}
		}
		break;
	}
}

void sort_by_semester(student* students, int n) {
	char choice;
	do {
		cout << "Do you want to sort in ascending(a) or descending(d) order? ";
		cin >> choice;
	} while (choice != 'a' && choice != 'd');
	switch (choice) {
	case 'a':
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				if (semester_comp(&(students[j].started), &(students[j + 1].started)) == -1)
					swap_stds(&(students[j]), &(students[j + 1]));
			}
		}
		break;
	case 'd':
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				if (semester_comp(&(students[j].started), &(students[j + 1].started)) == 1)
					swap_stds(&(students[j]), &(students[j + 1]));
			}
		}
		break;
	}

}

void group_by_major(student* students, int n) {
	bool check = false;
	char search_major[20];
	cout << "Select major: ";
	cin >> search_major;
	cout << "\n\n";
	for (int i = 0; i < n; i++) {
		if (strcmp(search_major, students[i].major) == 0) {
			cout << students[i].name << "-" << students[i].id << endl;
			check = true;
		}
	}
	if (!check)
		cerr << "No students found" << endl;
	else
		cerr << "\nSuccessfull\n" << endl;
}

void group_by_year(student* students, int n) {
	bool check = false;
	semester search_sem;
	cout << "Select semester: ";
	cin >> search_sem.season >> search_sem.year;
	cout << "\n\n";
	for (int i = 0; i < n; i++) {
		if (semester_comp(&(students[i].started), &search_sem) == 0) {
			cout << students[i].name << "-" << students[i].id << endl;
			check = true;
		}
	}
	if (!check)
		cerr << "No students found" << endl;
	else
		cerr << "\nSuccessfull\n" << endl;
}

void add_std(student* students, int n, int& std_count) {
	if (n == 1000) {
		cout << "Can no longer add students\n\n";
	}
	else {
		cin >> students[n];
		std_count++;
	}
}

bool searchstd_by_name(student* students, int n, int& pos, char search[]) {
	if (n == 0)
		return false;
	if (strcmp(search, students[n - 1].name) == 0) {
		pos = n - 1;
		return true;
	}
	else
		return searchstd_by_name(students, n - 1, pos, search);
}

bool searchstd_by_id(student* students, int n, int& pos, int search) {
	if (n == 0)
		return false;
	if (search == students[n - 1].id) {
		pos = n - 1;
		return true;
	}
	else
		return searchstd_by_id(students, n - 1, pos, search);
}

void remove_std(student* students, int n, int& std_count) {
	if (n == 0) {
		cout << "Can no longer remove students\n\n";
	}
	else {
		int search_id, pos1 = -1, pos2 = -1;
		char search_name[40];
		char choice;
		do {
			cout << "Would you like to search by name(n) or by id(i)? ";
			cin >> choice;
		} while (choice != 'n' && choice != 'i');
		switch (choice) {
		case 'n':
			cout << "Select student: ";
			cin.ignore();
			cin.getline(search_name, 40);
			if (searchstd_by_name(students, n, pos1, search_name)) {
				for (int i = pos1; i < n; i++) {
					students[i] = students[i + 1];
				}
				std_count--;
			}
			else
				cerr << "Student not found" << endl;
			break;
		case 'i':
			cout << "Select student: ";
			cin >> search_id;
			if (searchstd_by_id(students, n, pos1, search_id)) {
				for (int i = pos2; i < n; i++) {
					students[i] = students[i + 1];
				}
				std_count--;
				cout << "\nSuccessfully removed\n";
			}
			else
				cerr << "Student not found" << endl;
			break;
		}
	}
}

void update_std_info(student* students, int n) {
	int search_id, pos1 = -1, pos2 = -1, action;
	char search_name[40];
	char choice;
	do {
		cout << "Would you like to search by name(n) or by id(i)? ";
		cin >> choice;
	} while (choice != 'n' && choice != 'i');
	switch (choice) {
	case 'n':
		cout << "Select student: ";
		cin.ignore();
		cin.getline(search_name, 40);
		if (searchstd_by_name(students, n, pos1, search_name)) {
			cout << "\n1) All attributes" << endl;
			cout << "2) Name" << endl;
			cout << "3) ID" << endl;
			cout << "4) Gender" << endl;
			cout << "5) Date of birth" << endl;
			cout << "6) Major" << endl;
			cout << "7) GPA" << endl;
			cout << "8) Starting semester" << endl;
			cout << "9) Credits completed" << endl;
			do {
				cout << "-->"; cin >> action;
			} while (action < 1 || action >9);
			switch (action) {
			case 1:
				cin >> students[pos1];
				break;
			case 2:
				cout << "Full name: "; cin.ignore(); cin.getline(students[pos1].name, 40);
				break;
			case 3:
				do {
					cout << "Student ID: ";
					cin >> students[pos1].id;
				} while (students[pos1].id <= 0);
				break;
			case 4:
				do {
					cout << "Gender(M/F): ";
					cin >> students[pos1].gender;
				} while (students[pos1].gender != 'M' && students[pos1].gender != 'F');
				break;
			case 5:
				cin >> students[pos1].birth;
				break;
			case 6:
				cout << "\nAvailable majors (CCE-MCE-CME-BFE-BME)" << endl;
				cout << "Major: "; cin.ignore(); cin.getline(students[pos1].major, 20);
				while (strcmp(students[pos1].major, "CCE") != 0 && strcmp(students[pos1].major, "BME") != 0 &&
					strcmp(students[pos1].major, "BFE") != 0 && strcmp(students[pos1].major, "CME") != 0
					&& strcmp(students[pos1].major, "MCE") != 0) {
					cout << "Major: "; cin.getline(students[pos1].major, 20);
				}
				break;
			case 7:
				do {
					cout << "GPA: ";
					cin >> students[pos1].gpa;
				} while (students[pos1].gpa < 0.00 || students[pos1].gpa> 4.00);
				break;
			case 8:
				do {
					cout << "Starting semester: ";
					cin >> students[pos1].started.season >> students[pos1].started.year;
				} while (students[pos1].started.year < 2000 || students[pos1].started.year > 2023);
				break;
			case 9:
				do {
					cout << "Credits completed: ";
					cin >> students[pos1].credits;
				} while (students[pos1].credits < 0);
				break;
			}
		}
		else
			cerr << "Student not found" << endl;
		break;
	case 'i':
		cout << "Select student: ";
		cin >> search_id;
		if (searchstd_by_id(students, n, pos2, search_id)) {
			cout << "1) All attributes" << endl;
			cout << "2) Name" << endl;
			cout << "3) ID" << endl;
			cout << "4) Gender" << endl;
			cout << "5) Date of birth" << endl;
			cout << "6) Major" << endl;
			cout << "7) GPA" << endl;
			cout << "8) Starting semester" << endl;
			cout << "9) Credits completed" << endl;
			do {
				cout << "-->"; cin >> action;
			} while (action < 1 || action >9);
			switch (action) {
			case 1:
				cin >> students[pos2];
				break;
			case 2:
				cout << "Full name: "; cin.ignore(); cin.getline(students[pos2].name, 40);
				break;
			case 3:
				do {
					cout << "Student ID: ";
					cin >> students[pos2].id;
				} while (students[pos2].id <= 0);
				break;
			case 4:
				do {
					cout << "Gender(M/F): ";
					cin >> students[pos2].gender;
				} while (students[pos2].gender != 'M' && students[pos2].gender != 'F');
				break;
			case 5:
				cin >> students[pos2].birth;
				break;
			case 6:
				cout << "\nMajor: "; cin.ignore(); cin.getline(students[pos2].major, 20);
				while (strcmp(students[pos2].major, "CCE") != 0 && strcmp(students[pos2].major, "BME") != 0 &&
					strcmp(students[pos2].major, "BFE") != 0 && strcmp(students[pos2].major, "CME") != 0
					&& strcmp(students[pos2].major, "MCE") != 0) {
					cout << "Major: "; cin.getline(students[pos2].major, 20);
				}
				break;
			case 7:
				do {
					cout << "GPA: ";
					cin >> students[pos2].gpa;
				} while (students[pos2].gpa < 0.00 || students[pos2].gpa> 4.00);
				break;
			case 8:
				do {
					cout << "Starting semester: ";
					cin >> students[pos2].started.season >> students[pos2].started.year;
				} while (students[pos2].started.year < 2000 || students[pos2].started.year > 2023);
				break;
			case 9:
				do {
					cout << "Credits completed: ";
					cin >> students[pos2].credits;
				} while (students[pos2].credits < 0);
				break;
			}
		}
		else
			cerr << "Student not found" << endl;
		break;
	}
}

int student_file_counter(ifstream& file) {
	file.seekg(0, ios::end);
	return (file.tellg() / sizeof(student));
}

void input_std_binary(student* students, int n) {
	ofstream file;
	file.open("Students.dat", ios::binary | ios::app);
	for (int i = 0; i < n; i++) {
		file.write((char*)(&(students[i])), sizeof(student));
	}
	file.close();
}

void display_std_binary(student* students) {
	double avg;
	student s, in;
	int counter;
	ifstream file;
	file.open("Students.dat", ios::binary);
	counter = student_file_counter(file);
	if (counter == 0 || file.fail())
		cout << "\a\nNo students in this file\n\n";
	else {
		file.seekg(0);
		for (int i = 0; i < counter; i++) {
			file.read((char*)(&(in)), sizeof(student));
			cout << in << endl;
			s += in;
		}
		file.close();
		avg = s.gpa / counter;
		cout << "The average GPA is: " << avg << "\n\n";
	}
}

void input_std_binary_major(student* students, int n, char std_major[]) {
	ofstream file;
	char file_name[40];
	strcpy_s(file_name, std_major);
	strcat_s(file_name, "_File.dat");
	file.open(file_name, ios::binary | ios::app);
	for (int i = 0; i < n; i++) {
		if (strcmp(students[i].major, std_major) == 0) {
			file.write((char*)(&(students[i])), sizeof(student));
		}
	}
	file.close();
}

void display_std_binary_major(student* students, char std_major[]) {
	double avg;
	student s, in;
	int counter;
	ifstream file;
	char file_name[40];
	strcpy_s(file_name, std_major);
	strcat_s(file_name, "_File.dat");
	file.open(file_name, ios::binary);
	counter = student_file_counter(file);
	if (counter == 0 || file.fail())
		cout << "\aNo students in this file\n\n";
	else {
		file.seekg(0);
		for (int i = 0; i < counter; i++) {
			file.read((char*)(&(in)), sizeof(student));
			cout << in << endl;
			s += in;
		}
		file.close();
		avg = s.gpa / counter;
		cout << "The average GPA for this major is: " << avg << endl;
	}
}

void remove_std_binary(student* students) {
	char search[40], file_name[40];
	int count1, count2, pos1 = -1, pos2 = -1;
	cout << "\nRemove student: ";
	cin.ignore();
	cin.getline(search, 40);
	ifstream stds, majors;
	ofstream new_stds, new_majors;
	stds.open("Students.dat", ios::binary);
	new_stds.open("New_Students.dat", ios::binary);
	count1 = student_file_counter(stds);
	if (count1 == 0 || stds.fail())
		cout << "\nNo students in this file\n\n";
	else {
		stds.seekg(0);
		for (int i = 0; i < count1; i++) {
			stds.read((char*)(&(students[0])), sizeof(student));
			if (strcmp(search, students[0].get_name()) == 0) {
				cout << "\nStudent found\n";
				pos1 = i;
				strcpy_s(file_name, students[0].get_major());
				break;
			}
		}
		strcat_s(file_name, "_File.dat");
		if (pos1 == -1) {
			stds.close();
			new_stds.close();
			majors.close();
			new_majors.close();
			remove("Sub_Majors.dat");
			remove("New_Students.dat");
			cout << "\nStudent not found\n\n";
		}
		if (pos1 != -1) {
			majors.open(file_name, ios::binary);
			new_majors.open("Sub_Majors.dat", ios::binary | ios::trunc);
			count2 = student_file_counter(majors);
			majors.seekg(0);
			for (int j = 0; j < count2; j++) {
				majors.read((char*)(&(students[0])), sizeof(student));
				if (strcmp(search, students[0].get_name()) == 0) {
					pos2 = j;
					break;
				}
			}
			stds.seekg(0);
			for (int i = 0; i < count1; i++) {
				if (i == pos1)
					stds.seekg((i + 1) * sizeof(student));
				else {
					stds.read((char*)(&(students[0])), sizeof(student));
					new_stds.write((char*)(&(students[0])), sizeof(student));
				}
			}
			if (pos2 != -1) {
				majors.seekg(0);
				for (int i = 0; i < count2; i++) {
					if (i == pos2)
						majors.seekg((i + 1) * sizeof(student));
					else {
						majors.read((char*)(&(students[0])), sizeof(student));
						new_majors.write((char*)(&(students[0])), sizeof(student));
					}
				}
			}
			stds.close();
			new_stds.close();
			majors.close();
			new_majors.close();
			remove("Students.dat");
			remove(file_name);
			rename("New_Students.dat", "Students.dat");
			rename("Sub_Majors.dat", file_name);
			cout << "\nSuccessfully removed\n";
		}
	}
}

void std_menu() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);
	cout << "Student management: " << endl;
	cout << "-------------------\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
	cout << "1) Input student information" << endl;
	cout << "2) Display student information" << endl;
	cout << "3) Sort students by credits completed" << endl;
	cout << "4) Sort students by semester started" << endl;
	cout << "5) Group students by major" << endl;
	cout << "6) Group students by semester started" << endl;
	cout << "7) Search for student by name" << endl;
	cout << "8) Search for student by ID" << endl;
	cout << "+) Add student" << endl;
	cout << "-) Remove student" << endl;
	cout << "*) Update student information" << endl;
	cout << "f) File options" << endl;
	cout << "B) Go back" << endl;
}

void std_file_menu() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xE);
	cout << "File options: " << endl;
	cout << "-------------\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC0);
	cout << "Warning!! All information entered during the code's runtime are saved upon exit\n";
	cout << "End code execution to save all the info into the binary file for display\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
	cout << "1) Display from binary file" << endl;
	cout << "2) Remove student from binary file" << endl;
	cout << "3) Dipslay students by major" << endl;
	cout << "B) Go back" << endl;
}

bool search_std_binary(student* students, char name[]) {
	int count;
	ifstream stds;
	stds.open("Students.dat", ios::binary);
	if (stds.fail())
		return false;
	count = student_file_counter(stds);
	stds.seekg(0);
	for (int i = 0; i < count; i++) {
		stds.read((char*)(&(students[0])), sizeof(student));
		if (strcmp(name, students[0].get_name()) == 0) {
			return true;
			stds.close();
		}
	}
	return false;
	stds.close();
}

void check_major(char major[], int& CCE, int& MCE, int& CME, int& BFE, int& BME) {
	if (strcmp(major, "CCE") == 0)
		CCE = 1;
	if (strcmp(major, "MCE") == 0)
		MCE = 1;
	if (strcmp(major, "BME") == 0)
		BME = 1;
	if (strcmp(major, "BFE") == 0)
		BFE = 1;
	if (strcmp(major, "CME") == 0)
		CME = 1;
}

#endif _STUDENTS_H_