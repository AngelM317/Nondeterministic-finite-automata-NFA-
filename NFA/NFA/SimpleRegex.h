#pragma once
#include "Regex.h"
class SimpleRegex:public Regex
{
public:
	SimpleRegex(const MyString& text);
	void initializeAutomation() override;
	Regex* clone()const override;
};

