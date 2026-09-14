#pragma once
#include <string>
#include <vector>
#include <iostream>

enum Categories;
class Instructor {
private:
	std::string name;
	std::string surname;
	int age;
	int drivingExp;
	std::vector<Categories> allowedCategory;
public:
	Instructor(std::string name, std::string surname, int age, int drivingExp, Categories ctg);

	std::string getName();
	std::string getSurname();
	int getExp();

	void addCategory(Categories owned);
	bool hasCategory(Categories ctg);
	void printInfo();

	~Instructor();
};
