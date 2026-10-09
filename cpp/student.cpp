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

std::ostream& operator<<(std::ostream& os, Student& stud) {
	os << "Student: " << stud.getName() << " " << stud.getSurname() << ".\nAge: " << stud.getAge() << ".\nDesired category: " << ctgToString(stud.category) << ".\nAssigned instructor: ";
	if (stud.instructor != nullptr)
		os << stud.instructor->getName() << " " << stud.instructor->getSurname() << "." << std::endl;
	else
		os << "not assigned." << std::endl;
	os << "--------------------------------" << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Student& stud) {
	std::string tempName, tempSurname;
	is >> tempName >> tempSurname;
	stud.name = tempName;
	stud.surname = tempSurname;
	return is;
}

Student::~Student() {
	std::cout << "Student " << this->name << " " << this->surname << " has been deleted." << std::endl;
}
