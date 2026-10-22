#include "person.h"
Person::Person(std::string name, std::string surname, int age) {
	this->name = name;
	this->surname = surname;
	this->age = age;
}

std::string Person::getName() const{
	return this->name;
}

std::string Person::getSurname() const {
	return this->surname;
}

int Person::getAge() const {
	return this->age;
}
void Person::setName(std::string name) {
	this->name = name;
}
void Person::setSurname(std::string surname) {
	this->surname = surname;
}
void Person::printInfo() const {
	std::cout << "Name: " << name << " " << surname << ".\nAge: " << age << ".";
}

Person::~Person() {
	std::cout << "Base class Person was deleted.\n";
}