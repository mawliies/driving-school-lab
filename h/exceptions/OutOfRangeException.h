#pragma once
#include "SchoolException.h"
class OutOfRangeException :public SchoolException {
public:
	explicit OutOfRangeException(int i, int size) :SchoolException("Index " + std::to_string(i) + " not in the range [0..." + std::to_string(size) + "]") {};
};