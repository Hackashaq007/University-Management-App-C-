#ifndef _TEACHER_H_
#define _TEACHER_H_

#include "member.h"

class teacher : public member {
	//function to search for a teacher (by name) from a binary file
	friend bool search_tch_binary(teacher*, char[]);

	//function to update a teacher's deisred information
	friend void update_tch_info(teacher*, int);

	//recursive function to search for a teacher by ID
	friend bool searchtch_by_id(teacher*, int, int&, int);

	//recursive function to search for a teacher by name
	friend bool searchtch_by_name(teacher*, int, int&, char[]);

	//function to group teachers according to their specialization
	friend void group_by_specialization(teacher*, int);

	//function to sort teachers by age
	friend void sort_by_age_tch(teacher*, int);

	//function to sort teachers by semester started
	friend void sort_by_semester(teacher*, int);

	//overloading input operator for teacher objects
	friend istream& operator>>(istream&, teacher&);

	//overloading output operator for teacher objects
	friend ostream& operator<<(ostream&, teacher&);
private:
	double salary;
	char specialization[20];
public:
	//teacher class constructor
	teacher() :member() {
		salary = 0;
		strcpy_s(specialization, "N/A");
	}
};

void display_tch_binary(teacher*);

//display teacher file options menu
void tch_file_menu();

void tch_menu();

//function to input teachers into the binary file
void input_tch_binary(teacher*, int);

//function to count number of teachers in a binary file
int teacher_file_counter(ifstream&);

//function to remove teacher from a binary file
void remove_tch_binary(teacher*);

void add_tch(teacher*, int, int&);
void swap_tchs(teacher*, teacher*);
void remove_tch(teacher*, int, int&);
void display_all_tchs(teacher*, int);
void input_all_tchs(teacher*, int);

istream& operator>>(istream& in, teacher& tch) {
	cout << "\nTeacher information : \n";
	cout << "--------------------\n\n";
	cout << "Full name: "; in.ignore(); in.getline(tch.name, 40);
	do {
		cout << "Teacher ID: ";
		in >> tch.id;
	} while (tch.id <= 0);
	do {
		cout << "Gender(M/F): ";
		in >> tch.gender;
	} while (tch.gender != 'M' && tch.gender != 'F');
	cout << "Date of birth: " << endl;
	in >> tch.birth;
	cout << "\nSpecialization: "; in.ignore(); in.getline(tch.specialization, 20);
	do {
		cout << "Starting semester: ";
		in >> tch.started.season >> tch.started.year;
	} while (tch.started.year < 1990 || tch.started.year > 2023);
	do {
		cout << "Salary($/month): ";
		in >> tch.salary;
	} while (tch.salary < 0);
	return in;
}

ostream& operator<<(ostream& out, teacher& tch) {
	out << tch.name << "-" << tch.id << " (" << tch.specialization << ")\n";
	out << "Gender: " << tch.gender << endl;
	out << "Date of birth: " << tch.birth << endl;
	out << "Starting semester: " << tch.started.season << " " << tch.started.year << endl;
	out << "Salary: " << setprecision(2) << fixed << showpoint << tch.salary << " $/month" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x4);
	out << "----------------------------------------------------------\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
	return out;
}

void display_all_tchs(teacher* teachers, int n) {
	cout << "Displaying all teachers...\n";
	cout << "--------------------------\n\n";
	for (int i = 0; i < n; i++) {
		cout << teachers[i] << "\n";
	}
	cout << "\n";
}

void input_all_tchs(teacher* teachers, int n) {
	cout << "Input all teachers...\n";
	cout << "--------------------------\n";
	for (int i = 0; i < n; i++) {
		cin >> teachers[i];
	}
	cout << "\n";
}

void swap_tchs(teacher* tch1, teacher* tch2) {
	teacher temp;
	temp = *tch1;
	*tch1 = *tch2;
	*tch2 = temp;
}

void sort_by_semester(teacher* teachers, int n) {
	char choice;
	do {
		cout << "Do you want to sort in ascending(a) or descending(d) order? ";
		cin >> choice;
	} while (choice != 'a' && choice != 'd');
	switch (choice) {
	case 'a':
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				if (semester_comp(&(teachers[j].started), &(teachers[j + 1].started)) == -1)
					swap_tchs(&(teachers[j]), &(teachers[j + 1]));
			}
		}
		break;
	case 'd':
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				if (semester_comp(&(teachers[j].started), &(teachers[j + 1].started)) == 1)
					swap_tchs(&(teachers[j]), &(teachers[j + 1]));
			}
		}
		break;
	}
}

void sort_by_age_tch(teacher* teachers, int n) {
	char choice;
	do {
		cout << "Do you want to sort in ascending(a) or descending(d) order? ";
		cin >> choice;
	} while (choice != 'a' && choice != 'd');
	switch (choice) {
	case 'a':
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				if (date_comp(&(teachers[j].birth), &(teachers[j + 1].birth)) == -1)
					swap_tchs(&(teachers[j]), &(teachers[j + 1]));
			}
		}
		break;
	case 'd':
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				if (date_comp(&(teachers[j].birth), &(teachers[j + 1].birth)) == 1)
					swap_tchs(&(teachers[j]), &(teachers[j + 1]));
			}
		}
		break;
	}
}

void group_by_specialization(teacher* teachers, int n) {
	bool check = false;
	char search_spec[20];
	cout << "Select specialization: ";
	cin >> search_spec;
	for (int i = 0; i < n; i++) {
		if (strcmp(search_spec, teachers[i].specialization) == 0) {
			cout << teachers[i].name << "-" << teachers[i].id << endl;
			check = true;
		}
	}
	if (!check)
		cerr << "No teachers found" << endl;
	else
		cerr << "Successfull" << endl;
}

void add_tch(teacher* teachers, int n, int& tch_count) {
	if (n == 500) {
		cout << "Can no longer add teachers\n\n";
	}
	else {
		tch_count++;
		cin >> teachers[n];
	}
}

bool searchtch_by_id(teacher* teachers, int n, int& pos, int search_id) {
	if (n == 0)
		return false;
	if (search_id == teachers[n - 1].id) {
		pos = n - 1;
		return true;
	}
	else
		return searchtch_by_id(teachers, n - 1, pos, search_id);
}

bool searchtch_by_name(teacher* teachers, int n, int& pos, char search_name[]) {
	if (n == 0)
		return false;
	if (strcmp(search_name, teachers[n - 1].name) == 0) {
		pos = n - 1;
		return true;
	}
	else
		return searchtch_by_name(teachers, n - 1, pos, search_name);
}

void remove_tch(teacher* teachers, int n, int& tch_count) {
	if (n == 0) {
		cout << "Can no longer remove teachers\n\n";
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
			cout << "Select teacher: ";
			cin.ignore();
			cin.getline(search_name, 40);
			if (searchtch_by_name(teachers, n, pos1, search_name)) {
				for (int i = pos1; i < n; i++) {
					teachers[i] = teachers[i + 1];
				}
				tch_count--;
				cout << "\nSuccessfully removed\n";
			}
			else
				cerr << "Teacher not found" << endl;
			break;
		case 'i':
			cout << "Select teacher: ";
			cin >> search_id;
			if (searchtch_by_id(teachers, n, pos1, search_id)) {
				for (int i = pos2; i < n; i++) {
					teachers[i] = teachers[i + 1];
				}
				tch_count--;
			}
			else
				cerr << "Teacher not found" << endl;
			break;
		}
	}
}

void update_tch_info(teacher* teachers, int n) {
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
		if (searchtch_by_name(teachers, n, pos1, search_name)) {
			cout << "1) All attributes" << endl;
			cout << "2) Name" << endl;
			cout << "3) ID" << endl;
			cout << "4) Gender" << endl;
			cout << "5) Date of birth" << endl;
			cout << "6) Specialization" << endl;
			cout << "7) Salary" << endl;
			cout << "8) Starting semester" << endl;
			do {
				cout << "-->"; cin >> action;
			} while (action < 1 || action >8);
			switch (action) {
			case 1:
				cin >> teachers[pos1];
				break;
			case 2:
				cout << "Full name: "; cin.ignore(); cin.getline(teachers[pos1].name, 40);
				break;
			case 3:
				do {
					cout << "Teacher ID: ";
					cin >> teachers[pos1].id;
				} while (teachers[pos1].id <= 0);
				break;
			case 4:
				do {
					cout << "Gender(M/F): ";
					cin >> teachers[pos1].gender;
				} while (teachers[pos1].gender != 'M' && teachers[pos1].gender != 'F');
				break;
			case 5:
				cin >> teachers[pos1].birth;
				break;
			case 6:
				cout << "\nSpecialization: "; cin.ignore(); cin.getline(teachers[pos1].specialization, 20);
				break;
			case 7:
				do {
					cout << "Salary($/month): ";
					cin >> teachers[pos1].salary;
				} while (teachers[pos1].salary < 0);
				break;
			case 8:
				do {
					cout << "Starting semester: ";
					cin >> teachers[pos1].started.season >> teachers[pos1].started.year;
				} while (teachers[pos1].started.year < 2000 || teachers[pos1].started.year > 2023);
				break;
			}
		}
		else
			cerr << "Teacher not found" << endl;
		break;
	case 'i':
		cout << "Select student: ";
		cin >> search_id;
		if (searchtch_by_id(teachers, n, pos2, search_id)) {
			cout << "1) All attributes" << endl;
			cout << "2) Name" << endl;
			cout << "3) ID" << endl;
			cout << "4) Gender" << endl;
			cout << "5) Date of birth" << endl;
			cout << "6) Specialization" << endl;
			cout << "7) Salary" << endl;
			cout << "8) Starting semester" << endl;
			do {
				cout << "-->"; cin >> action;
			} while (action < 1 || action >8);
			switch (action) {
			case 1:
				cin >> teachers[pos2];
				break;
			case 2:
				cout << "Full name: "; cin.ignore(); cin.getline(teachers[pos2].name, 40);
				break;
			case 3:
				do {
					cout << "Teacher ID: ";
					cin >> teachers[pos2].id;
				} while (teachers[pos2].id <= 0);
				break;
			case 4:
				do {
					cout << "Gender(M/F): ";
					cin >> teachers[pos2].gender;
				} while (teachers[pos2].gender != 'M' && teachers[pos2].gender != 'F');
				break;
			case 5:
				cin >> teachers[pos2].birth;
				break;
			case 6:
				cout << "\nSpecialization: "; cin.ignore(); cin.getline(teachers[pos2].specialization, 20);
				break;
			case 7:
				do {
					cout << "Salary($/month): ";
					cin >> teachers[pos2].salary;
				} while (teachers[pos2].salary < 0);
				break;
			case 8:
				do {
					cout << "Starting semester: ";
					cin >> teachers[pos2].started.season >> teachers[pos2].started.year;
				} while (teachers[pos2].started.year < 2000 || teachers[pos2].started.year > 2023);
				break;
			}
		}
		else
			cerr << "Teacher not found" << endl;
		break;
	}
}

int teacher_file_counter(ifstream& file) {
	file.seekg(0, ios::end);
	return (file.tellg() / sizeof(teacher));
}

void input_tch_binary(teacher* teachers, int n) {
	ofstream file;
	file.open("Teachers.dat", ios::binary | ios::app);
	for (int i = 0; i < n; i++) {
		file.write((char*)(&(teachers[i])), sizeof(teacher));
	}
	file.close();
}

void display_tch_binary(teacher* teachers) {
	int counter;
	ifstream file;
	teacher tch;
	file.open("Teachers.dat", ios::binary);
	counter = teacher_file_counter(file);
	if (counter == 0 || file.fail()) {
		cout << "No teachers in this file\n\n";
	}
	else {
		file.seekg(0);
		for (int i = 0; i < counter; i++) {
			file.read((char*)(&(tch)), sizeof(teacher));
			cout << tch << endl;
		}
		file.close();
	}
}

void remove_tch_binary(teacher* teachers) {
	bool test;
	int pos = -1, count;
	char search_name[40];
	ifstream Teachers;
	ofstream sub_teachers;
	Teachers.open("Teachers.dat", ios::binary);
	sub_teachers.open("sub_teachers.dat", ios::binary);
	if (Teachers.fail())
		cerr << "\nNo teachers in this file\n\n";
	else {
		count = teacher_file_counter(Teachers);
		Teachers.seekg(0);
		cout << "\nTeacher name: "; cin.ignore(); cin.getline(search_name, 40);
		for (int j = 0; j < count; j++) {
			Teachers.read((char*)(&(teachers[0])), sizeof(teacher));
			if (strcmp(teachers[0].get_name(), search_name) == 0) {
				pos = j;
				break;
			}
			else
				pos = -1;
		}
		switch (pos) {
		case -1:
			test = false; break;
		default:
			test = true; break;
		}
		if (!test) {
			cout << "\nTeacher not found\n\n";
			Teachers.close();
			sub_teachers.close();
			remove("sub_teachers.dat");
		}
		if (test) {
			Teachers.seekg(0);
			for (int i = 0; i < count; i++) {
				if (i == pos)
					Teachers.seekg((i + 1) * sizeof(teacher));
				else {
					Teachers.read((char*)(&(teachers[0])), sizeof(teacher));
					sub_teachers.write((char*)(&(teachers[0])), sizeof(teacher));
				}
			}
			cout << "\nSuccessfully removed\n\n";
			Teachers.close();
			sub_teachers.close();
			remove("Teachers.dat");
			rename("sub_teachers.dat", "Teachers.dat");
		}
	}
}

void tch_menu() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC);
	cout << "Teacher management: " << endl;
	cout << "-------------------\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
	cout << "1) Input teacher information" << endl;
	cout << "2) Display teacher information" << endl;
	cout << "3) Sort teachers by age" << endl;
	cout << "4) Sort teachers by semester started" << endl;
	cout << "5) Group teachers by specialization" << endl;
	cout << "6) Search for teacher by name" << endl;
	cout << "7) Search for teacher by ID" << endl;
	cout << "+) Add teacher" << endl;
	cout << "-) Remove teacher" << endl;
	cout << "*) Update teacher information" << endl;
	cout << "f) File options" << endl;
	cout << "B) Go back" << endl;
}

void tch_file_menu() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xE);
	cout << "File options: " << endl;
	cout << "-------------\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xC0);
	cout << "Warning!! All information entered during the code's runtime are saved upon exit\n";
	cout << "End code execution to save all the info into the binary file for display\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
	cout << "1) Display from binary file" << endl;
	cout << "2) Remove student from binary file" << endl;
	cout << "B) Go back" << endl;
}

bool search_tch_binary(teacher* teachers, char name[]) {
	int count;
	ifstream tchs;
	tchs.open("Teachers.dat", ios::binary);
	count = teacher_file_counter(tchs);
	tchs.seekg(0);
	if (tchs.fail())
		return false;
	for (int i = 0; i < count; i++) {
		tchs.read((char*)(&(teachers[0])), sizeof(teacher));
		if (strcmp(name, teachers[0].get_name()) == 0) {
			return true;
		}
	}
	return false;
}

#endif _TEACHER_H_