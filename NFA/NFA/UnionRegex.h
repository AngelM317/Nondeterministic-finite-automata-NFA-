#pragma once
#include"Regex.h"
class UnionRegex:public Regex
{
private:
	SharedPtr<Regex> regex1;
	SharedPtr<Regex> regex2;
public:
	UnionRegex(SharedPtr<Regex> regex1, SharedPtr<Regex> regex2);
	void initializeAutomation() override;
	SharedPtr<Regex> clone()const override;
};

