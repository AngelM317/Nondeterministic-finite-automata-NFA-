#include "Engine.h"
#include <fstream>
#include <iostream>
namespace
{
	void successfulCommand()
	{
		std::cout << "Command executed succefully";
	}
}
void Engine::Exists(const MyString& name)
{
	for (size_t i = 0; i < automata.getSize(); i++)
	{
		if (automata[i].getSecond()==name)
		{
			throw std::exception();
		}
	}
}
RegexWrap& Engine::findAutomation(const MyString& name)
{
	for (size_t i = 0; i < automata.getSize(); i++)
	{
		if (automata[i].getSecond() == name)
		{
			return automata[i].getFirst();
		}
	}
	throw std::exception("Not Found");
}

MyString Engine::getCommandName(const MyString& command)
{
	MyString toReturn = "";
	size_t i = 0;
	while (command[i] != '\0' && command[i] != ' ')
	{
		toReturn += command[i++];
	}
	if (isValidCommandName(toReturn))
	{
		return toReturn;
	}
	throw std::exception("Invalid command\n");
}
void Engine::prinhHelp()
{
	std::cout << "Create <regex> <nameOfAutomation>\nLoadFromFile <fileName> <nameToBeSavedWith>\nSaveInFile <fileName> <nameOfAutomation\nCheckWord <nameOFAutomation> <word>\nDeterminate <NameOFAutomation>\nMinimize <nameOfAutomation>\naddUnionOf <firstAutomationName> <secondAutomationName> <UnionName>\naddConcatenationOf <firstAutomationName> <secondAutomationName> <ConcatenationName>\nAddKleenieOf <automationName> <KleenieName>\nReverse <automationName>\nRegexOf <automationName>\nPrintInfo <automationName>\nMakeTotal <automationName>\n";
}

bool Engine::isValidCommandName(const MyString& name)
{
	if (name == "MakeTotal")
	{
		return true;
	}
	if (name == "SaveInFile")
	{
		return true;
	}
	if (name == "Create")
	{
		return true;
	}
	if (name == "LoadFromFile")
	{
		return true;
	}
	if (name == "CheckWord")
	{
		return true;
	}
	if (name == "Determinate")
	{
		return true;
	}
	if (name == "Minimize")
	{
		return true;
	}
	if (name == "AddUnionOf")
	{
		return true;
	}
	if (name == "AddKleenieOf")
	{
		return true;
	}
	if (name == "AddConcatenationOf")
	{
		return true;
	}
	if (name == "Reverse")
	{
		return true;
	}
	if (name == "RegexOf")
	{
		return true;
	}
	if (name == "help")
	{
		return true;
	}
	if (name == "PrintInfo")
	{
		return true;
	}
	if (name == "IsEmptyLanguage")
	{
		return true;
	}

	return false;
}

size_t Engine::getCommandParametersCount(const MyString& command)
{
	size_t toReturn=0;
	for (size_t i = 0; i < strlen(command.c_str()); i++)
	{
		if (command[i] == ' ')
		{
			toReturn++;
		}
	}
	return toReturn;
}

MyString Engine::getParameter(const MyString& command, size_t index)
{
	MyString toReturn="";
	size_t i = 0;
	size_t j = 0;
	while (j != index)
	{
		if (command[i++] == ' ')
		{
			j++;
		}
	}
	while (command[i] != ' ' && command[i] != '\0')
	{
		toReturn += command[i];
		i++;
	}
	return toReturn;
	
}

void Engine::Run()
{
	std::cout << "Welcome!\n";
	prinhHelp();
	while (1)
	{
		MyString command="";
		command.setLength(101);
		std::cin.getline((char*)command.c_str(), 100);
		executeCommand(command);
	}
}

void Engine::createAutomation(MyString& regex, const MyString& name)
{
	try
	{
		Exists(name);
		MyString newRegex = "(" + regex + ")";
		automata.addElement(Pair<RegexWrap, MyString>(RegexWrap(newRegex), name));
		successfulCommand();
	}
	catch(std::exception)
	{
		std::cout << "Automation with this name already exists\n";
	}
	
}

void Engine::automationFromFile(const MyString& name, const MyString& nameOfAutomation)
{
	std::ifstream file(name.c_str(), std::ios::binary);

	if (file.is_open())
	{
		MyString regex;
		file >> regex;
		createAutomation(regex, nameOfAutomation);
	}
	else
	{
		std::cout << "File not found\n";
	}

}

void Engine::saveAutomatioInFle(const MyString& name, const MyString& automationName)
{
	try
	{
		std::ofstream file;
		file.open(name.c_str());
		file<<findAutomation(name).getRegex()->getText();
		successfulCommand();
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

bool Engine::accepts(const MyString& name, const MyString& word)
{
	try
	{
		return findAutomation(name).getRegex()->getAutomation().accept(word);
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

void Engine::makeDeterm(const MyString& name)
{
	try
	{
		findAutomation(name).getRegex()->getAutomation().convertToDfa();
		successfulCommand();
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

void Engine::makeTotal(const MyString& name)
{
	try
	{
		findAutomation(name).getRegex()->getAutomation().makeTotal();
		successfulCommand();
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

void Engine::minimize(const MyString& name)
{
	try
	{
		findAutomation(name).getRegex()->getAutomation().minimize();
		successfulCommand();
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

void Engine::addUnionOfAutomata(const MyString& name1, const MyString& name2, const MyString& nameOfUnion)
{
	try
	{
		MyString unionRegex = findAutomation(name1).getRegex()->getText() + "+"+ findAutomation(name2).getRegex()->getText();
		createAutomation(unionRegex, nameOfUnion);
		successfulCommand();
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

void Engine::addKleenieOfAutomata(const MyString& nameOfAutomation, const MyString& nameOfKleenieAutomation)
{
	try
	{
		MyString kleenieRegex = "(";
		kleenieRegex = kleenieRegex+ findAutomation(nameOfAutomation).getRegex()->getText() + ")*";
		createAutomation(kleenieRegex, nameOfKleenieAutomation);
		successfulCommand();
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

void Engine::addConcatenationOfAutomata(const MyString& name1, const MyString& name2, const MyString& nameOFConcat)
{
	try
	{
		MyString unionRegex = findAutomation(name1).getRegex()->getText() + findAutomation(name2).getRegex()->getText();
		createAutomation(unionRegex, nameOFConcat);
		successfulCommand();
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

void Engine::reverseAutomata(const MyString& name)
{
	try
	{
		findAutomation(name).getRegex()->getAutomation().reverseAutomata();
		successfulCommand();
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

MyString& Engine::getRegex(const MyString& name)
{
	try
	{
		MyString toReturn=findAutomation(name).getRegex()->getText();
		return toReturn;
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

void Engine::executeCommand(const MyString& command)
{
	try
	{
		MyString type= getCommandName(command);
		if (type == "SaveInFile"&&getCommandParametersCount(command)==2)
		{
			saveAutomatioInFle(getParameter(command, 1), getParameter(command, 2));
		} 
		else if(type == "Create" && getCommandParametersCount(command) == 2)
		{
			MyString parameter1 = getParameter(command, 1);
			createAutomation(parameter1, getParameter(command, 2));
		} 
		else if (type == "LoadFromFile" && getCommandParametersCount(command) == 2)
		{
			automationFromFile(getParameter(command, 1), getParameter(command, 2));
		}	
		else if (type == "CheckWord" && getCommandParametersCount(command) == 2)
		{
			
			if (accepts(getParameter(command, 1), getParameter(command, 2)))
			{
				std::cout << "true\n";
			}
			else
			{
				std::cout << "false\n";
			}
		}
		else if (type == "Determinate" && getCommandParametersCount(command) == 1)
		{
			makeDeterm(getParameter(command, 1));
		}
		else if (type == "Minimize" && getCommandParametersCount(command) == 1)
		{
			minimize(getParameter(command, 1));
		}
		else if (type == "AddUnionOf" && getCommandParametersCount(command) == 3)
		{
			addUnionOfAutomata(getParameter(command, 1), getParameter(command, 2), getParameter(command, 3));
		}
		else if (type == "AddKleenieOf" && getCommandParametersCount(command) == 2)
		{
			addKleenieOfAutomata(getParameter(command, 1), getParameter(command, 2));
		}
		else if (type == "AddConcatenationOf" && getCommandParametersCount(command) == 3)
		{
			addConcatenationOfAutomata(getParameter(command, 1), getParameter(command, 2), getParameter(command, 3));
		}
		else if (type == "Reverse" && getCommandParametersCount(command) == 1)
		{
			reverseAutomata(getParameter(command, 1));
		}
		else if (type == "RegexOf" && getCommandParametersCount(command) == 1)
		{
			getRegex(getParameter(command, 1));
		}
		else if (type == "PrintInfo" && getCommandParametersCount(command) == 1)
		{
			PrintInfo(getParameter(command, 1));
		}
		else if (type == "help")
		{
			prinhHelp();
		}
		else if (type == "MakeTotal" && getCommandParametersCount(command) == 1)
		{
			makeTotal(getParameter(command, 1));
		}
		else if (type == "MakeTotal" && getCommandParametersCount(command) == 1)
		{
			isEmptyLanguage(getParameter(command, 1));
		}
		else
		{
			std::cout << "Invalid parameters for the command: " << command;
		}
		std::cout << "\n";
	}
	catch (std::exception a)
	{
		std::cout << a.what();
	}
}

void Engine::PrintInfo(const MyString& name)
{
	std::cout << "Starting States: ";
	NondetemFiniteAutomata temp = findAutomation(name).getRegex()->getAutomation();
	for (size_t i = 0; i < temp.getStartingStates().getSize(); i++)
	{
		std::cout<<temp.getStartingStates()[i]<<" ";
	}
	std::cout << "Final States: ";
	for (size_t i = 0; i < temp.getFinalStates().getSize(); i++)
	{
		std::cout << temp.getFinalStates()[i] << " ";
	}
	std::cout << "\nTransitions are: \n";
	temp.printTransitions();
}

void Engine::isEmptyLanguage(const MyString& name)
{
	if (findAutomation(name).getRegex()->getAutomation().isEmptyLanguage())
	{
		std::cout << "True\n";
	}
	else
	{
		std::cout << "False\n";
	}
}
