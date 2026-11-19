#include "student.h"
#include "instructor.h"
#include "drivingSchool.h"
#include "AllExceptions.h"
#include <iomanip>

Student::Student(std::string name, std::string surname, int age, Categories category, Instructor* instructor)
	: Person(name, surname, age) {
	if (category < Categories::AM || category > Categories::I)
		throw OutOfRangeException(static_cast<int>(category), 6);

	if (instructor != nullptr && !instructor->hasCategory(category))
		throw InvalidOperationException("Assigned instructor does not have the required category.\n");

	this->category = category;
	this->instructor = instructor;
}

Categories Student::getCategory() {
	return this->category;
}

Instructor* Student::getInstructor() {
	return this->instructor;
}

void Student::setInstructor(Instructor* instr) {

	if (instr != nullptr && !instr->hasCategory(this->category)) {
		throw InvalidOperationException("Instructor " + instr->getName() + " cannot teach category " + ctgToString(this->category) + "\n");
	}
	this->instructor = instr;
}

bool Student::operator==(const Student& other) const {
	return (this->name == other.getName() && this->surname == other.getSurname());
}

bool Student::hasInstructor(Instructor* instr) {
	return this->instructor == instr;
}

void Student::showFinancialReport(float basePrice, float discount, float markup, float finalPrice) const {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "==================================================\n";
	std::cout << "         FINANCIAL RECEIPT FOR STUDENT            \n";
	std::cout << "==================================================\n";
	std::cout << "Base Price: $" << basePrice << "\n";
	if (discount > 0) std::cout << "Age Discount (Under 18): -$" << discount << "\n";
	if (markup > 0)   std::cout << "Category/Instructor Markups: +$" << markup << "\n";
	std::cout << "--------------------------------------------------\n";
	std::cout << "TOTAL TUITION FEES: $" << finalPrice << "\n";
	std::cout << "==================================================\n\n\n\n";
}

void Student::financialCalculations() const {
	float basePrice = 499.99f;
	float discount = 0, markup = 0, finalPrice = 0;

	if (this->age < 18)
		discount = basePrice * 0.20f;
	if (this->instructor != nullptr) {
		if (this->instructor->getExperience() >= 20)
			markup += 50.00f;
		else if (this->instructor->getExperience() >= 10 && this->instructor->getExperience() < 20)
			markup += 100.00f;
	}
	if (this->category == Categories::C || this->category == Categories::D)
		markup += 70.00f;
	else if (this->category == Categories::F || this->category == Categories::I)
		markup += 100.00f;
	finalPrice = basePrice - discount + markup;
	showFinancialReport(basePrice, discount, markup, finalPrice);
}

void Student::printInfo() const {
	Person::printInfo();
	std::cout << "\nDesired category: " << ctgToString(category) << "\nInstructor: ";
	if (instructor != nullptr)
		std::cout << instructor->getName() << " " << instructor->getSurname() << "." << std::endl;
	else
		std::cout << "Instructor is not assigned." << std::endl;
	financialCalculations();
}

std::ostream& operator<<(std::ostream& os, Student& stud) {
	stud.printInfo();
	return os;
}

std::istream& operator>>(std::istream& is, Student& stud) {
	std::string tempName, tempSurname;
	if (!(is >> tempName >> tempSurname)) {
		is.clear();
		is.ignore(100, '\n');
		throw InvalidDataException("Failed to read student's first and last name.\n");
	}
	stud.setName(tempName);
	stud.setSurname(tempSurname);
	return is;
}

std::string Student::getType() const {
	return "Student";
}

Student::~Student() {
	std::cout << "Student " << this->name << " " << this->surname << " has been deleted." << std::endl;
}