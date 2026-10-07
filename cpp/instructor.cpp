#include "instructor.h"
#include "drivingSchool.h"
#include "student.h"

Instructor::Instructor(std::string name, std::string surname, int age, int drivingExp, Categories ctg) :Person(name, surname, age) {
	this->drivingExp = drivingExp;
	this->allowedCategory.push_back(ctg);
}
int Instructor::getExp()const {
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
std::ostream& operator<<(std::ostream& os, const Instructor& instr) {
	os << "Instructor: " << instr.getName() << " " << instr.getSurname() << ".\nAge: " << instr.age << ".\nDriving experience: " << instr.getExp() << " years.\nAuthorized for categories: ";
	for (int i = 0; i < instr.allowedCategory.size(); i++)
		os << ctgToString(instr.allowedCategory[i]) << " ";
	os << "\n--------------------------------\n";

	return os;
}
bool Instructor::operator>(const Instructor& other)const {
	return(this->drivingExp > other.getExp());
}
bool Instructor::operator<(const Instructor& other)const {
	return(this->drivingExp < other.getExp());
}
Instructor::~Instructor() {
	std::cout << "Instructor " << this->name << " " << this->surname << " has been deleted." << std::endl;
}
