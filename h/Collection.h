#pragma once
#include <stdio.h>
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
	void getSize() const{
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
	void clear() {
		delete[]data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}
	void print()const {
		for (int i = 0; i < size; i++)
			std::cout << data[i] << endl;
	}
	~Collection() {
		delete[] data;
	};
};