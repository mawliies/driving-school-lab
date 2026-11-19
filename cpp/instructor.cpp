#include "instructor.h"
#include "drivingSchool.h"
#include "student.h"
#include "AllExceptions.h"
#include <iomanip>

Instructor::Instructor(std::string name, std::string surname, int age, int drivingExperience, Categories ctg)
	: Person(name, surname, age) {
	if (age < 18)
		throw AgeRestrictionException("Instructor must be at least 18 years old.\n");
	if (drivingExperience < 0 || drivingExperience >(age - 18))
		throw InvalidDataException("Invalid driving experience (" + std::to_string(drivingExperience) + " years) for age " + std::to_string(age) + ".\n");
	if (ctg < Categories::AM || ctg > Categories::I)
		throw OutOfRangeException(static_cast<int>(ctg), 6);

	this->drivingExperience = drivingExperience;
	this->allowedCategory.add(ctg);
}

int Instructor::getExperience() const {
	return this->drivingExperience;
}

void Instructor::addCategory(Categories owned) {
	if (owned < Categories::AM || owned > Categories::I)
		throw OutOfRangeException(static_cast<int>(owned), 6);

	if (this->hasCategory(owned))
		throw InvalidOperationException("Category " + ctgToString(owned) + " is already assigned to this instructor.\n");

	this->allowedCategory.add(owned);
}

bool Instructor::hasCategory(Categories ctg) {
	for (int i = 0; i < allowedCategory.getSize(); i++) {
		if (allowedCategory.get(i) == ctg)
			return true;
	}
	return false;
}

void Instructor::printInfo() const {
	Person::printInfo();
	std::cout << "\nDriving experience: " << drivingExperience << ".\nOwned categories: ";
	for (int i = 0; i < allowedCategory.getSize(); i++)
		std::cout << ctgToString(allowedCategory.get(i)) << " ";
	std::cout << "\n--------------------------------\n";
}

std::ostream& operator<<(std::ostream& os, const Instructor& instr) {
	instr.printInfo();
	return os;
}

bool Instructor::operator>(const Instructor& other) const {
	return (this->drivingExperience > other.getExperience());
}

bool Instructor::operator<(const Instructor& other) const {
	return (this->drivingExperience < other.getExperience());
}

std::string Instructor::getType() const {
	return "Instructor";
}

void Instructor::salaryCalculation(float baseSalary, float experienceBonus, float categoryBonus, float salary) const {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "\n==================================================\n";
	std::cout << "         PAYSLIP FOR INSTRUCTOR                   \n";
	std::cout << "==================================================\n";
	std::cout << "Instructor: " << this->name << " " << this->surname << "\n";
	std::cout << "Base Salary: $" << baseSalary << "\n";
	std::cout << "Experience Bonus (" << this->drivingExperience << " years): +$" << experienceBonus << "\n";
	std::cout << "Categories Bonus (" << this->allowedCategory.getSize() << " opened): +$" << categoryBonus << "\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "TOTAL NET SALARY: $" << salary << "\n";
	std::cout << "==================================================\n\n\n\n";
}

void Instructor::financialCalculations() const {
	float baseSalary = 800.00f;
	float experienceBonus = this->getExperience() * 15.00f;
	float categoryBonus = this->allowedCategory.getSize() * 35.00f;
	float salary = baseSalary + experienceBonus + categoryBonus;

	salaryCalculation(baseSalary, experienceBonus, categoryBonus, salary);
}

Instructor::~Instructor() {
	std::cout << "Instructor " << this->name << " " << this->surname << " has been deleted." << std::endl;
}