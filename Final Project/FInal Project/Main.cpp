//including header files
#include "schedule.h"
#include "students.h"
#include "teachers.h"

int main() {
	//sets system color to white
	system("color 7");
	char search_name[40], binary_search[40];
	int std_add = 0, tch_add = 0, c1 = 0, c2 = 0;
	int std_num = 0, tch_num = 0, search_id, sub = -1, pos1 = -1, n;
	student* students;
	teacher* teachers;
	//array of teachers containing a maximum of 500 teachers
	teachers = new teacher[500];
	//array of students containing a maximum of 1000 students
	students = new student[1000];
	char main_action, std_action, tch_action, sch_action, file_action;
	int CCE = 0, MCE = 0, BFE = 0, BME = 0, CME = 0;
	char yon1, action, choice;
	//schedule object
	schedule s;
	//changes color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9);
	cout << "Manage your university\n";
	cout << "----------------------\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
	main_menu();
	cout << "\n-->";
	cin >> main_action;
	//loops main menu
	while (main_action != 'T') {
		//switch operation for main menu
		switch (main_action) {
		case'1':
			system("cls");
			std_menu();
			cout << "\n-->";
			cin >> std_action;
			//loops student menu
			while (std_action != 'B') {
				//switch operation for student menu
				switch (std_action) {
				case '1':
					if (c1 >= 1) {
						delete[]students;
						students = new student[1000];
						cout << "\a\nAttention! You are about to override previously saved info...\n";
						do {
							cout << "Do you still wish to proceed?(y/n) ";
							cin >> yon1;
						} while (yon1 != 'y' && yon1 != 'n');
						switch (yon1) {
						case 'y':
							cout << "\nEnter number of students to register: ";
							cin >> std_num;
							while (cin.fail() || std_num < 1 || std_num > 1000) {
								cin.clear(); cin.ignore(INT_MAX, '\n');
								cout << "\nEnter number of students to register: ";
								cin >> std_num;
							}
							cout << "\n";
							input_all_stds(students, std_num + std_add);
							c1++;
							break;
						case 'n':
							break;
						}
					}
					else {
						cout << "\nEnter number of students to register: ";
						cin >> std_num;
						while (cin.fail() || std_num < 1 || std_num > 1000) {
							cin.clear(); cin.ignore(INT_MAX, '\n');
							cout << "\nEnter number of students to register: ";
							cin >> std_num;
						}
						cout << "\n";
						input_all_stds(students, std_num + std_add);
						c1++;
					}
					system("pause");
					system("cls");
					break;
				case '2':
					cout << "\n";
					display_all_stds(students, std_num + std_add);
					system("pause");
					system("cls");
					break;
				case '3':
					cout << "\n";
					sort_by_credits(students, std_num + std_add);
					system("pause");
					system("cls");
					break;
				case'4':
					cout << "\n";
					sort_by_semester(students, std_num + std_add);
					system("pause");
					system("cls");
					break;
				case '5':
					cout << "\n";
					group_by_major(students, std_num + std_add);
					system("pause");
					system("cls");
					break;
				case '6':
					cout << "\n";
					group_by_year(students, std_num + std_add);
					system("pause");
					system("cls");
					break;
				case '7':
					pos1 = -1;
					cout << "\n";
					cout << "\nSearch for student: ";
					cin.ignore();
					cin.getline(search_name, 40);
					if (searchstd_by_name(students, std_num + std_add, pos1, search_name)) {
						cout << "\nStudent found\n\n";
						cout << students[pos1] << endl;
					}
					else
						cout << "\nStudent not found\n\n";
					system("pause");
					system("cls");
					break;
				case '8':
					pos1 = -1;
					cout << "\nSearch for student: ";
					cin >> search_id;
					if (searchstd_by_id(students, std_num + std_add, pos1, search_id)) {
						cout << "\nStudent found\n\n";
						cout << students[pos1] << endl;
					}
					else
						cout << "\nStudent not found\n\n";
					system("pause");
					system("cls");
					break;
				case '+':
					cout << "\n";
					add_std(students, std_num + std_add, std_add);
					system("pause");
					system("cls");
					break;
				case '-':
					cout << "\n";
					remove_std(students, std_num + std_add, std_add);
					system("pause");
					system("cls");
					break;
				case '*':
					cout << "\n";
					update_std_info(students, std_num + std_add);
					system("pause");
					system("cls");
					break;
				case 'f':
					cout << "\n";
					system("cls");
					std_file_menu();
					cout << "\n-->";
					cin >> file_action;
					//loops student file menu 
					while (file_action != 'B') {
						//switch operation for student file menu
						switch (file_action) {
						case '1':
							display_std_binary(students);
							system("pause");
							system("cls");
							break;
						case '2':
							remove_std_binary(students);
							system("pause");
							system("cls");
							break;
						case '3':
							char major_search[20];
							cout << "Search for major: ";
							cin.ignore();
							cin.getline(major_search, 20);
							cout << "\n";
							display_std_binary_major(students, major_search);
							system("pause");
							system("cls");
							break;
						case 'B':
							break;
						}
						system("cls");
						std_file_menu();
						cout << "\n-->";
						cin >> file_action;
					}
					break;
				case 'B':
					break;
				}
				system("cls");
				std_menu();
				cout << "\n-->";
				cin >> std_action;
			}
			break;
		case '2':
			system("cls");
			tch_menu();
			cout << "\n-->";
			cin >> tch_action;
			//loops teacher menu
			while (tch_action != 'B') {
				//switch operation for teacher menu
				switch (tch_action) {
				case '1':
					if (c2 >= 1) {
						delete[]teachers;
						teachers = new teacher[500];
						cout << "\a\nAttention! You are about to override previously saved info...\n";
						do {
							cout << "Do you still wish to proceed?(y/n) ";
							cin >> yon1;
						} while (yon1 != 'y' && yon1 != 'n');
						switch (yon1) {
						case 'y':
							cout << "\nEnter number of teachers to register: ";
							cin >> tch_num;
							while (cin.fail() || tch_num < 1 || tch_num > 500) {
								cin.clear(); cin.ignore(INT_MAX, '\n');
								cout << "\nEnter number of teachers to register: ";
								cin >> tch_num;
							}
							cout << "\n";
							input_all_tchs(teachers, tch_num + tch_add);
							c2++;
							break;
						case 'n':
							break;
						}
					}
					else {
						cout << "\nEnter number of teachers to register: ";
						cin >> tch_num;
						while (cin.fail() || tch_num < 1 || tch_num > 500) {
							cin.clear(); cin.ignore(INT_MAX, '\n');
							cout << "\nEnter number of teachers to register: ";
							cin >> tch_num;
						}
						cout << "\n";
						input_all_tchs(teachers, tch_num + tch_add);
						c2++;
					}
					system("pause");
					system("cls");
					break;
				case '2':
					cout << "\n";
					display_all_tchs(teachers, tch_num + tch_add);
					system("pause");
					system("cls");
					break;
				case '3':
					cout << "\n";
					sort_by_age_tch(teachers, tch_num + tch_add);
					system("pause");
					system("cls");
					break;
				case'4':
					cout << "\n";
					sort_by_semester(teachers, tch_num + tch_add);
					system("pause");
					system("cls");
					break;
				case '5':
					cout << "\n";
					group_by_specialization(teachers, tch_num + tch_add);
					system("pause");
					system("cls");
					break;
				case '6':
					pos1 = -1;
					cout << "\n";
					cout << "\nSearch for teacher: ";
					cin.ignore();
					cin.getline(search_name, 40);
					if (searchtch_by_name(teachers, tch_num + tch_add, pos1, search_name)) {
						cout << "\nTeacher found\n\n";
						cout << teachers[pos1] << endl;
					}
					else
						cout << "\nTeacher not found\n\n";
					system("pause");
					system("cls");
					break;
				case '7':
					pos1 = -1;
					cout << "\nSearch for teacher: ";
					cin >> search_id;
					if (searchtch_by_id(teachers, tch_num + tch_add, pos1, search_id)) {
						cout << "\nTeacher found\n\n";
						cout << teachers[pos1] << endl;
					}
					else
						cout << "\nTeacher not found\n\n";
					system("pause");
					system("cls");
					break;
				case '+':
					cout << "\n";
					add_tch(teachers, tch_num + tch_add, tch_add);
					system("pause");
					system("cls");
					break;
				case '-':
					cout << "\n";
					remove_tch(teachers, tch_num + tch_add, tch_add);
					system("pause");
					system("cls");
					break;
				case '*':
					cout << "\n";
					update_tch_info(teachers, tch_num + tch_add);
					system("pause");
					system("cls");
					break;
				case 'f':
					cout << "\n";
					system("cls");
					tch_file_menu();
					cout << "\n-->";
					cin >> file_action;
					//loops teacher file menu
					while (file_action != 'B') {
						//switch operation for teacher file menu
						switch (file_action) {
						case '1':
							display_tch_binary(teachers);
							system("pause");
							system("cls");
							break;
						case '2':
							remove_tch_binary(teachers);
							system("pause");
							system("cls");
							break;
						case 'B':
							break;
						}
						system("cls");
						tch_file_menu();
						cout << "\n-->";
						cin >> file_action;
					}
				case 'B':
					break;
				}
				system("cls");
				tch_menu();
				cout << "\n-->";
				cin >> tch_action;
			}
			break;
		case '3':
			system("cls");
			sch_menu();
			cout << "\n-->";
			cin >> sch_action;
			//loops schedule menu
			while (sch_action != 'B') {
				//switch operation for schedule menu
				switch (sch_action) {
				case '1':
					do {
						cout << "\nSearch in binary file(b) or in recently added information(r)? ";
						cin >> action;
					} while (action != 'b' && action != 'r');
					switch (action) {
					case 'b':
						cout << "\nStudent name: ";
						cin.ignore();
						cin.getline(binary_search, 40);
						if (search_std_binary(students, binary_search)) {
							cout << "\n";
							cin >> s;
							text_schedule(s, binary_search);
						}
						else
							cout << "\nStudent not found\n\n";
						break;
					case 'r':
						cout << "\nStudent name: ";
						cin.ignore();
						cin.getline(binary_search, 40);
						if (searchstd_by_name(students, std_num + std_add, sub, binary_search)) {
							cout << "\n";
							cin >> s;
							text_schedule(s, binary_search);
						}
						else
							cout << "\nStudent not found\n\n";
						break;
					}
					break;
				case '2':
					do {
						cout << "\nSearch in binary file(b) or in recently added information(r)? ";
						cin >> action;
					} while (action != 'b' && action != 'r');
					switch (action) {
					case 'b':
						cout << "\nTeacher name: ";
						cin.ignore();
						cin.getline(binary_search, 40);
						if (search_tch_binary(teachers, binary_search)) {
							cout << "\n";
							cin >> s;
							text_schedule(s, binary_search);
						}
						else
							cout << "\nTeacher not found\n\n";
						break;
					case 'r':
						cout << "\nTeacher name: ";
						cin.ignore();
						cin.getline(binary_search, 40);
						if (searchtch_by_name(teachers, tch_num + tch_add, sub, binary_search)) {
							cout << "\n";
							cin >> s;
							text_schedule(s, binary_search);
						}
						else
							cout << "\nTeacher not found\n\n";
						break;
					}
					break;
				case '3':
					cout << "\nStudent/Teacher name: ";
					cin.ignore();
					cin.getline(binary_search, 40);
					if (read_from_file(binary_search)) {
						cout << "\n\nOutput successfull\n" << endl;
					}
					else
						cout << "\nNot found\n\n";
					break;
				}
				system("pause");
				system("cls");
				sch_menu();
				cout << "\n-->";
				cin >> sch_action;
			}
			break;
		case 'T':
			break;
		default:
			cout << "\nInavlid search option\n\n";
			break;
		}
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x9);
		cout << "Manage your university\n";
		cout << "----------------------\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);
		main_menu();
		cout << "\n-->";
		cin >> main_action;
	}
	for (int i = 0; i < std_num + std_add; i++) {
		check_major(students[i].get_major(), CCE, MCE, CME, BFE, BME);
	}
	//number of majors chosen
	n = CCE + MCE + BME + BFE + CME;
	//inputs information into binary files
	if ((std_num + std_add) > 0) {
		input_std_binary(students, std_num + std_add);
		for (int i = 0; i < n; i++) { //add major counter function
			input_std_binary_major(students, std_num + std_add, students[i].get_major());
		}
	}
	if ((tch_num + tch_add) > 0) {
		input_tch_binary(teachers, tch_num + tch_add);
	}
	//deletes arrays
	delete[]students;
	delete[]teachers;
}