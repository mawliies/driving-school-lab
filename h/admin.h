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
	void adminDelS(DrivingSchool& school);
	void adminDelI(DrivingSchool& school);
	void adminAddS(DrivingSchool& school);
	void adminAddI(DrivingSchool& school);
	void printAllStud(DrivingSchool& school);

	~Admin();
};