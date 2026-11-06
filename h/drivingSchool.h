#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Collection.h"
class Person;
class Instructor;
class Student;
class Admin;
enum Categories {
	AM, A, B, C, D, F, I
};
std::string ctgToString(Categories ctg);

class DrivingSchool {
private:
	Collection<Person*> members;
	friend class Admin;
public:
	DrivingSchool();
	
	DrivingSchool& operator+=(Person* newMember);
	DrivingSchool& operator-=(Person* newMember);
	friend void defining(DrivingSchool& school, Student* stud);
	Collection<Person*>& getMembers();
	void registration();
	void profile(Student* stud);
	void findStudent();
	void printAllInstructors();
	void information();
	void loginAdmin();
	void statistics();

	~DrivingSchool();
};

void defining(DrivingSchool& school, Student* stud);
bool checkAge(int age, int newCategoryNum);
void menu(DrivingSchool& school);
void test(DrivingSchool& school);
