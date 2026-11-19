#include "admin.h"
#include "drivingSchool.h"
#include "student.h"
#include "instructor.h"
#include "Collection.h"
#include "AllExceptions.h"

Admin::Admin(std::string name, std::string surname, int age, int password) : Person(name, surname, age) {
	if (password <= 0)
		throw InvalidDataException("Admin password must be positive.\n");
	this->password = password;
}

int Admin::getPassword() {
	return this->password;
}

bool Admin::truePassword(int pass) {
	return this->password == pass;
}

void Admin::DeleteStudent(DrivingSchool& school) {
	int num;
	Collection<Student*> current;
	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;

	for (int i = 0; i < school.getMembers().getSize(); i++) {
		if (school.getMembers().get(i)->getType() == "Student")
			current.add(static_cast<Student*>(school.getMembers().get(i)));
	}

	if (current.getSize() == 0)
		throw NotFoundException("The student database is empty. Nothing to delete.\n");

	for (int i = 0; i < current.getSize(); i++)
		std::cout << i + 1 << ". " << current.get(i)->getName() << " " << current.get(i)->getSurname() << std::endl;

	std::cout << "Enter student number: ";
	num = readInt("Expected input: integer.\n");
	if (num < 1 || num > current.getSize())
		throw OutOfRangeException(num, current.getSize());

	Student* toDel = current.get(num - 1);
	current.removeAt(num - 1);
	school -= toDel;
	std::cout << "Student successfully deleted.\n";
}

void Admin::DeleteInstructor(DrivingSchool& school) {
	int num;
	Collection<Instructor*> current;
	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;

	for (int i = 0; i < school.getMembers().getSize(); i++) {
		if (school.getMembers().get(i)->getType() == "Instructor")
			current.add(static_cast<Instructor*>(school.getMembers().get(i)));
	}

	if (current.getSize() == 0)
		throw NotFoundException("The instructor database is empty. Nothing to delete.\n");

	for (int i = 0; i < current.getSize(); i++)
		std::cout << i + 1 << ". " << current.get(i)->getName() << " " << current.get(i)->getSurname() << std::endl;

	std::cout << "Enter instructor number: ";
	num = readInt("Expected input: integer.\n");
	if (num < 1 || num > current.getSize())
		throw OutOfRangeException(num, current.getSize());

	Instructor* toDel = current.get(num - 1);
	for (int i = 0; i < school.getMembers().getSize(); i++) {
		if (school.getMembers().get(i)->getType() == "Student") {
			Student* students = static_cast<Student*>(school.getMembers().get(i));
			if (students->getInstructor() == toDel)
				students->setInstructor(nullptr);
		}
	}
	current.removeAt(num - 1);
	school -= toDel;
	std::cout << "Instructor successfully deleted.\n";
}

void Admin::AddStudent(DrivingSchool& school) {
	std::string newName, newSurname;
	int newAge, newCategoryNum;

	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Enter student's first and last name: " << std::endl;
	std::cin >> newName >> newSurname;

	std::cout << "\nEnter student's age: " << std::endl;
	newAge = readInt("Expected input: integer.\n");
	if (newAge <= 0 || newAge > 100)
		throw InvalidDataException("You must input a real age (1-100).\n");

	std::cout << "\nEnter student's desired license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	newCategoryNum = readInt("Expected input: integer.\n");
	checkAge(newAge, newCategoryNum);

	Categories newCategory = static_cast<Categories>(newCategoryNum);
	Student* newStudent = new Student(newName, newSurname, newAge, newCategory, nullptr);
	school += newStudent;
	std::cout << "\nRegistration successful! " << std::endl;
}

void Admin::AddInstructor(DrivingSchool& school) {
	std::string newName, newSurname;
	int newAge, newCategoryNum, newExp;
	int answer = 0;

	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Enter instructor's first and last name: " << std::endl;
	std::cin >> newName >> newSurname;

	std::cout << "\nEnter instructor's age: " << std::endl;
	newAge = readInt("Expected input: integer.\n");
	if (newAge < 18 || newAge > 100)
		throw AgeRestrictionException("Instructor must be between 18 and 100 years old.\n");

	std::cout << "\nEnter instructor's experience: " << std::endl;
	newExp = readInt("Expected input: integer.\n");
	if (newExp < 0 || newExp >(newAge - 18))
		throw InvalidDataException("Invalid driving experience relative to age.\n");

	std::cout << "\nEnter instructor's initial license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	newCategoryNum = readInt("Expected input: integer.\n");
	if (newCategoryNum < 0 || newCategoryNum > 6)
		throw OutOfRangeException(newCategoryNum, 6);

	Categories newCategory = static_cast<Categories>(newCategoryNum);
	Instructor* newInstructor = new Instructor(newName, newSurname, newAge, newExp, newCategory);

	bool add = true;
	while (add) {
		std::cout << "Does the instructor have more categories?\n1. Yes.\n2. No." << std::endl;
		answer = readInt("Expected input: integer.\n");
		switch (answer) {
		case 1: {
			std::cout << "Enter category number (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): ";
			if (!(std::cin >> newCategoryNum)) {
				delete newInstructor;
				std::cin.clear();
				std::cin.ignore(100, '\n');
				throw InvalidDataException("Expected input: integer.\n");
			}
			if (newCategoryNum < 0 || newCategoryNum > 6) {
				delete newInstructor;
				throw OutOfRangeException(newCategoryNum, 6);
			}
			Categories extraCategory = static_cast<Categories>(newCategoryNum);
			newInstructor->addCategory(extraCategory);
			std::cout << "Category added!" << std::endl;
			break;
		}
		case 2:
			add = false;
			break;
		default:
			delete newInstructor;
			throw OutOfRangeException(answer, 2);
		}
	}
	school += newInstructor;
	std::cout << "\nRegistration successful! " << std::endl;
}

void Admin::recomendation(DrivingSchool& school) {
	system("cls");
	Collection<Student*> lonelyStudent;
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "  INSTRUCTOR RECOMMENDATION SYSTEM  " << std::endl;
	std::cout << "------------------------------------" << std::endl;

	for (int i = 0; i < school.getMembers().getSize(); i++) {
		if (school.getMembers().get(i)->getType() == "Student") {
			Student* students = static_cast<Student*>(school.getMembers().get(i));
			if (students->getInstructor() == nullptr)
				lonelyStudent.add(students);
		}
	}
	if (lonelyStudent.getSize() == 0)
		throw NotFoundException("Instructors are already assigned to all students.\n");

	std::cout << "\nFound " << lonelyStudent.getSize() << " students without an instructor.\n";
	for (int i = 0; i < lonelyStudent.getSize(); i++) {
		Student* currentStudent = lonelyStudent.get(i);
		Collection<Instructor*> suitableInstructor;

		for (int k = 0; k < school.getMembers().getSize(); k++) {
			if (school.getMembers().get(k)->getType() == "Instructor") {
				Instructor* instructor = static_cast<Instructor*>(school.getMembers().get(k));
				if (instructor->hasCategory(currentStudent->getCategory())) {
					suitableInstructor.add(instructor);
				}
			}
		}
		std::cout << "\n\n\n------------------------------------";
		std::cout << "\nStudent: " << currentStudent->getName() << " " << currentStudent->getSurname();
		std::cout << "\nDesired category: " << ctgToString(currentStudent->getCategory());

		if (suitableInstructor.getSize() == 0) {
			std::cout << "\nThere are no suitable instructors for this student.\n";
			continue;
		}
		else {
			std::cout << "\nThe Instructors for assigning:\n";
			for (int j = 0; j < suitableInstructor.getSize(); j++) {
				std::cout << "\nInstructor: " << suitableInstructor.get(j)->getName() << " " << suitableInstructor.get(j)->getSurname();
				std::cout << "\nDriving experience: " << suitableInstructor.get(j)->getExperience() << " years";
				std::cout << "\n------------------------------------";
			}
			Instructor* best = findBest(suitableInstructor);
			if (best != nullptr) {
				std::cout << "\n-->The best candidate for this student: "
					<< best->getName() << " " << best->getSurname()
					<< " (Experience: " << best->getExperience() << " years)\n";
			}
		}
	}
	std::cout << "\n------------------------------------\n";
}
void Admin::printAllStudents(DrivingSchool& school) {
	bool empty = true;
	std::cout << "\n--ACTIVE STUDENT LIST--\n" << std::endl;
	for (int i = 0; i < school.getMembers().getSize(); i++) {
		if (school.getMembers().get(i)->getType() == "Student") {
			school.getMembers().get(i)->printInfo();
			empty = false;
		}
	}
	if (empty) 
		throw NotFoundException("The student database is currently empty.\n");
}

void Admin::instructorCheck(DrivingSchool& school) {
	bool empty = true;
	for (int i = 0; i < school.getMembers().getSize(); i++) {
		if (school.getMembers().get(i)->getType() == "Instructor") {
			school.getMembers().get(i)->financialCalculations();
			empty = false;
		}
	}
	if (empty) 
		throw NotFoundException("The instructor database is currently empty.\n");
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

		try {
			choice = readInt("Expected input: integer.\n");
			switch (choice) {
			case 1: {
				system("cls");
				std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
				std::cout << "------------------------------------" << std::endl;
				std::cout << "1. View the student's information.\n2. Delete student.\n3. Add student.\n4. Check students without instructors.\nYour choice: ";

				way1 = readInt("Expected input: integer.\n");
				switch (way1) {
				case 1: {
					this->printAllStudents(school);
					system("pause");
					system("cls");
					break;
				}
				case 2: {
					this->DeleteStudent(school);
					system("pause");
					system("cls");
					break;
				}
				case 3: {
					this->AddStudent(school);
					system("pause");
					system("cls");
					break;
				}
				case 4: {
					this->recomendation(school);
					system("pause");
					system("cls");
					break;
				}
				default: 
					throw OutOfRangeException(way1, 4);
				}
				break;
			}
			case 2: {
				system("cls");
				std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
				std::cout << "------------------------------------" << std::endl;
				std::cout << "1. Delete instructor.\n2. Add instructor.\n3. Check instructors' salary.\nYour choice: ";

				way2 = readInt("Expected input: integer.\n");

				switch (way2) {
				case 1: {
					this->DeleteInstructor(school);
					system("pause");
					system("cls");
					break;
				}
				case 2: {
					this->AddInstructor(school);
					system("pause");
					system("cls");
					break;
				}
				case 3: {
					this->instructorCheck(school);
					system("pause");
					system("cls");
					break;
				}
				default:
					throw OutOfRangeException(way2, 3);
				}
				break;
			}
			case 3: {
				question = false;
				std::cout << "\nYou exited from admin menu.\n" << std::endl;
				system("pause");
				system("cls");
				break;
			}
			default: 
				throw OutOfRangeException(choice, 3);
			}
		}
		catch (const AgeRestrictionException& e) {
			std::cerr << "\n[AGE RESTRICTION] " << e.what() << "\n";
			system("pause");
			system("cls");
		}
		catch (const DuplicateDataException& e) {
			std::cerr << "\n[DUPLICATE MEMBER] " << e.what() << "\n";
			system("pause");
			system("cls");
		}
		catch (const NotFoundException& e) {
			std::cerr << "\n[NOT FOUND] " << e.what() << "\n";
			system("pause");
			system("cls");
		}
		catch (const OutOfRangeException& e) {
			std::cerr << "\n[OUT OF RANGE] " << e.what() << "\n";
			system("pause");
			system("cls");
		}
		catch (const InvalidDataException& e) {
			std::cerr << "\n[INVALID INPUT] " << e.what() << "\n";
			system("pause");
			system("cls");
		}
		catch (const SchoolException& e) {
			std::cerr << "\n[ADMIN ERROR] " << e.what() << "\n";
			system("pause");
			system("cls");
		}
	}
}

std::string Admin::getType() const {
	return "Administrator";
}

void Admin::printInfo() const {
	Person::printInfo();
	std::cout << "\nAccess level: System administrator.\n--------------------------\n";
}

void Admin::financialCalculations() const {
	return;
}

Admin::~Admin() {
	std::cout << "Admin " << this->name << " " << this->surname << " has been deleted.\n";
}