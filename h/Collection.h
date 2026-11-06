#pragma once
#include <iostream>
#include <cstddef> 

template <typename T>
class Collection {
private:
	T* data;
	size_t capacity; 
	size_t size;     
public:
	Collection() {
		data = nullptr;
		capacity = 0;
		size = 0;
	}
	Collection(const Collection& other) {
		size = other.size;
		capacity = other.capacity;
		if (capacity > 0) {
			data = new T[capacity];
			for (size_t i = 0; i < size; i++) 
				data[i] = other.data[i];
		}
		else
			data = nullptr;
	}
	Collection& operator=(const Collection& other) {
		if (this != &other) {
			delete[] data;
			size = other.size;
			capacity = other.capacity;
			if (capacity > 0) {
				data = new T[capacity];
				for (size_t i = 0; i < size; i++)
					data[i] = other.data[i];
			}
			else
				data = nullptr;
		}
		return *this;
	}
	size_t getSize() const {
		return size;
	}
	T get(size_t i) const { 
		if (i >= size || data == nullptr) return T();
		return data[i];
	}
	void add(const T& item) {
		if (size >= capacity) {
			size_t newCapacity = (capacity == 0) ? 4 : capacity * 2;
			T* newData = new T[newCapacity];
			for (size_t i = 0; i < size; i++)
				newData[i] = data[i];
			delete[] data;
			data = newData;
			capacity = newCapacity;
		}
		if (data != nullptr && size < capacity) {
			data[size] = item;
			size++;
		}
	}
	int findElement(const T& target) const { 
		for (size_t i = 0; i < size; i++)
			if (data[i] == target)
				return static_cast<int>(i);
		return -1;
	}
	void removeAt(int idx) {
		if (idx < 0 || static_cast<size_t>(idx) >= size)
			return;
		for (size_t i = static_cast<size_t>(idx); i < size - 1; i++)
			data[i] = data[i + 1];
		size--;
	}
	void clear() {
		delete[] data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}
	void print() const {
		for (size_t i = 0; i < size; i++)
			std::cout << data[i] << std::endl;
	}
	~Collection() {
		clear();
	}
};

template <typename T>
T findBest(Collection<T>& collection) {
	if (collection.getSize() == 0)
		return T();
	T best = collection.get(0);
	for (size_t i = 1; i < collection.getSize(); i++)
		if (*collection.get(i) > *best)
			best = collection.get(i);
	return best;
}