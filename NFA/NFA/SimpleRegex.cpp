#include "SimpleRegex.h"
#include "SharedPtr.hpp"
void SimpleRegex::initializeAlphabeth()
{
	for (size_t i = 0; i < text.length(); i++)
	{		
		auotomation.addLetter(text[i]);	
	}
}
SimpleRegex::SimpleRegex(const MyString& exp)
{
	text = exp;
	if (text != "~")
	{
		initializeAutomation();
	}
}

void SimpleRegex::initializeAutomation()
{
	if (text != "~")
	{
		if (text == "")
		{
			auotomation.addState();
			auotomation.makeStateStarting(1);
			auotomation.makeStateFinal(1);	
		}
		else
		{
			initializeAlphabeth();
			auotomation.addState();
			for (size_t i = 0; i < text.length(); i++)
			{
				auotomation.addState();
				auotomation.addTransition(i+1, text[i], i + 2);
			}
			auotomation.makeStateFinal(text.length()+1);
			auotomation.makeStateStarting(1);
		}
	}
	else
	{
		auotomation.addState();
		auotomation.makeStateStarting(1);
	}
}

SharedPtr<Regex> SimpleRegex::clone() const
{
	return new SimpleRegex(*this);
}
