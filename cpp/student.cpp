#include "student.h"
#include "instructor.h"
#include "drivingSchool.h"

Student::Student(std::string name, std::string surname, int age, Categories category, Instructor* instructor) :Person(name, surname, age) {
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
	this->instructor = instr;
}

bool Student::operator==(const Student& other)const {
	return(this->name == other.getName() && this->surname == other.getSurname());
}

bool Student::hasInstructor(Instructor* instr) {
	if (this->instructor == instr)
		return true;
	return false;
}
void Student::printInfo()const {
	Person::printInfo();
	std::cout << "\nDesired category: " << ctgToString(category)<<"\nInstructor: ";
	if (instructor != nullptr)
		std::cout << instructor->getName() << " " << instructor->getSurname() << "." << std::endl;
	else
		std::cout << "Instructor is not assigned." << std::endl;
	std::cout << "--------------------------------" << std::endl;
}
std::ostream& operator<<(std::ostream& os, Student& stud) {
	stud.printInfo();
	return os;
}

std::istream& operator>>(std::istream& is, Student& stud) {
	std::string tempName, tempSurname;
	is >> tempName >> tempSurname;
	stud.setName(tempName);
	stud.setSurname(tempSurname);
	return is;
}
std::string Student:: getType()const {
	return "Student";
}

void Student::specific()const {
	//?
}

Student::~Student() {
	std::cout << "Student " << this->name << " " << this->surname << " has been deleted." << std::endl;
}
