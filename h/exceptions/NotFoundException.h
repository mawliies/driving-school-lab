#pragma once
#include "SchoolException.h"
class NotFoundException :public SchoolException {
public:
	explicit NotFoundException(const std::string& data) :SchoolException("No object found: " + data) {};
};