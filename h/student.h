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

	bool operator==(const Student& other)const;

	void setInstructor(Instructor* instr);
	void printInfo();
	/*friend std::ostream& operator<<(std::ostream& os, const Student& stud);
	friend std::istream& operator>>(std::istream & is, const Student & stud);*/

	~Student();
};
