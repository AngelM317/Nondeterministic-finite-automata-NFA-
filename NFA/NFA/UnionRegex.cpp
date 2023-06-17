#include "UnionRegex.h"
#include "OperationsWithAutomata.h"
#include "SimpleRegex.h"
void UnionRegex::free()
{
	delete regex1;
	delete regex2;
}

void UnionRegex::copyFrom(const UnionRegex& other)
{
	text = other.text;
	auotomation = other.auotomation;
	regex1 = other.regex1->clone();
	regex2 = other.regex1->clone();
}

void UnionRegex::moveFrom(UnionRegex&& other)
{
	text = other.text;
	other.text = nullptr;
	auotomation = other.auotomation;
	regex1 = other.regex1;
	regex2 = other.regex2;
	other.regex1 = nullptr;
	other.regex2 = nullptr;
}

UnionRegex::UnionRegex(Regex* regex1, Regex* regex2)
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

UnionRegex::UnionRegex(const UnionRegex& other)
{
	copyFrom(other);
}

UnionRegex::UnionRegex(UnionRegex&& other)
{
	moveFrom(std::move(other));
}

UnionRegex::~UnionRegex()
{
	free();
}

UnionRegex& UnionRegex::operator=(const UnionRegex& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

UnionRegex& UnionRegex::operator=(UnionRegex&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void UnionRegex::initializeAutomation()
{
	this->auotomation = Union(regex1->getAutomation(), regex2->getAutomation());
}

Regex* UnionRegex::clone() const
{
	return new UnionRegex(*this);
}
