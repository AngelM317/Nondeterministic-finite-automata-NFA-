#pragma once
#include "NondetemFiniteAutomata.h"
namespace
{
	NondetemFiniteAutomata Union(const NondetemFiniteAutomata& automata1, const NondetemFiniteAutomata& automata2)
	{
		NondetemFiniteAutomata toReturn(automata1);
		for (size_t i = 0; i < automata2.getAlphabeth().getSize(); i++)
		{
			toReturn.addLetter(automata2.getAlphabeth().getElements()[i]);
		}
		for (size_t i = 0; i < automata2.getStatesCount(); i++)
		{
			toReturn.addState();
			for (size_t j = 0; j < automata2.getTransitions()[i].getSize(); j++)
			{
				toReturn.addTransition(toReturn.getStatesCount(), automata2.getTransitions()[i][j].getFirst(), automata2.getTransitions()[i][j].getSecond());
			}
		}
		for (size_t i = 0; i < automata2.getFinalStates().getSize(); i++)
		{
			toReturn.makeStateFinal(automata2.getFinalStates().getElements()[i] + automata1.getStatesCount());
		}
		for (size_t i = 0; i < automata2.getStartingStates().getSize(); i++)
		{
			toReturn.makeStateStarting(automata2.getStartingStates().getElements()[i] + automata1.getStatesCount());
		}
		return toReturn;
	}

	NondetemFiniteAutomata Concat(const NondetemFiniteAutomata& automata1, const NondetemFiniteAutomata& automata2)
	{
		NondetemFiniteAutomata toReturn;
		for (size_t i = 0; i < automata2.getAlphabeth().getSize(); i++)
		{
			toReturn.addLetter(automata2.getAlphabeth().[i]);
		}
		for (size_t i = 0; i < automata2.getStatesCount(); i++)
		{
			toReturn.addState();
			for (size_t j = 0; j < automata2.getTransitions()[i].getSize(); j++)
			{
				toReturn.addTransition(toReturn.getStatesCount(), automata2.getTransitions()[i][j].getFirst(), automata2.getTransitions()[i][j].getSecond());
			}
		}
		bool clear = true;
		for (size_t i = 0; i < automata2.getFinalStates().getSize(); i++)
		{
			for (size_t j = 0; j < automata2.getStartingStates().getSize(); j++)
			{
				if (automata2.getFinalStates()[i] == automata2.getStartingStates()[j])
				{
					clear = false;
					break;
				}
			}
			if (!clear)
			{
				break;
			}
		}
		if (clear)
		{
			toReturn.clearFinalStates();
		}
		for (size_t i = 0; i < automata2.getFinalStates().getSize(); i++)
		{
			toReturn.makeStateFinal(automata2.getFinalStates().[i] + automata1.getStatesCount());
		}

		for (size_t i = 0; i < automata1.getFinalStates().getSize(); i++)
		{
			for (size_t j = 0; j < automata2.getStartingStates().getSize(); j++)
			{
				for (size_t s = 0; s < automata2.getTransitions()[automata2.getStartingStates()[j] - 1].getSize(); s++)
				{
					char ch = automata2.getTransitions()[automata2.getStartingStates()[j] - 1][s].getFirst();					//To be more readable!; A little sacrefice
					size_t to = automata2.getTransitions()[automata2.getStartingStates()[j] - 1][s].getSecond();				//To be more readable!;
					size_t from = automata1.getFinalStates()[i];																//To be more readable!;
					toReturn.addTransition(from, ch, to);
				}
			}
		}
		return toReturn;
	}

	NondetemFiniteAutomata Kleene(const NondetemFiniteAutomata& automata1)
	{
		NondetemFiniteAutomata toReturn(automata1);
		toReturn.addState();
		toReturn.makeStateFinal(toReturn.getStatesCount());
		for (size_t i = 0; i < toReturn.getFinalStates().getSize(); i++)
		{
			for (size_t j = 0; j < toReturn.getStartingStates().getSize(); j++)
			{
				for (size_t s = 0; s < toReturn.getTransitions()[toReturn.getStartingStates()[j] - 1].getSize(); s++)
				{
					char ch = toReturn.getTransitions()[toReturn.getStartingStates()[j] - 1][s].getFirst();
					size_t to = toReturn.getTransitions()[toReturn.getStartingStates()[j] - 1][s].getSecond();
					size_t from = automata1.getFinalStates()[i];
					toReturn.addTransition(from, ch, to);
				}
			}
		}
		toReturn.clearStartingStates();
		toReturn.makeStateStarting(toReturn.getStatesCount());
		return toReturn;
	}
}