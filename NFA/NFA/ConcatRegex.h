#pragma once
#include"Regex.h"
class ConcatRegex : public Regex
{
private:
	SharedPtr<Regex> regex1;
	SharedPtr<Regex> regex2;

public:
	ConcatRegex(const SharedPtr<Regex> regex1, const SharedPtr<Regex> regex2);
	void initializeAutomation() override;
	SharedPtr<Regex> clone() const override;
};

