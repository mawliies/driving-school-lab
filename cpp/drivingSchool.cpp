#include "person.h"
#include "drivingSchool.h"
#include "instructor.h"
#include "student.h"
#include "admin.h"

std::string ctgToString(Categories ctg) {
	switch (ctg) {
	case AM:
		return "Category AM: mopeds and scooters.";
	case A:
		return "Category A: motorcycles.";
	case B:
		return "Category B: passenger cars.";
	case C:
		return "Category C: trucks.";
	case D:
		return "Category D: buses.";
	case F:
		return "Category F: trams.";
	case I:
		return "Category I: trolleys.";
	}
	return "Error! Retry.";
}

DrivingSchool::DrivingSchool() {}

DrivingSchool& DrivingSchool::operator+=(Person* newMember) {
	if (newMember == nullptr)
		return *this;
	this->members.push_back(newMember);
	return *this;
}

DrivingSchool& DrivingSchool::operator-=(Person* newMember) {
	if (newMember == nullptr)
		return *this;
	for (auto it = members.begin(); it != members.end(); ++it) {
		if (*it == newMember)
		{
			delete* it;
			members.erase(it);
			break;
		}
	}
	return *this;
}

bool checkAge(int age, int newCategoryNum) {
	if (age < 16) {
		std::cout << "\nRegistration failed: Student must be at least 16 years old to register!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		return false;
	}
	std::cout << "\nEnter student's desired license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	std::cout << "[AUTO] " << newCategoryNum << "." << std::endl;
	if (((age < 18 && age >= 16) && newCategoryNum != 1)) {
		std::cout << "\nRegistration failed: You can register this student only on license category AM!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		return false;
	}
	if (((age >= 18 && age < 21) && newCategoryNum >= 4)) {
		std::cout << "\nRegistration failed: You can't register this student on D, F, I license categories!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		return false;
	}
	return true;
}

void defining(DrivingSchool& school, Student* stud) {	
	std::vector<Instructor*> suitableInstructor;
	int choice = 0;

	for (int i = 0; i < school.members.size(); i++)
		if (school.members[i]->getType() == "Instructor") {
			Instructor* instructor = static_cast<Instructor*>(school.members[i]);
			if(instructor->hasCategory(stud->getCategory()))
				suitableInstructor.push_back(instructor);
		}
	if (suitableInstructor.empty()) {
		std::cout << "No suitable instructor found for student " << stud->getName() << " " << stud->getSurname() << "." << std::endl;
		return;
	}
	for (int i = 0; i < suitableInstructor.size(); i++) {
		if (stud->hasInstructor(suitableInstructor[i])) {
			std::cout << "\nInstructor is already assigned to this student.\n";
			system("pause");
			return;
		}
	}
	std::cout << "\n-- Available instructors for " << ctgToString(stud->getCategory()) << " --\n" << std::endl;
	for (int i = 0; i < suitableInstructor.size(); i++)
		std::cout << i + 1 << ". " << suitableInstructor[i]->getName() << " " << suitableInstructor[i]->getSurname() << ". (Experience: " << suitableInstructor[i]->getExperience() << " years).\n" << std::endl;

	std::cout << "Enter the number of the selected instructor (0 to cancel): ";
	std::cin >> choice;
	if (choice > 0 && choice <= suitableInstructor.size()) {
		stud->setInstructor(suitableInstructor[choice - 1]);
		std::cout << "Congratulations! The instructor has been assigned." << std::endl;
	}
	else
		std::cout << "Selection canceled or invalid number entered. Instructor not assigned." << std::endl;
	std::cout << "--------------------------------" << std::endl;
	system("pause");
	system("cls");
}

void DrivingSchool::registration() {
	std::string newName, newSurname;
	int newAge, newCategoryNum;

	std::cout << "\n--STUDENT REGISTRATION--\nEnter your first and last name: " << std::endl;
	std::cin >> newName;
	std::cin >> newSurname;
	std::cout << "\nEnter your age: " << std::endl;
	std::cin >> newAge;
	std::cout << "\nEnter your desired license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	std::cin >> newCategoryNum;
	if (!checkAge(newAge, newCategoryNum))
		return;
	Categories newCategory = static_cast<Categories>(newCategoryNum);

	Student* newStudent = new Student(newName, newSurname, newAge, newCategory, nullptr);
	*this += newStudent;
	std::cout << "\nRegistration successful! You are now in the database." << std::endl;
	std::cout << "--------------------------------" << std::endl;
}

void DrivingSchool::profile(Student* stud) {
	int choice = 0;

	while (choice != 3)
	{
		system("cls");
		std::cout << "--STUDENT PERSONAL PROFILE--\n1. View profile card.\n2. Assign an instructor.\n3. Return to main menu." << std::endl;
		std::cin >> choice;

		switch (choice) {
		case 1:
		{
			system("cls");
			std::cout << *stud;
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			defining(*this, stud);
			break;
		}
		case 3: {
			system("cls");
			return;
		}
		default:
			std::cout << "Invalid menu option." << std::endl;
			break;
		}
	}
}

void DrivingSchool::findStudent() {		
	std::string myName, mySurname;	
	Student* found = nullptr;
	Student other("", "", 0, Categories::AM, nullptr);
	int reg;

	std::cout << "\nTo log into your personal profile, enter your first and last name:\n" << std::endl;
	std::cin >> other;	

	for (int i = 0; i < members.size(); i++)
		if (members[i]->getType() == "Student") {
			Student* student = static_cast<Student*>(members[i]);
			if (*student == other) {
				found = student;
				break;
			}
		}
	if (found != nullptr) {
		system("cls");
		std::cout << "You have successfully logged into your profile!\n--------------------------------\n";

		this->profile(found);
	}
	else {		
		std::cout << "Account not found. Would you like to register?\n" << std::endl;
		std::cout << "1. YES\n2. NO\n" << std::endl;
		do
			std::cin >> reg;
		while (reg != 1 && reg != 2);
		if (reg == 1)
			this->registration();
		system("pause");
		return;
	}

}

void DrivingSchool::printAllInstr() {		
	system("cls");
	bool empty = true;
	std::cout << "--ACTIVE INSTRUCTOR ROSTER--\n" << std::endl;
	for (int i = 0; i < members.size(); i++)
		if (members[i]->getType() == "Instructor") {
			members[i]->printInfo();
			empty = false;
		}
	if(empty)
		std::cout << "The instructor database is currently empty." << std::endl;
	system("pause");
}

void DrivingSchool::statistics() {		
	system("cls");
	bool empty = true;
	std::vector<Instructor*> current;
	for (int i = 0; i < members.size(); i++) {
		if (members[i]->getType() == "Instructor")
			current.push_back(static_cast<Instructor*>(members[i]));
	}
	if (current.empty()) {
		std::cout << "The instructor database is currently empty. Statistics unavailable." << std::endl;
		system("pause");
		return;
	}

	Instructor* best = current[0];
	Instructor* young = current[0];
	for (int i = 0; i < current.size(); i++) {
		if (*current[i] > *best)
			best = current[i];
		if (*current[i] < *young)
			young = current[i];
	}
	std::cout << "==================================================" << std::endl;
	std::cout << "           DRIVING SCHOOL STATISTICS              " << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "\n--THE INSTRUCTOR OF THE YEAR--\n" << *best;
	std::cout << "\n--THE YOUNGEST WORKER WITH GREAT POTENTIAL--\n" << *young;
	system("pause");
}

void DrivingSchool::loginAdmin() {	
	system("cls");
	std::vector<Admin*>current;
	int pass = 0;
	int num = 0;
	
	for (int i = 0; i < members.size(); i++)
		if (members[i]->getType() == "Administrator")
			current.push_back(static_cast<Admin*>(members[i]));
		
	if (current.empty()) {
		std::cout << "No current admins!.\n";
		system("pause");
		return;
	}
	std::cout << "==================================================" << std::endl;
	std::cout << "                 LOGIN AS ADMIN                   " << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "ADMIN LIST:\n";
	for (int i = 0; i < current.size(); i++)
		std::cout << "#" << i + 1 << ". Name: " << current[i]->getName() << "\nSurname: " << current[i]->getSurname() << "\nAge: " << current[i]->getAge() << "\n-----------------\n";
	std::cout << "\nENTER CHOICE\n";
	std::cin >> num;
	std::cout << "\nENTER SPECIAL ADMIN PASSWORD: ";
	std::cin >> pass;
	if (current[num - 1]->truePassword(pass) && num > 0 && num <= current.size()) {
		std::cout << "\nCorrect password! Welcome!\n";
		system("pause");
		current[num - 1]->admin(*this);
	}
	else {
		std::cout << "\nWrong password! Request declined\n";
		system("pause");
	}
		
}

DrivingSchool::~DrivingSchool() {
	for (int i = 0; i < members.size(); i++)
		delete this->members[i];
	this->members.clear();
	std::cout << "\nAll memory has been successfully freed." << std::endl;
}

void menu(DrivingSchool& school) {
	int choice;
	bool toDo = true;

	while (toDo) {
		system("cls");
		std::cout << "-----------DRIVING SCHOOL-----------" << std::endl;
		std::cout << "\n--1. Log in as a student.\n--2. Log in as an administrator.\n--3. View general information.\n--4. View statistics.\n--5. Exit program.\n";
		std::cin >> choice;
		switch (choice) {
		case 1: {
			school.findStudent();
			break;
		}
		case 2: {
			school.loginAdmin();
			break;
		}
		case 3: {
			school.printAllInstr();
			break;
		}
		case 4: {
			school.statistics();
			break;
		}
		case 5: {
			  std::cout << "Program successfully completed.\n";
			  toDo = false;
			  break;
		}
		default:
			std::cout << "Exit!";
			break;
		}
	}
}

void test(DrivingSchool& school) {		//тестовые для лр
	Instructor* i1 = new Instructor("Borat", "Sagdiev", 54, 25, AM);
	Instructor* i2 = new Instructor("Baby", "Yoda", 50, 20, B);
	Instructor* i3 = new Instructor("Skibidi", "Toilet", 25, 3, C);
	Instructor* i4 = new Instructor("Big", "Floppa", 22, 1, B);
	Instructor* i5 = new Instructor("Ozzy", "Osborne", 70, 43, B);
	Instructor* i6 = new Instructor("Lana", "DelRay", 20, 1, B);

	i1->addCategory(A);
	i3->addCategory(D); i3->addCategory(F);
	i4->addCategory(C);
	i5->addCategory(D); i5->addCategory(I);
	i6->addCategory(AM); i6->addCategory(A);

	Student* s1 = new Student("Daria", "Zhvirblya", 19, A, nullptr);
	Student* s2 = new Student("Jane", "Dou", 25, C, nullptr);
	Student* s3 = new Student("Walter", "White", 51, D, i3);
	Student* s4 = new Student("Peter", "Parker", 16, AM, nullptr);
	Student* s5 = new Student("Dexter", "Morgan", 33, B, i6);
	Student* s6 = new Student("Nana", "Osaki", 21, F, nullptr);
	Student* s7 = new Student("Kurt", "Cobain", 27, AM, i1);
	Student* s8 = new Student("Vivienne", "Westwood", 17, AM, i4);

	Admin* a1 = new Admin("Irina", "Skiba", 25, 12345);
	Admin* a2 = new Admin("Roman", "Molchanov", 32, 52520);
	Admin* a3 = new Admin("Giga", "Chad", 43, 70766);

	school += i1;
	school += i2;
	school += i3;
	school += i4;
	school += i5;
	school += i6;
	school += s1;
	school += s2;
	school += s3;
	school += s4;
	school += s5;
	school += s6;
	school += s7;
	school += s8;
	school += a1;
	school += a2;
	school += a3;
}
