#pragma once
#include "SchoolException.h"
class DuplicateDataException :public SchoolException {
public:
	explicit DuplicateDataException(const std::string& data) :SchoolException("User " + data + " is already have been registrated.") {};
};