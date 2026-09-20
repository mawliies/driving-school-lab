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

	bool operator>(const Instructor& other)const;
	bool operator<(const Instructor& other)const;
	friend std::ostream& operator<<(std::ostream& os, const Instructor& instr);
	friend std::istream& operator>>(std::istream& is, Instructor& instr);

	~Instructor();
};
