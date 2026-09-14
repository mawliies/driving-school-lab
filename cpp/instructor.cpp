#include "C:\labs\2k\DrivingSchool\DrivingSchool\h\drivingSchool.h"

Instructor::Instructor(std::string name, std::string surname, int age, int drivingExp, Categories ctg) {
	this->name = name;
	this->surname = surname;
	this->age = age;
	this->drivingExp = drivingExp;
	this->allowedCategory.push_back(ctg);
}
std::string Instructor::getName() {
	return this->name;
}
std::string Instructor::getSurname() {
	return this->surname;
}
int Instructor::getExp() {
	return this->drivingExp;
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
void Instructor::printInfo() {
	std::cout << "Instructor: " << this->name << " " << this->surname << ".\nAge: " << this->age << ".\nDriving experience: " << this->drivingExp << " years.\nAuthorized for categories: ";
	for (int i = 0; i < this->allowedCategory.size(); i++)
		std::cout << ctgToString(allowedCategory[i]) << " ";
	std::cout << "\n--------------------------------\n" << std::endl;
}
Instructor::~Instructor() {
	std::cout << "Instructor " << this->name << " " << this->surname << " has been deleted." << std::endl;
}
