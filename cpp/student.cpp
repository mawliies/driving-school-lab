#include "student.h"
#include "instructor.h"
#include "drivingSchool.h"

Student::Student(std::string name, std::string surname, int age, Categories myCategory, Instructor* myInstructor) {
	this->name = name;
	this->surname = surname;
	this->age = age;
	this->myCategory = myCategory;
	this->myInstructor = myInstructor;
}
std::string Student::getName() {
	return this->name;
}
std::string Student::getSurname() {
	return this->surname;
}
int Student::getAge() {
	return this->age;
}
Categories Student::getMyCategory() {
	return this->myCategory;
}
Instructor* Student::getInstructor() {
	return this->myInstructor;
}
void Student::setInstructor(Instructor* instr) {
	this->myInstructor = instr;
}
bool Student::operator==(const Student& other)const {
	return(this->name == other.name && this->surname == other.surname);
}
std::ostream& operator<<(std::ostream& os, Student& stud) {
	os << "Student: " << stud.name << " " << stud.surname << ".\nAge: " << stud.age << ".\nDesired category: " << ctgToString(stud.myCategory) << ".\nAssigned instructor: ";
	if (stud.myInstructor != nullptr)
		os << stud.myInstructor->getName() << " " << stud.myInstructor->getSurname() << "." << std::endl;
	else
		os << "not assigned." << std::endl;
	os << "--------------------------------" << std::endl;
	return os;
}
std::istream& operator>>(std::istream& is, Student& stud) {
	is >> stud.name;
	is >> stud.surname;
	return is;
}
Student::~Student() {
	std::cout << "Student " << this->name << " " << this->surname << " has been deleted." << std::endl;
}
