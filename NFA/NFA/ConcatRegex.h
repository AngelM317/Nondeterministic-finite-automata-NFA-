#pragma once
#include"Regex.h"
class ConcatRegex : public Regex
{
private:
	Regex* regex1;
	Regex* regex2;
	void free();
	void copyFrom(const ConcatRegex& other);
	void moveFrom(ConcatRegex&& other);
public:
	ConcatRegex(Regex* regex1, Regex* regex2);
	ConcatRegex(const ConcatRegex& other);
	ConcatRegex(ConcatRegex&& other);
	~ConcatRegex();
	ConcatRegex& operator=(const ConcatRegex& other);
	ConcatRegex& operator=(ConcatRegex&& other);
	void initializeAutomation() override;
	Regex* clone()const override;
};

