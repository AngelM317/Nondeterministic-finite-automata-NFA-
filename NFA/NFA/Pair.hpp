//This uses code from: https://github.com/GeorgiTerziev02/Object-oriented_programming_FMI/blob/05dd57259d970cd8a970dd185f5b4829556e2cf2/Sem.%2013/Solutions/Pair/Pair.hpp#L4
#pragma once

template<typename T, typename D>
class Pair
{
	T first;
	D second;
public:
	Pair() = default;
	Pair(const T& first, const D& second);
	const T& getFirst() const;
	const D& getSecond() const;
	T& getFirst();
	D& getSecond();

	void setFirst(const T& newValue);
	void setSecond(const D& newValue);
	bool operator==(const Pair<T, D>other) const;
};

template<typename T, typename D>
Pair<T, D>::Pair(const T& first, const D& second) : first(first), second(second)
{}

template<typename T, typename D>
const T& Pair<T, D>::getFirst() const
{
	return first;
}
template<typename T, typename D>
const D& Pair<T, D>::getSecond() const
{
	return second;
}

template<typename T, typename D>
T& Pair<T, D>::getFirst()
{
	return first;
}

template<typename T, typename D>
D& Pair<T, D>::getSecond()
{
	return second;
}

template<typename T, typename D>
void Pair<T, D>::setFirst(const T& newValue)
{
	first = newValue;
}

template<typename T, typename D>
void Pair<T, D>::setSecond(const D& newValue)
{
	second = newValue;
}

template<typename T, typename D>
inline bool Pair<T, D>::operator==(const Pair<T, D> other) const
{
	return this->first==other.first&&this->second==other.second;
}
