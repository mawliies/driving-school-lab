#include "instructor.h"
#include "drivingSchool.h"
#include "student.h"
#include <iomanip>

Instructor::Instructor(std::string name, std::string surname, int age, int drivingExperience, Categories ctg) :Person(name, surname, age) {
	this->drivingExperience = drivingExperience;
	this->allowedCategory.push_back(ctg);
}

int Instructor::getExperience()const {
	return this->drivingExperience;
}

void Instructor::addCategory(Categories owned) {
	this->allowedCategory.push_back(owned);
}

bool Instructor::hasCategory(Categories ctg) {
	for (int i = 0; i < allowedCategory.size(); i++)
		if (allowedCategory[i] == ctg)
			return true;
	return false;
}
void Instructor::printInfo()const {
	Person::printInfo();
	std::cout << "\nDriving experience: " << drivingExperience << ".\nOwned categories: ";
	for (int i = 0; i < allowedCategory.size(); i++)
		std::cout << ctgToString(allowedCategory[i]) << " ";
	std::cout << "\n--------------------------------\n";
}
std::ostream& operator<<(std::ostream& os, const Instructor& instr) {
	instr.printInfo();
	return os;
}

bool Instructor::operator>(const Instructor& other)const {
	return(this->drivingExperience > other.getExperience());
}

bool Instructor::operator<(const Instructor& other)const {
	return(this->drivingExperience < other.getExperience());
}
std::string Instructor::getType()const {
	return "Instructor";
}
void Instructor::salaryCalculation(float baseSalary, float experienceBonus, float categoryBonus, float salary)const {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "\n==================================================\n";
	std::cout << "         PAYSLIP FOR INSTRUCTOR                   \n";
	std::cout << "==================================================\n";
	std::cout << "Instructor: " << this->name << " " << this->surname << "\n";
	std::cout << "Base Salary: $" << baseSalary << "\n";
	std::cout << "Experience Bonus (" << this->drivingExperience << " years): +$" << experienceBonus << "\n";
	std::cout << "Categories Bonus (" << this->allowedCategory.size() << " opened): +$" << categoryBonus << "\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "TOTAL NET SALARY: $" << salary << "\n";
	std::cout << "==================================================\n\n\n\n";
}

void Instructor::financialCalculations()const {
	float baseSalary = 800.00;
	float experienceBonus = this->getExperience() * 15.00;
	float categoryBonus = this->allowedCategory.size() * 35.00;
	float salary = baseSalary + experienceBonus + categoryBonus;

	salaryCalculation(baseSalary, experienceBonus, categoryBonus, salary);
}
Instructor::~Instructor() {
	std::cout << "Instructor " << this->name << " " << this->surname << " has been deleted." << std::endl;
}
