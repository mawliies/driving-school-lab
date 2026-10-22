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
	void setName(std::string name);
	void setSurname(std::string surname);
	int getAge()const;
	virtual std::string getType()const = 0;
	virtual void printInfo()const;
	virtual void financialCalculations()const = 0;
	
	virtual ~Person();
};