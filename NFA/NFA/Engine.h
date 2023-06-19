#pragma once
#include "RegexWrap.h"
class Engine
{
private:
	MySet<Pair<RegexWrap,MyString>> automata;
	SharedPtr<RegexWrap> findAutomation(const MyString& name);
	MyString getCommandName(const MyString& command);
	bool isValidCommandName(const MyString& name);
	size_t getCommandParametersCount(const MyString& command);
	MyString getParameter(const MyString& command, size_t index);
	void Exists(const MyString& name);
	void prinhHelp();

	public:
		Engine()=default;
		void Run();
		void createAutomation(MyString& regex, const MyString& name);
		void automationFromFile(const MyString& name, const MyString& nameOfAutomation);
		void saveAutomatioInFle(const MyString& name, const MyString& automationName);
		bool accepts(const MyString& name, const MyString& word);
		void makeDeterm(const MyString& name);
		void minimize(const MyString& name);
		void addUnionOfAutomata(const MyString& name1, const MyString& name2, const MyString& nameOfUnion);
		void addKleenieOfAutomata(const MyString& nameOfAutomation, const MyString& nameOfKleenieAutomation);
		void addConcatenationOfAutomata(const MyString& name1, const MyString& name2, const MyString& nameOfUnion);
		void reverseAutomata(const MyString& name);
		MyString& getRegex(const MyString& name);
		void executeCommand(const MyString& name);
};

