#include "C:\labs\2k\DrivingSchool\DrivingSchool\h\drivingSchool.h"

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

DrivingSchool::DrivingSchool(Instructor* instr, Student* stud) {
	if (instr != nullptr) this->instructors.push_back(instr);
	if (stud != nullptr) this->students.push_back(stud);
}

void DrivingSchool::registrInstructor(Instructor* instr) {
	this->instructors.push_back(instr);
}

void DrivingSchool::registrStudent(Student* stud) {
	this->students.push_back(stud);
}

void DrivingSchool::defining(Student* stud) {
	std::vector<Instructor*> suitableInstr;
	int choice = 0;

	for (size_t i = 0; i < instructors.size(); i++)
		if (instructors[i]->hasCategory(stud->getMyCategory()))
			suitableInstr.push_back(instructors[i]);

	if (suitableInstr.empty()) {
		std::cout << "No suitable instructor found for student " << stud->getName() << " " << stud->getSurname() << "." << std::endl;
		return;
	}

	std::cout << "\n-- Available instructors for " << ctgToString(stud->getMyCategory()) << " --\n" << std::endl;
	for (size_t i = 0; i < suitableInstr.size(); i++)
		std::cout << i + 1 << ". " << suitableInstr[i]->getName() << " " << suitableInstr[i]->getSurname() << ". (Experience: " << suitableInstr[i]->getExp() << " years).\n" << std::endl;

	std::cout << "Enter the number of the selected instructor (0 to cancel): ";
	std::cin >> choice;
	if (choice > 0 && choice <= static_cast<int>(suitableInstr.size())) {
		stud->setInstructor(suitableInstr[choice - 1]);
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
	if (newAge < 16) {
		std::cout << "\nRegistration failed: You must be at least 16 years old to register!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		system("pause");
		return;
	}
	std::cout << "\nEnter your desired license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	std::cin >> newCategoryNum;
	if (((newAge < 18 && newAge > 16) && newCategoryNum != 1)) {
		std::cout << "\nRegistration failed: You can register only on license category AM!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		system("pause");
		return;
	}
	if (((newAge > 18 && newAge < 21) && newCategoryNum >= 4)) {
		std::cout << "\nRegistration failed: You can't register on D, F, I license categories!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		system("pause");
		return;
	}
	Categories newCategory = static_cast<Categories>(newCategoryNum);

	Student* newStudent = new Student(newName, newSurname, newAge, newCategory, nullptr);
	this->registrStudent(newStudent);
	std::cout << "\nRegistration successful! You are now in the database." << std::endl;
	std::cout << "--------------------------------" << std::endl;
	system("pause");
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
			stud->printInfo();

			break;
		}
		case 2: {
			system("cls");
			this->defining(stud);
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
	/*std::string myName;
	std::string mySurname;
	int reg;*/				//для защиты лр нужен автоввод
	std::string myName = "Daria", mySurname = "Zhvirblya";
	Student* found = nullptr;
	int reg = 2;

	std::cout << "\nTo log into your personal profile, enter your first and last name:\n" << std::endl;
	/*std::cin >> myName;
	std::cin >> mySurname;*/
	std::cout << "[AUTO] " << myName << " " << mySurname << "." << std::endl;
	system("pause"); //не используется при обычном вводе
	for (int i = 0; i < students.size(); i++)
		if (this->students[i]->getName() == myName && this->students[i]->getSurname() == mySurname) {
			found = this->students[i];
			break;
		}
	if (found != nullptr) {
		system("cls");
		std::cout << "You have successfully logged into your profile!\n--------------------------------\n";

		this->profile(found);
	}
	else {		//данный сценарий при автовводе опущен
		std::cout << "Account not found. Would you like to register?\n" << std::endl;
		std::cout << "1. YES\n2. NO\n" << std::endl;
		//std::cin >> reg;
		if (reg == 1)
			this->registration();
		else
			std::cout << "[AUTO] 2." << std::endl;
		system("pause");
		return;
	}

}

void DrivingSchool::adminDelS() {
	int num;

	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	for (int i = 0; i < students.size(); i++)
		std::cout << i + 1 << ". " << students[i]->getName() << " " << students[i]->getSurname() << std::endl;
	std::cout << "Enter student number: ";
	std::cin >> num;
	delete this->students[num - 1];
	this->students.erase(this->students.begin() + (num - 1));
}

void DrivingSchool::adminDelI() {
	system("cls");
	int num;
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	for (int i = 0; i < instructors.size(); i++)
		std::cout << i + 1 << ". " << instructors[i]->getName() << " " << instructors[i]->getSurname() << std::endl;
	std::cout << "Enter instructor number: ";
	std::cin >> num;
	for (int i = 0; i < students.size(); i++)
		if (this->students[i]->getInstructor() != nullptr && this->students[i]->getInstructor() == this->instructors[num - 1])
			this->students[i]->setInstructor(nullptr);
	delete this->instructors[num - 1];
	this->instructors.erase(this->instructors.begin() + (num - 1));
}

void DrivingSchool::adminAddS() {
	/*std::string newName, newSurname;		 //для защиты лр нужен автоввод
	int newAge, newCategoryNum;*/
	std::string newName = "Lady", newSurname = "Gaga";
	int newAge = 40, newCategoryNum = 2;

	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Enter student's first and last name: " << std::endl;
	/*std::cin >> newName;
	std::cin >> newSurname;*/
	std::cout << "[AUTO] " << newName << " " << newSurname << "." << std::endl;
	std::cout << "\nEnter student's age: " << std::endl;
	//std::cin >> newAge;
	std::cout << "[AUTO] " << newAge << "." << std::endl;
	if (newAge < 16) {
		std::cout << "\nRegistration failed: Student must be at least 16 years old to register!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		system("pause");
		return;
	}
	std::cout << "\nEnter student's desired license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	//std::cin >> newCategoryNum;
	std::cout << "[AUTO] " << newCategoryNum << "." << std::endl;
	if (((newAge < 18 && newAge > 16) && newCategoryNum != 1)) {
		std::cout << "\nRegistration failed: You can register this student only on license category AM!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		system("pause");
		return;
	}
	if (((newAge > 18 && newAge < 21) && newCategoryNum >= 4)) {
		std::cout << "\nRegistration failed: You can't register this student on D, F, I license categories!" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		system("pause");
		return;
	}
	Categories newCategory = static_cast<Categories>(newCategoryNum);

	Student* newStudent = new Student(newName, newSurname, newAge, newCategory, nullptr);
	this->registrStudent(newStudent);
	std::cout << "\nRegistration successful! " << std::endl;
}
void DrivingSchool::adminAddI() {
	/*std::string newName, newSurname;			//для защиты лр нужен автоввод
	int newAge, newCategoryNum, newExp;
	int answer;*/
	std::string newName = "Ryan", newSurname = "Gosling";
	int newAge = 22, newCategoryNum = 2, newExp = 3;
	int answer = 2;

	system("cls");
	std::cout << "!YOU LOGGED IN AS AN ADMINISTRATOR!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Enter instructor's first and last name: " << std::endl;
	/*std::cin >> newName;
	std::cin >> newSurname;*/
	std::cout << "[AUTO] " << newName << " " << newSurname << "." << std::endl;
	std::cout << "\nEnter instructor's age: " << std::endl;
	//std::cin >> newAge;
	std::cout << "[AUTO] " << newAge << "." << std::endl;
	std::cout << "\nEnter instructor's experience: " << std::endl;
	//std::cin >> newExp;
	std::cout << "[AUTO] " << newExp << "." << std::endl;
	std::cout << "\nEnter instructor's initial license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	//std::cin >> newCategoryNum;
	std::cout << "[AUTO] " << newCategoryNum << "." << std::endl;
	Categories newCategory = static_cast<Categories>(newCategoryNum);

	Instructor* newInstructor = new Instructor(newName, newSurname, newAge, newExp, newCategory);
	bool add = true;
	while (add) {
		std::cout << "Does the instructor have more categories?\n1. Yes.\n2. No." << std::endl;
		//std::cin >> answer;
		std::cout << "[AUTO] " << answer << "." << std::endl;
		switch (answer) {
		case 1: {		//данный сценарий при автовводе опущен
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
	this->registrInstructor(newInstructor);
	std::cout << "\nRegistration successful! " << std::endl;
}

void DrivingSchool::admin() {
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
			std::cout << "1. Delete student.\n2. Add student.\nYour choice: ";
			std::cin >> way1;
			switch (way1) {
			case 1: {
				this->adminDelS();
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				this->adminAddS();
				system("pause");
				system("cls");
				break;
			}
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
				this->adminDelI();
				system("pause");
				system("cls");
				break;
			}
			case 2: {
				this->adminAddI();
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

void DrivingSchool::printAllInstr() {
	system("cls");
	if (this->instructors.empty())
		std::cout << "The instructor database is currently empty." << std::endl;
	else {
		std::cout << "--ACTIVE INSTRUCTOR ROSTER--\n" << std::endl;
		for (int i = 0; i < instructors.size(); i++)
			this->instructors[i]->printInfo();
	}
	system("pause");
}

DrivingSchool::~DrivingSchool() {
	for (int i = 0; i < instructors.size(); i++)
		delete this->instructors[i];
	this->instructors.clear();
	for (int i = 0; i < students.size(); i++)
		delete this->students[i];
	this->students.clear();
	std::cout << "\nAll memory has been successfully freed." << std::endl;
}

void menu(DrivingSchool& school) {
	int choice;
	bool toDo = true;

	while (toDo) {
		system("cls");
		std::cout << "-----------DRIVING SCHOOL-----------" << std::endl;
		std::cout << "\n--1. Log in as a student.\n--2. Log in as an administrator.\n--3. View general information.\n--4. Exit program.\n";
		std::cin >> choice;
		switch (choice) {
		case 1: {
			school.findStudent();
			break;
		}
		case 2: {
			school.admin();
			break;
		}
		case 3: {
			school.printAllInstr();
			break;
		}
		case 4: {
			std::cout << "Program successfully completed.";
			toDo = false;
		}
		}

	}
}

void test(DrivingSchool& school) {		//тестовые для лр
	Instructor* i1 = new Instructor("Borat", "Sagdiev", 54, 25, AM);
	Instructor* i2 = new Instructor("Baby", "Yoda", 50, 20, B);
	Instructor* i3 = new Instructor("Skibidi", "Toilet", 37, 11, C);
	Instructor* i4 = new Instructor("Big", "Floppa", 22, 1, B);
	Instructor* i5 = new Instructor("Ozzy", "Osborne", 70, 43, B);
	Instructor* i6 = new Instructor("Lana", "DelRay", 41, 17, B);

	i1->addCategory(A);
	i3->addCategory(D); i3->addCategory(F);
	i4->addCategory(C);
	i5->addCategory(D); i5->addCategory(I);
	i6->addCategory(AM); i6->addCategory(A);

	Student* s1 = new Student("Daria", "Zhvirblya", 19, A, nullptr);
	Student* s2 = new Student("Jane", "Dou", 25, C, nullptr);
	Student* s3 = new Student("Walter", "White", 51, D, i3);
	Student* s4 = new Student("Peter", "Parker", 15, AM, nullptr);
	Student* s5 = new Student("Dexter", "Morgan", 33, B, i6);
	Student* s6 = new Student("Nana", "Osaki", 21, F, nullptr);
	Student* s7 = new Student("Kurt", "Cobain", 27, AM, i1);
	Student* s8 = new Student("Vivienne", "Westwood", 17, C, i4);

	school.registrInstructor(i1);
	school.registrInstructor(i2);
	school.registrInstructor(i3);
	school.registrInstructor(i4);
	school.registrInstructor(i5);
	school.registrInstructor(i6);
	school.registrStudent(s1);
	school.registrStudent(s2);
	school.registrStudent(s3);
	school.registrStudent(s4);
	school.registrStudent(s5);
	school.registrStudent(s6);
	school.registrStudent(s7);
	school.registrStudent(s8);
}
