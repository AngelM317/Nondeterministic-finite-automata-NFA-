#pragma once
#include "Regex.h"
class KleeneRegex: public Regex
{
	Regex* regex1;
	void free();
	void copyFrom(const KleeneRegex& other);
	void moveFrom(KleeneRegex&& other);
public:
	KleeneRegex(Regex* regex1);
	KleeneRegex(const KleeneRegex& other);
	KleeneRegex(KleeneRegex&& other);
	~KleeneRegex();
	KleeneRegex& operator=(const KleeneRegex& other);
	KleeneRegex& operator=(KleeneRegex&& other);
	void initializeAutomation() override;
	Regex* clone()const override;
};

