#pragma once
#include "NondetemFiniteAutomata.h"
class Regex
{
	protected:
	NondetemFiniteAutomata auotomation;
	MyString text = nullptr;
	void initializeAlphabeth();
	void clearWS();
public:
	const MyString& getText() const;
	const NondetemFiniteAutomata& getAutomation() const;
	virtual Regex* clone() const = 0;
	virtual ~Regex() = default;
	void virtual initializeAutomation() = 0;
	bool isValidRegex() const;
	bool isEmpty() const;
};

