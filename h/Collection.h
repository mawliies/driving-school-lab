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
	Collection(const Collection& other) {
		size = other.size;
		capacity = other.capacity;
		if (capacity > 0) {
			data = new T[capacity];
			for (int i = 0; i < size; i++)
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
				for (int i = 0; i < size; i++)
					data[i] = other.data[i];
			}
			else 
				data = nullptr;
		}
		return *this;
	}
	int getSize() const{
		return size;
	}
	T get(int i) const{
		return data[i];
	}
	void add(const T& item) {
		if (size == capacity) {
			int newCapacity = (capacity == 0) ? 4 : capacity * 2;
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
	int findElement(const T& target) const{
		for (int i = 0; i < getSize(); i++)
			if (data[i] == target)
				return i;
		return -1;
	}
	void removeAt(int idx) {
		if (idx < 0 || idx >= size) 
			return;
		for (int i = idx; i < size - 1; i++)
			data[i] = data[i + 1];
		size--;
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
		clear();
	}
};
template <typename T>
T findBest(Collection<T> collection) {
	if (collection.getSize() == 0)
		return T();
	T best = collection.get(0);
	for (int i = 1; i < collection.getSize(); i++)
		if (*collection.get(i) > *best)
			best = collection.get(i);
	return best;
}