#pragma once
#include "Vector.hpp"
template <typename T>
class MySet
{
private:
	Vector<T> elements;
public:
	MySet() = default;
	MySet(const Vector<T>& elements);
	size_t getSize() const;
	bool removeElement(T& elemet);
	bool addElement(const T& element);
	bool contains(const T& element) const;
	void unionWith(const MySet& other);
	const Vector<T>& getElements() const;
	bool equalsTo(const MySet<T>& other) const;
	bool operator==(const MySet<T>& other) const;
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	void clear();
};

template<typename T>
MySet<T>::MySet(const Vector<T>& elements)
{
	this->elements = elements;
}

template<typename T>
size_t MySet<T>::getSize() const
{
	return elements.getSize();
}

template<typename T>
bool MySet<T>::removeElement(T& elemnet)
{
	for (size_t i = 0; i < getSize(); i++)
	{
		if (elements[i] == elemnet)
		{
			elements.popAt(i);
			return true;
		}
	}
	return false;
}

template<typename T>
bool MySet<T>::addElement(const T& element)
{
	if (!contains(element))
	{
		elements.pushBack(element);
		return true;
	}
	return false;
}

template<typename T>
bool MySet<T>::contains(const T& element) const
{
	for (size_t i = 0; i < elements.getSize(); i++)
	{
		if (elements[i] == element)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
void MySet<T>::unionWith(const MySet& other)
{
	for (size_t i = 0; i < other.getSize(); i++)
	{
		addElement(other.elements[i]);
	}
}

template<typename T>
const Vector<T>& MySet<T>::getElements() const
{
	return this->elements;
}

template<typename T>
bool MySet<T>::equalsTo(const MySet<T>& other) const
{
	if (getSize() != other.getSize())
	{
		return false;
	}
	for (size_t i = 0; i < other.getSize(); i++)
	{
		if (!this->contains(other[i]))
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool MySet<T>::operator==(const MySet<T>& other) const
{
	return equalsTo(other);
}

template<typename T>
T& MySet<T>::operator[](size_t index)
{
	return elements[index];
}

template<typename T>
const T& MySet<T>::operator[](size_t index) const
{
	return elements[index];
}

template<typename T>
void MySet<T>::clear()
{
	elements.clear();
}


