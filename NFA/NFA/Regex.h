#pragma once
#include "NondetemFiniteAutomata.h"
#include "UniquePointer.hpp"
#include "SharedPtr.hpp"
class Regex
{
	protected:
	NondetemFiniteAutomata auotomation;
	MyString text = "~";
public:
	const MyString& getText() const;
	NondetemFiniteAutomata& getAutomation();
	virtual SharedPtr<Regex> clone() const = 0;
	virtual ~Regex() = default;
	void virtual initializeAutomation() = 0;
	bool isEmpty() const;
	void setText(const MyString&);

};

