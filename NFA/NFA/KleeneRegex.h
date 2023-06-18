#pragma once
#include "Regex.h"
class KleeneRegex: public Regex
{
	SharedPtr<Regex> regex1;
public:
	KleeneRegex(SharedPtr<Regex> regex1);
	void initializeAutomation() override;
	SharedPtr<Regex> clone()const override;
};

