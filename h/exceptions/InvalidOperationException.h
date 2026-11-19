#pragma once
#include "SchoolException.h"
class InvalidOperationException :public SchoolException {
public:
	explicit InvalidOperationException(const std::string& data) :SchoolException("Invalid operation error: " + data) {};
};