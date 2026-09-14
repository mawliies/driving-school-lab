#pragma once
#include "instructor.h"

class Instructor;
class Student {
private:
	std::string name;
	std::string surname;
	int age;
	Categories myCategory;
	Instructor* myInstructor;
public:
	Student(std::string name, std::string surname, int age, Categories myCategory, Instructor* myInstructor = nullptr);

	std::string getName();
	std::string getSurname();
	int getAge();
	Categories getMyCategory();
	Instructor* getInstructor();

	void setInstructor(Instructor* instr);
	void printInfo();

	~Student();
};
