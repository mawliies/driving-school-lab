#pragma once
#include <string>
#include <vector>
#include <iostream>
class Instructor;
class Student;
class Admin;
enum Categories {
	AM, A, B, C, D, F, I
};
std::string ctgToString(Categories ctg);

class DrivingSchool {
private:
	std::vector<Instructor*> instructors;
	std::vector<Student*> students;
	std::vector<Admin*> admins;
public:
	DrivingSchool(Instructor* instr = nullptr, Student* stud = nullptr, Admin* adm = nullptr);

	friend class Admin;
	DrivingSchool& operator+=(Student* stud);
	DrivingSchool& operator+=(Instructor* instr);
	DrivingSchool& operator+=(Admin* adm);
	DrivingSchool& operator-=(Student* stud);
	DrivingSchool& operator-=(Instructor* instr);
	friend void defining(DrivingSchool& school, Student* stud);
	void registration();
	void profile(Student* stud);
	void findStudent();
	void printAllInstr();
	void loginAdmin();
	void statistics();

	~DrivingSchool();
};

void defining(DrivingSchool& school, Student* stud);
bool checkAge(int age, int newCategoryNum);
void menu(DrivingSchool& school);
void test(DrivingSchool& school);
