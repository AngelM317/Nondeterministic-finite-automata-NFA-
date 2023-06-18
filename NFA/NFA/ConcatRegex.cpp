#include "ConcatRegex.h"
#include "SimpleRegex.h"
#include"OperationsWithAutomata.h"


ConcatRegex::ConcatRegex(const SharedPtr<Regex> regex1,const SharedPtr<Regex> regex2)
{
	if (regex1 == nullptr)
	{
		this->regex1 = new SimpleRegex("~");
	}
	else
	{
		this->regex1 = regex1->clone();
	}
	if (regex2 == nullptr)
	{
		this->regex2 = new SimpleRegex("~");
	}
	else
	{
		this->regex2 = regex2->clone();
	}
	initializeAutomation();
}


void ConcatRegex::initializeAutomation()
{
	this->auotomation = Concat(regex1->getAutomation(), regex2->getAutomation());
}

SharedPtr<Regex> ConcatRegex::clone() const
{
	return new ConcatRegex(*this);
}
