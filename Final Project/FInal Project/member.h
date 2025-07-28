#ifndef _MEMBER_H_
#define _MEMBER_H_

#include "date.h"
#include <cstring>
#include <windows.h>
#include <iomanip>
#include <fstream>

//semester structure (season-year)
struct semester {
	int year;
	char season[20];
};

//function comparing 2 semesters (newest and oldest)
int semester_comp(semester*, semester*);

class member {
protected:
	int id;
	date birth;
	semester started;
	char gender, name[40];
public:
	member() {
		id = 0;
		gender = 'N';
		started.year = 2023;
		strcpy_s(name, "N/A");
		strcpy_s(started.season, "Fall");
	}
	//getter function to return member name
	char* get_name() {
		return name;
	}
};

int semester_comp(semester* s1, semester* s2) {
	if (s1->year > s2->year)
		return 1;
	else
		if (s1->year < s2->year)
			return -1;
		else
			if (strcmp(s1->season, s2->season) == -1)
				return -1;
			else
				if (strcmp(s1->season, s2->season) == 1)
					return 1;
				else
					return 0;
}

#endif _MEMBER_H_