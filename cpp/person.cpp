#include "person.h"
Person::Person(std::string name, std::string surname, int age) {
	this->name = name;
	this->surname = surname;
	this->age = age;
}

std::string Person::getName() const {
	return this->name;
}

std::string Person::getSurname() const {
	return this->surname;
}

int Person::getAge() const {
	return this->age;
}

Person::~Person() {
	std::cout << "Base class was deleted.\n";
}