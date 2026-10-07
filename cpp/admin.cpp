#include "admin.h"
#include "drivingSchool.h"
#include "student.h"
#include "instructor.h"

Admin::Admin(std::string name, std::string surname, int age, int password) :Person(name, surname, age) {
	this->password = password;
}
int Admin::getPassword() {
	return this->password;
}
bool Admin::truePassword(int pass) {
	return this->password == pass;
}
void Admin::adminDelS(DrivingSchool& school) {	//
	int num;
	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	for (int i = 0; i < school.students.size(); i++)
		std::cout << i + 1 << ". " << school.students[i]->getName() << " " << school.students[i]->getSurname() << std::endl;
	std::cout << "Enter student number: ";
	std::cin >> num;
	if (num > 0 && num <= school.students.size())
		school -= school.students[num - 1];
}

void Admin::adminDelI(DrivingSchool& school) {
	int num;

	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	for (int i = 0; i < school.instructors.size(); i++)
		std::cout << i + 1 << ". " << school.instructors[i]->getName() << " " << school.instructors[i]->getSurname() << std::endl;
	std::cout << "Enter instructor number: ";
	std::cin >> num;
	if (num > 0 && num <= school.instructors.size()) {
		Instructor* toDel = school.instructors[num - 1];
		for (int i = 0; i < school.students.size(); i++)
			if (school.students[i]->getInstructor() != nullptr && school.students[i]->getInstructor() == toDel)
				school.students[i]->setInstructor(nullptr);
		school -= toDel;
	}

}

void Admin::adminAddS(DrivingSchool& school) {
	std::string newName = "Lady", newSurname = "Gaga";
	int newAge = 17, newCategoryNum = 2;

	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Enter student's first and last name: " << std::endl;
	std::cout << "[AUTO] " << newName << " " << newSurname << "." << std::endl;
	std::cout << "\nEnter student's age: " << std::endl;
	std::cout << "[AUTO] " << newAge << "." << std::endl;
	if (newAge < 16) {
		std::cout << "\nRegistration failed: Student must be at least 16 years old to register!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		return;
	}
	std::cout << "\nEnter student's desired license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	std::cout << "[AUTO] " << newCategoryNum << "." << std::endl;
	if (((newAge < 18 && newAge >= 16) && newCategoryNum != 1)) {
		std::cout << "\nRegistration failed: You can register this student only on license category AM!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		return;
	}
	if (((newAge >= 18 && newAge < 21) && newCategoryNum >= 4)) {
		std::cout << "\nRegistration failed: You can't register this student on D, F, I license categories!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		return;
	}
	Categories newCategory = static_cast<Categories>(newCategoryNum);

	Student* newStudent = new Student(newName, newSurname, newAge, newCategory, nullptr);
	school += newStudent;
	std::cout << "\nRegistration successful! " << std::endl;
}
void Admin::adminAddI(DrivingSchool& school) {
	std::string newName = "Ryan", newSurname = "Gosling";
	int newAge = 22, newCategoryNum = 2, newExp = 3;
	int answer = 2;

	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Enter instructor's first and last name: " << std::endl;
	std::cout << "[AUTO] " << newName << " " << newSurname << "." << std::endl;
	std::cout << "\nEnter instructor's age: " << std::endl;
	std::cout << "[AUTO] " << newAge << "." << std::endl;
	std::cout << "\nEnter instructor's experience: " << std::endl;
	std::cout << "[AUTO] " << newExp << "." << std::endl;
	std::cout << "\nEnter instructor's initial license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	std::cout << "[AUTO] " << newCategoryNum << "." << std::endl;
	Categories newCategory = static_cast<Categories>(newCategoryNum);

	Instructor* newInstructor = new Instructor(newName, newSurname, newAge, newExp, newCategory);
	bool add = true;
	while (add) {
		std::cout << "Does the instructor have more categories?\n1. Yes.\n2. No." << std::endl;
		std::cout << "[AUTO] " << answer << "." << std::endl;
		switch (answer) {
		case 1: {
			std::cout << "Enter category number (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): ";
			std::cin >> newCategoryNum;
			Categories newCategory = static_cast<Categories>(newCategoryNum);
			newInstructor->addCategory(newCategory);
			std::cout << "Category added!" << std::endl;
			break;
		}
		case 2:
			add = false;
			break;
		default:
			std::cout << "Invalid input!" << std::endl;
		}
	}
	school += newInstructor;
	std::cout << "\nRegistration successful! " << std::endl;
}
void Admin::printAllStud(DrivingSchool& school) {
	if (school.students.empty())
		std::cout << "The student database is currently empty." << std::endl;
	else {
		std::cout << "\n--ACTIVE STUDENT LIST--\n" << std::endl;
		for (int i = 0; i < school.students.size(); i++)
			std::cout << *school.students[i];
	}
}
void Admin::admin(DrivingSchool& school) {
	int choice, way1, way2;
	bool question = true;

	system("cls");
	while (question)
	{
		std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
		std::cout << "------------------------------------" << std::endl;
		std::cout << "1. Operations on students\n2. Operations on instructors.\n3. Exit the admin menu.\nSelect an option: ";
		std::cin >> choice;
		switch (choice) {
		case 1: {
			system("cls");
			std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
			std::cout << "------------------------------------" << std::endl;
			std::cout << "1. View the student's information.\n2. Delete student.\n3. Add student.\nYour choice: ";
			std::cin >> way1;
			switch (way1) {
			case 1: {
				this->printAllStud(school);
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				this->adminDelS(school);
				system("pause");
				system("cls");
				break;
			}
			case 3:
				this->adminAddS(school);
				system("pause");
				system("cls");
				break;
			}
			break;
		}
		case 2: {
			system("cls");
			std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
			std::cout << "------------------------------------" << std::endl;
			std::cout << "1. Delete instructor.\n2. Add instructor.\nYour choice: ";
			std::cin >> way2;
			switch (way2) {
			case 1: {
				this->adminDelI(school);
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				this->adminAddI(school);
				system("pause");
				system("cls");
				break;
			}
			}
			break;
		}
		default:
			question = false;
			std::cout << "\nYou exited from admin menu or chosed wrong answer.\n" << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

Admin::~Admin() {
	std::cout << "Admin " << this->name << " " << this->surname << "has been deleted.\n";
}