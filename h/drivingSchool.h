#pragma once
#include <string>
#include <vector>
#include <iostream>
class Instructor;
class Student;

enum Categories {
	AM, A, B, C, D, F, I
};
std::string ctgToString(Categories ctg);

class DrivingSchool {
private:
	std::vector<Instructor*> instructors;
	std::vector<Student*> students;
public:
	DrivingSchool(Instructor* instr = nullptr, Student* stud = nullptr);

	DrivingSchool& operator+=(Student* stud);
	DrivingSchool& operator+=(Instructor* instr);
	DrivingSchool& operator-=(int index);
	friend void defining(DrivingSchool& school, Student* stud);
	void registration();
	void profile(Student* stud);
	void findStudent();
	void admin();
	void adminDelS();
	void adminDelI();
	void adminAddS();
	void adminAddI();
	void printAllInstr();
	void printAllStud();
	void statistics();

	~DrivingSchool();
};
void defining(DrivingSchool& school, Student* stud);
void menu(DrivingSchool& school);
void test(DrivingSchool& school);
