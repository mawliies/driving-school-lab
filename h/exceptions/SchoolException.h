#pragma once
#include<stdexcept>
#include<string>
class SchoolException :public std::runtime_error {
public:
	explicit SchoolException(const std::string& msg) :std::runtime_error(msg) {}
};