#pragma once
#include "person.h"
#include <string>
#include <iostream>
class Instructor;
class DrivingSchool;
enum Categories;

class Student : public Person{
private:
	Categories myCategory;
	Instructor* myInstructor;
public:
	Student(std::string name, std::string surname, int age, Categories myCategory, Instructor* myInstructor = nullptr);

	Categories getMyCategory();
	Instructor* getInstructor();

	bool operator==(const Student& other)const;

	void setInstructor(Instructor* instr);
	friend std::istream& operator>>(std::istream& is,Student & stud);
	friend std::ostream& operator<<(std::ostream& os, Student& stud);

	~Student();
};
