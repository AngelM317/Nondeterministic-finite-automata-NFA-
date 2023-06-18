#pragma once
#include "KleeneRegex.h"
#include "ConcatRegex.h"
#include "UnionRegex.h"
#include "SimpleRegex.h"

class RegexWrap
{
private:
	SharedPtr<Regex> regex;
public:
	void clearWs(MyString& text);
	RegexWrap();
	RegexWrap(MyString& exp);
	bool isValidReggex(const MyString& exp) const;
	SharedPtr<Regex>& getRegex();
	
};

