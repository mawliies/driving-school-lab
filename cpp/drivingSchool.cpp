#include "AllExceptions.h"
#include "person.h"
#include "drivingSchool.h"
#include "instructor.h"
#include "student.h"
#include "admin.h"

namespace {
	int readInt(const std::string& errorMsg = "Expected input: integer.\n") {
		int value = 0;
		if (!(std::cin >> value)) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			throw InvalidDataException(errorMsg);
		}
		return value;
	}

	int readIntInRange(int minVal, int maxVal, const std::string& errorMsg = "Expected input: integer.\n") {
		int value = readInt(errorMsg);
		if (value < minVal || value > maxVal) {
			throw OutOfRangeException(value, maxVal);
		}
		return value;
	}

	void logErrorAndPause(const std::string& tag, const std::exception& e) {
		std::cerr << "\n[" << tag << "] " << e.what() << "\n";
		system("pause");
	}

	Collection<Instructor*> findSuitableInstructors(DrivingSchool& school, Categories cat) {
		Collection<Instructor*> suitable;
		Collection<Instructor*> instructors = collectByType<Instructor>(school, "Instructor");
		for (int i = 0; i < instructors.getSize(); i++) {
			Instructor* instr = instructors.get(i);
			if (instr->hasCategory(cat)) {
				suitable.add(instr);
			}
		}
		return suitable;
	}

	Collection<std::string> createDefaultAutopark() {
		Collection<std::string> car;
		car.add("Yamaha YBR 125");
		car.add("Volkswagen Polo (Manual)");
		car.add("Renault Logan (Manual)");
		car.add("Hyundai Accent (Automatic)");
		car.add("GAZON NEXT");
		car.add("MAZ-4371 ('Zubrenok')");
		car.add("Mercedes-Benz Sprinter");
		car.add("DRILL");
		car.add("MAZ-203Т");
		return car;
	}
}

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
	default:
		return "Error! Retry.";
	}
}

DrivingSchool::DrivingSchool() {}

Collection<Person*>& DrivingSchool::getMembers() {
	return this->members;
}

DrivingSchool& DrivingSchool::operator+=(Person* newMember) {
	if (newMember == nullptr)
		throw NotFoundException("No member for adding.\n");
	if (newMember->getType() == "Student") {
		Student* newStud = static_cast<Student*>(newMember);
		Collection<Student*> students = collectByType<Student>(*this, "Student");
		for (int i = 0; i < students.getSize(); i++) {
			if (*students.get(i) == *newStud) {
				std::string name = newStud->getName() + " " + newStud->getSurname();
				delete newMember;
				throw DuplicateDataException(name);
			}
		}
	}
	this->members.add(newMember);
	return *this;
}

DrivingSchool& DrivingSchool::operator-=(Person* newMember) {
	if (newMember == nullptr)
		throw NotFoundException("No member for deleting.\n");
	int i = members.findElement(newMember);
	if (i != -1) {
		delete members.get(i);
		members.removeAt(i);
	}
	return *this;
}

void checkAge(int age, int newCategoryNum) {
	if (newCategoryNum < 0 || newCategoryNum > 6)
		throw OutOfRangeException(newCategoryNum, 6);
	if (age < 16)
		throw AgeRestrictionException("Registration failed: Student must be at least 16 years old to register!\n");
	std::cout << "\nEnter student's desired license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	std::cout << "[AUTO] " << newCategoryNum << "." << std::endl;
	if (((age < 18 && age >= 16) && newCategoryNum != 0))
		throw AgeRestrictionException("Registration failed : You can register this student only on license category AM!\n");
	if (((age >= 18 && age < 21) && newCategoryNum >= 4))
		throw AgeRestrictionException("Registration failed: You can't register this student on D, F, I license categories!\n");
}

void defining(DrivingSchool& school, Student* stud) {
	if (stud == nullptr)
		throw NotFoundException("No student found.\n");

	Collection<Instructor*> suitableInstructor = findSuitableInstructors(school, stud->getCategory());
	requireNonEmpty(suitableInstructor, "No suitable instructor found for student " + stud->getName() + " " + stud->getSurname() + "\n");

	for (int i = 0; i < suitableInstructor.getSize(); i++) {
		if (stud->hasInstructor(suitableInstructor.get(i)))
			throw InvalidOperationException("Instructor is already assigned.\n");
	}

	std::cout << "\n-- Available instructors for " << ctgToString(stud->getCategory()) << " --\n" << std::endl;
	for (int i = 0; i < suitableInstructor.getSize(); i++) {
		Instructor* instr = suitableInstructor.get(i);
		std::cout << i + 1 << ". " << instr->getName() << " " << instr->getSurname()
			<< ". (Experience: " << instr->getExperience() << " years).\n" << std::endl;
	}

	std::cout << "Enter the number of the selected instructor (0 to cancel): ";
	int choice = readIntInRange(0, suitableInstructor.getSize(), "Expected input: integer");
	if (choice == 0) {
		std::cout << "Exit!\n";
		system("pause");
		return;
	}

	stud->setInstructor(suitableInstructor.get(choice - 1));
	std::cout << "Congratulations! The instructor has been assigned." << std::endl;
	std::cout << "--------------------------------" << std::endl;
	system("pause");
	system("cls");
}

void DrivingSchool::registration() {
	std::string newName, newSurname;
	std::cout << "\n--STUDENT REGISTRATION--\nEnter your first and last name: " << std::endl;
	std::cin >> newName >> newSurname;

	std::cout << "\nEnter your age: " << std::endl;
	int newAge = readInt("Expected input: integer");
	if (newAge <= 0 || newAge > 100)
		throw InvalidDataException("You must input your real age.\n");

	std::cout << "\nEnter your desired license category (0-AM, 1-A, 2-B, 3-C, 4-D, 5-F, 6-I): " << std::endl;
	int newCategoryNum = readIntInRange(0, 6, "Expected input: integer");
	checkAge(newAge, newCategoryNum);

	Categories newCategory = static_cast<Categories>(newCategoryNum);
	Student* newStudent = new Student(newName, newSurname, newAge, newCategory, nullptr);
	*this += newStudent;
	std::cout << "\nRegistration successful! You are now in the database." << std::endl;
	std::cout << "--------------------------------" << std::endl;
}

void DrivingSchool::profile(Student* stud) {
	int choice = 0;
	while (choice != 3) {
		system("cls");
		std::cout << "--STUDENT PERSONAL PROFILE--\n1. View profile card.\n2. Assign an instructor.\n3. Return to main menu." << std::endl;
		try {
			choice = readIntInRange(1, 3, "Expected input: integer.\n");
			switch (choice) {
			case 1:
				system("cls");
				std::cout << *stud;
				system("pause");
				break;
			case 2:
				system("cls");
				defining(*this, stud);
				break;
			case 3:
				system("cls");
				return;
			}
		}
		catch (const SchoolException& e) {
			logErrorAndPause("PROFILE ERROR", e);
		}
	}
}

void DrivingSchool::findStudent() {
	Student* found = nullptr;
	Student other("Temp", "Temp", 0, Categories::AM, nullptr);
	std::cout << "\nTo log into your personal profile, enter your first and last name:\n" << std::endl;
	std::cin >> other;

	Collection<Student*> students = collectByType<Student>(*this, "Student");
	for (int i = 0; i < students.getSize(); i++) {
		if (*students.get(i) == other) {
			found = students.get(i);
			break;
		}
	}

	if (found != nullptr) {
		system("cls");
		std::cout << "You have successfully logged into your profile!\n--------------------------------\n";
		this->profile(found);
	}
	else {
		std::cout << "Account not found. Would you like to register?\n\n1. YES\n2. NO\n" << std::endl;
		int reg = readIntInRange(1, 2, "Expected input: integer.\n");
		if (reg == 1)
			this->registration();
		system("pause");
	}
}

void DrivingSchool::printAllInstructors() {
	system("cls");
	Collection<Instructor*> instructors = collectByType<Instructor>(*this, "Instructor");
	requireNonEmpty(instructors, "The instructor database is currently empty.\n");

	std::cout << "--ACTIVE INSTRUCTOR ROSTER--\n" << std::endl;
	for (int i = 0; i < instructors.getSize(); i++) {
		instructors.get(i)->printInfo();
	}
	system("pause");
}

void DrivingSchool::information() {
	system("cls");
	Collection<std::string> car = createDefaultAutopark();
	std::cout << "\n--1. Check instructor's list.\n--2. Check driving school's autopark.\n--3. Search exactly car in autopark.\n--4. Exit.\n";

	try {
		int choice = readIntInRange(1, 4, "Expected input: integer.\n");
		switch (choice) {
		case 1:
			this->printAllInstructors();
			break;
		case 2:
			std::cout << "==================================================" << std::endl;
			std::cout << "             DRIVING SCHOOL AUTOPARK              " << std::endl;
			std::cout << "==================================================" << std::endl;
			car.print();
			std::cout << "==================================================" << std::endl;
			system("pause");
			break;
		case 3: {
			system("cls");
			std::string typing;
			std::cout << "Type the exactly mark of the car (e.g. Hyundai Accent (Automatic))...\n";
			std::cin.ignore();
			std::getline(std::cin, typing);
			if (car.findElement(typing) == -1)
				throw NotFoundException("This car is currently not in our fleet.\n");
			std::cout << "\nCar is AVAILABLE! Check all the autopark information for more details...\n";
			system("pause");
			break;
		}
		case 4:
			std::cout << "Exit!\n";
			system("pause");
			return;
		}
	}
	catch (const NotFoundException& e) {
		logErrorAndPause("CAR NOT FOUND", e);
	}
	catch (const SchoolException& e) {
		logErrorAndPause("INFORMATION ERROR", e);
	}
}

void DrivingSchool::statistics() {
	system("cls");
	Collection<Instructor*> current = collectByType<Instructor>(*this, "Instructor");
	requireNonEmpty(current, "The instructor database is currently empty. Statistics unavailable.\n");

	Instructor* best = current.get(0);
	Instructor* young = current.get(0);
	for (int i = 1; i < current.getSize(); i++) {
		if (*current.get(i) > *best)
			best = current.get(i);
		if (*current.get(i) < *young)
			young = current.get(i);
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
	Collection<Admin*> current = collectByType<Admin>(*this, "Administrator");
	requireNonEmpty(current, "No current admins.\n");

	std::cout << "==================================================" << std::endl;
	std::cout << "                 LOGIN AS ADMIN                   " << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "ADMIN LIST:\n";
	for (int i = 0; i < current.getSize(); i++) {
		std::cout << "#" << i + 1 << ". ";
		current.get(i)->printInfo();
	}

	std::cout << "\nENTER CHOICE\n";
	int num = readIntInRange(1, current.getSize(), "Expected input: integer.\n");

	std::cout << "\nENTER SPECIAL ADMIN PASSWORD: ";
	int pass = readInt("Expected input: integer.\n");
	if (!(current.get(num - 1)->truePassword(pass)))
		throw InvalidDataException("Wrong password!Request declined\n");

	std::cout << "\nCorrect password! Welcome!\n";
	system("pause");
	current.get(num - 1)->admin(*this);
}

DrivingSchool::~DrivingSchool() {
	for (int i = 0; i < members.getSize(); i++)
		delete this->members.get(i);
	this->members.clear();
	std::cout << "\nAll memory has been successfully freed." << std::endl;
}

void menu(DrivingSchool& school) {
	int choice = 0;
	bool toDo = true;
	while (toDo) {
		system("cls");
		std::cout << "-----------DRIVING SCHOOL-----------" << std::endl;
		std::cout << "\n--1. Log in as a student.\n--2. Log in as an administrator.\n--3. View general information.\n--4. View statistics.\n--5. Exit program.\n";
		try {
			choice = readIntInRange(1, 5, "Expected input: integer.\n");
			switch (choice) {
			case 1:
				school.findStudent();
				break;
			case 2:
				school.loginAdmin();
				break;
			case 3:
				school.information();
				break;
			case 4:
				school.statistics();
				break;
			case 5:
				std::cout << "Program successfully completed.\n";
				toDo = false;
				system("pause");
				break;
			}
		}
		catch (const AgeRestrictionException& e) {
			logErrorAndPause("AGE RESTRICTION", e);
		}
		catch (const DuplicateDataException& e) {
			logErrorAndPause("DUPLICATE MEMBER", e);
		}
		catch (const InvalidOperationException& e) {
			logErrorAndPause("ACCESS / OPERATION DENIED", e);
		}
		catch (const NotFoundException& e) {
			logErrorAndPause("NOT FOUND", e);
		}
		catch (const OutOfRangeException& e) {
			logErrorAndPause("OUT OF RANGE", e);
		}
		catch (const InvalidDataException& e) {
			logErrorAndPause("INVALID INPUT", e);
		}
		catch (const SchoolException& e) {
			logErrorAndPause("SYSTEM ERROR", e);
		}
		catch (const std::exception& e) {
			logErrorAndPause("CRITICAL ERROR", e);
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
	i4->addCategory(C); i4->addCategory(AM);
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
