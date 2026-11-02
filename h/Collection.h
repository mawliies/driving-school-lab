#pragma once
#include <iostream>
template <typename T>
class Collection {
private:
	T* data;
	int capacity;
	int size;
public:
	Collection() {
		data = nullptr;
		capacity = 0;
		size = 0;
	}
	int getSize() {
		return size;
	}
	T get(int i) {
		return data[i];
	}
	void add(const T& item) {
		if (size == capacity) {
			int newCapacity = capacity + 1;
			T* newData = new T[newCapacity];
			for (int i = 0; i < size; i++)
				newData[i] = data[i];
			delete[] data;
			data = newData;
			capacity = newCapacity;
		}
		data[size] = item;
		size++;
	}
	int findElement(const Collection<T>& collection, const T& target) {
		for (int i = 0; i < getSize(); i++)
			if (collection[i] == target)
				return i;
		return -1;
	}
	void clear() {
		delete[]data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}
	void print()const {
		for (int i = 0; i < size; i++)
			std::cout << data[i] << std::endl;
	}
	~Collection() {
		delete[] data;
	};
};