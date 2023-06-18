// NFA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Regex.h"
#include "RegexWrap.h"
#include "OperationsWithAutomata.h"


int main()
{
	MyString hmm = "(a)*(b)*ccc + (a)*(b)*";
	RegexWrap ss(hmm);
	std::cout<<ss.getRegex()->getAutomation().accept("aaaaabbbbbcccbbbb");
	NondetemFiniteAutomata test = ss.getRegex()->getAutomation();
	//test.printTransitions();
	MyString agg = test.regexFromAutomation();
	ss.clearWs(agg);
	std::cout << agg;
	RegexWrap rk(agg);
	
	
	


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
