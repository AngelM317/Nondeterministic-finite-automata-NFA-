#include "ConcatRegex.h"
#include "SimpleRegex.h"
#include"OperationsWithAutomata.h"

void ConcatRegex::free()
{
	delete regex1;
	delete regex2;
}

void ConcatRegex::copyFrom(const ConcatRegex& other)
{
	text = other.text;
	auotomation = other.auotomation;
	regex1 = other.regex1->clone();
	regex2 = other.regex1->clone();
}

void ConcatRegex::moveFrom(ConcatRegex&& other)
{
	text = other.text;
	other.text = nullptr;
	auotomation = other.auotomation;
	regex1 = other.regex1;
	regex2 = other.regex2;
	other.regex1 = nullptr;
	other.regex2 = nullptr;
}

ConcatRegex::ConcatRegex(Regex* regex1, Regex* regex2)
{
	if (regex1 == nullptr)
	{
		this->regex1 = new SimpleRegex(nullptr);
	}
	else
	{
		this->regex1 = regex1->clone();
	}
	if (regex2 == nullptr)
	{
		this->regex2 = new SimpleRegex(nullptr);
	}
	else
	{
		this->regex2 = regex2->clone();
	}
	initializeAutomation();
}

ConcatRegex::ConcatRegex(const ConcatRegex& other)
{
	copyFrom(other);
}

ConcatRegex::ConcatRegex(ConcatRegex&& other)
{
	moveFrom(std::move(other));
}

ConcatRegex::~ConcatRegex()
{
	free();
}

ConcatRegex& ConcatRegex::operator=(const ConcatRegex& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ConcatRegex& ConcatRegex::operator=(ConcatRegex&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void ConcatRegex::initializeAutomation()
{
	this->auotomation = Concat(regex1->getAutomation(), regex2->getAutomation());
}

Regex* ConcatRegex::clone() const
{
	return new ConcatRegex(*this);
}
