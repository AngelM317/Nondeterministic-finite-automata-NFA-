#include "UnionRegex.h"
#include "OperationsWithAutomata.h"
#include "SimpleRegex.h"


UnionRegex::UnionRegex(SharedPtr<Regex> regex1, SharedPtr<Regex> regex2)
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


void UnionRegex::initializeAutomation()
{
	this->auotomation = Union(regex1->getAutomation(), regex2->getAutomation());
}

SharedPtr<Regex> UnionRegex::clone() const
{
	return new UnionRegex(*this);
}
