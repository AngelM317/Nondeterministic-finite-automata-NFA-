#include "KleeneRegex.h"
#include "SimpleRegex.h"
#include "OperationsWithAutomata.h"
void KleeneRegex::free()
{
	delete regex1;
}

void KleeneRegex::copyFrom(const KleeneRegex& other)
{
	text = other.text;
	auotomation = other.auotomation;
	regex1 = other.regex1->clone();
}

void KleeneRegex::moveFrom(KleeneRegex&& other)
{
	text = other.text;
	other.text = nullptr;
	auotomation = other.auotomation;
	regex1 = other.regex1;
	other.regex1 = nullptr;
}

KleeneRegex::KleeneRegex(Regex* regex1)
{
	if (regex1 == nullptr)
	{
		this->regex1 = new SimpleRegex(nullptr);
	}
	else
	{
		this->regex1 = regex1->clone();
	}
	initializeAutomation();
}

KleeneRegex::KleeneRegex(const KleeneRegex& other)
{
	copyFrom(other);
}

KleeneRegex::KleeneRegex(KleeneRegex&& other)
{
	moveFrom(std::move(other));
}

KleeneRegex::~KleeneRegex()
{
	free();
}

KleeneRegex& KleeneRegex::operator=(const KleeneRegex& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

KleeneRegex& KleeneRegex::operator=(KleeneRegex&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void KleeneRegex::initializeAutomation()
{
	this->auotomation = Kleene(regex1->getAutomation());
}

Regex* KleeneRegex::clone() const
{
	return new KleeneRegex(*this);
}
