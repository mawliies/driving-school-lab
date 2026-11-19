#pragma once
#include <iostream>
#include <stdexcept>
#include "AllExceptions.h"

template <typename T>
class Collection {
private:
	T* data;
	int capacity;
	int size;

	void validateInvariants() const {
		if (size < 0 || capacity < 0 || size > capacity) {
			throw std::logic_error("Collection internal state corrupted");
		}
	}

public:
	Collection() : data(nullptr), capacity(0), size(0) {}

	Collection(const Collection& other) : data(nullptr), capacity(0), size(0) {
		other.validateInvariants();
		if (other.capacity > 0) {
			data = new T[other.capacity];
			capacity = other.capacity;
			size = other.size;
			for (int i = 0; i < size; i++) {
				data[i] = other.data[i];
			}
		}
	}

	Collection& operator=(const Collection& other) {
		if (this != &other) {
			other.validateInvariants();
			T* newData = nullptr;
			if (other.capacity > 0) {
				newData = new T[other.capacity];
				for (int i = 0; i < other.size; i++) {
					newData[i] = other.data[i];
				}
			}
			delete[] data;
			data = newData;
			capacity = other.capacity;
			size = other.size;
		}
		return *this;
	}

	int getSize() const {
		return (size < 0) ? 0 : size;
	}

	T get(int i) const {
		if (size <= 0 || i < 0 || i >= size || data == nullptr) {
			throw OutOfRangeException(i, (size < 0) ? 0 : size);
		}
		return data[i];
	}

	void add(const T& item) {
		if (size < 0) {
			size = 0;
		}
		if (capacity < size) {
			capacity = size;
		}
		if (data == nullptr || size >= capacity) {
			int newCapacity = (capacity <= 0) ? 4 : capacity * 2;
			T* newData = new T[newCapacity];
			for (int i = 0; i < size; i++) {
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
			capacity = newCapacity;
		}
		data[size] = item;
		size++;
	}

	int findElement(const T& target) const {
		if (size <= 0 || data == nullptr) {
			return -1;
		}
		for (int i = 0; i < size; i++) {
			if (data[i] == target) {
				return i;
			}
		}
		return -1;
	}

	void removeAt(int idx) {
		if (size <= 0 || idx < 0 || idx >= size || data == nullptr) {
			throw OutOfRangeException(idx, (size < 0) ? 0 : size);
		}
		for (int i = idx; i < size - 1; i++) {
			data[i] = data[i + 1];
		}
		size--;
	}

	void clear() {
		delete[] data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}

	void print() const {
		if (size <= 0 || data == nullptr) {
			throw NotFoundException("Collection is empty, nothing to print.\n");
		}
		for (int i = 0; i < size; i++) {
			std::cout << data[i] << std::endl;
		}
	}

	~Collection() {
		clear();
	}
};

template <typename T>
T findBest(Collection<T>& collection) {
	int n = collection.getSize();
	if (n <= 0) {
		throw NotFoundException("Cannot find best element in an empty collection.\n");
	}
	T best = collection.get(0);
	for (int i = 1; i < n; i++) {
		if (*collection.get(i) > *best) {
			best = collection.get(i);
		}
	}
	return best;
}