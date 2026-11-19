#pragma once
#include "SchoolException.h"
class AgeRestrictionException :public SchoolException {
public:
	explicit AgeRestrictionException(const std::string& data) :SchoolException("Age restriction for user: " + data) {};
};