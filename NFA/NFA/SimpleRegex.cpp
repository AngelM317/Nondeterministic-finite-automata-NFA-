#include "SimpleRegex.h"
SimpleRegex::SimpleRegex(const MyString& text)
{
	if (text != nullptr)
	{
		clearWS();
		if (isValidRegex())
		{
			initializeAutomation();
		}
	}
}

void SimpleRegex::initializeAutomation()
{
	if (text != nullptr)
	{
		if (text == "")
		{
			auotomation.addState();
			auotomation.addState();
			for (size_t i = 0; i < auotomation.getAlphabeth().getSize(); i++)
			{
				auotomation.addTransition(1, auotomation.getAlphabeth()[i], 2);
			}
			auotomation.makeStateFinal(1);
			auotomation.makeStateFinal(1);	
		}
		else
		{
			initializeAlphabeth();
			auotomation.addState();
			for (size_t i = 1; i < text.length(); i++)
			{
				auotomation.addState();
				auotomation.addTransition(i, text[i - 1], i + 1);
			}
			auotomation.makeStateFinal(text.length());
			auotomation.makeStateStarting(1);
		}
	}
}

Regex* SimpleRegex::clone() const
{
	return new SimpleRegex(*this);
}
