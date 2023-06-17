#pragma once
#include"Regex.h"
class UnionRegex:public Regex
{
private:
	Regex* regex1;
	Regex* regex2;
	void free();
	void copyFrom(const UnionRegex& other);
	void moveFrom(UnionRegex&& other);
public:
	UnionRegex(Regex* regex1, Regex* regex2);
	UnionRegex(const UnionRegex& other);
	UnionRegex(UnionRegex&& other);
	~UnionRegex();
	UnionRegex& operator=(const UnionRegex& other);
	UnionRegex& operator=(UnionRegex&& other);
	void initializeAutomation() override;
	Regex* clone()const override;
};

