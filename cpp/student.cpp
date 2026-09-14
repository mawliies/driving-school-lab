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
void Student::printInfo() {
	std::cout << "Student: " << this->name << " " << this->surname << ".\nAge: " << this->age << ".\nDesired category: " << ctgToString(this->myCategory) << ".\nAssigned instructor: ";
	if (this->myInstructor != nullptr)
		std::cout << this->myInstructor->getName() << " " << this->myInstructor->getSurname() << "." << std::endl;
	else
		std::cout << "not assigned." << std::endl;
	std::cout << "--------------------------------" << std::endl;
	system("pause");
}
Student::~Student() {
	std::cout << "Student " << this->name << " " << this->surname << " has been deleted." << std::endl;
}
