#include "drivingSchool.h"

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
bool Instructor::operator>(const Instructor& other)const {
	return(this->drivingExp > other.drivingExp);
}
bool Instructor::operator<(const Instructor& other)const {
	return(this->age <= other.age);
}
//std::ostream& operator<<(std::ostream& os, const Instructor& instr) {
//	os<< "Instructor: " << instr.name << " " << instr.surname << ".\nAge: " << instr.age << ".\nDriving experience: " << instr.drivingExp << " years.\nAuthorized for categories: ";
//	for (int i = 0; i < instr.allowedCategory.size(); i++)
//		os << ctgToString(instr.allowedCategory[i]) << " ";
//	os << "\n--------------------------------\n\n";
//}
//std::istream& operator>>(std::istream& is, const Instructor& instr) {
//
//}
Instructor::~Instructor() {
	std::cout << "Instructor " << this->name << " " << this->surname << " has been deleted." << std::endl;
}
