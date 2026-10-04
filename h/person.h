#pragma once
#include <string>
#include <iostream>
class Person {
protected:
	std::string name;
	std::string surname;
	int age;
public:
	Person (std::string name, std::string surname, int age);
	std::string getName()const;
	std::string getSurname()const;
	int getAge()const;
	~Person();
};