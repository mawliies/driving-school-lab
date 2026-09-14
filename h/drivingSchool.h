#pragma once
#include "instructor.h"
#include "student.h"

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

	void registrInstructor(Instructor* instr);
	void registrStudent(Student* stud);
	void defining(Student* stud);
	void registration();
	void profile(Student* stud);
	void findStudent();
	void admin();
	void adminDelS();
	void adminDelI();
	void adminAddS();
	void adminAddI();
	void printAllInstr();

	~DrivingSchool();
};

void menu(DrivingSchool& school);
void test(DrivingSchool& school);
