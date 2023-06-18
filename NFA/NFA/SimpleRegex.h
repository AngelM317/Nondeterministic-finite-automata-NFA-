#pragma once
#include "Regex.h"
class SimpleRegex:public Regex
{
	void initializeAlphabeth();
public:
	SimpleRegex(const MyString& exp);
	void initializeAutomation() override;
	SharedPtr<Regex> clone() const override;
};

