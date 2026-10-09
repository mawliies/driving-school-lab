#pragma once
#include <iostream>
#include <string>
#include "person.h"
class DrivingSchool;
class Admin :public Person {
private:
	int password;
public:
	Admin(std::string name, std::string surname, int age, int password);

	int getPassword();
	bool truePassword(int pass);
	void admin(DrivingSchool& school);
	void DeleteStudent(DrivingSchool& school);
	void DeleteInstructor(DrivingSchool& school);
	void AddStudent(DrivingSchool& school);
	void AddInstructor(DrivingSchool& school);
	void printAllStudents(DrivingSchool& school);

	~Admin();
};