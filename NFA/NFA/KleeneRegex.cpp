#include "KleeneRegex.h"
#include "SimpleRegex.h"
#include "OperationsWithAutomata.h"

KleeneRegex::KleeneRegex(SharedPtr<Regex> regex1)
{
	if (regex1 == nullptr)
	{
		this->regex1 = new SimpleRegex("~");
	}
	else
	{
		this->regex1 = regex1->clone();
	}
	initializeAutomation();
}


void KleeneRegex::initializeAutomation()
{
	this->auotomation = Kleene(regex1->getAutomation());
}

SharedPtr<Regex> KleeneRegex::clone() const
{
	return new KleeneRegex(*this);
}
