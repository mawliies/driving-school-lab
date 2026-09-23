#pragma once
#include <string>
#include <vector>
#include <iostream>
class Instructor;
class DrivingSchool;
enum Categories;

class Student {
private:
	std::string name;
	std::string surname;
	int age;
	Categories myCategory;
	Instructor* myInstructor;
	friend void defining(DrivingSchool& school, Student* stud);
public:
	Student(std::string name, std::string surname, int age, Categories myCategory, Instructor* myInstructor = nullptr);

	std::string getName();
	std::string getSurname();
	int getAge();
	Categories getMyCategory();
	Instructor* getInstructor();

	
	bool operator==(const Student& other)const;

	void setInstructor(Instructor* instr);
	friend std::istream& operator>>(std::istream& is,Student & stud);
	friend std::ostream& operator<<(std::ostream& os, Student& stud);

	~Student();
};
