#pragma once
#include"SchoolException.h"
class InvalidDataException :public SchoolException {
public:
	explicit InvalidDataException(const std::string& data) :SchoolException("Incorrect input: " + data) {}
};