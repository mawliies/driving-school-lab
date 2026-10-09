#pragma once
#include "person.h"
#include <string>
#include <iostream>
class Instructor;
class DrivingSchool;
enum Categories;

class Student : public Person{
private:
	Categories category;
	Instructor* instructor;
public:
	Student(std::string name, std::string surname, int age, Categories category, Instructor* instructor = nullptr);

	Categories getCategory();
	Instructor* getInstructor();
	bool operator==(const Student& other)const;
	bool hasInstructor(Instructor* instr);
	void setInstructor(Instructor* instr);
	friend std::istream& operator>>(std::istream& is,Student & stud);
	friend std::ostream& operator<<(std::ostream& os, Student& stud);

	~Student();
};
