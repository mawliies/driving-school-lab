#pragma once
#include "person.h"
#include <string>
#include <vector>
#include <iostream>

class Student;
class DrivingSchool;
enum Categories;

class Instructor :public Person {
private:
	int drivingExperience;
	std::vector<Categories> allowedCategory;
public:
	Instructor(std::string name, std::string surname, int age, int drivingExperience, Categories category);

	int getExperience()const;
	void addCategory(Categories owned);
	bool hasCategory(Categories ctg);
	bool operator>(const Instructor& other)const;
	bool operator<(const Instructor& other)const;
	friend std::ostream& operator<<(std::ostream& os, const Instructor& instructor);

	~Instructor();
};
