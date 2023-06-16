#include "NondetemFiniteAutomata.h"
#include <exception>

namespace
{

	bool hasTransitionWithLetter(size_t state, char ch, const Vector<Vector<Pair<char, size_t>>>& transitions)
	{
		for (size_t i = 0; i < transitions[state - 1].getSize(); i++)
		{
			if (transitions[state - 1][i].getFirst() == ch)
			{
				return true;
			}
		}
		return false;
	}

	int indexOfState(MySet<MySet<size_t>> states, MySet<size_t> state)
	{
		for (size_t i = 0; i < states.getSize(); i++)
		{
			if (state == states[i])
			{
				return i;
			}
		}
		return -1;
	}
	bool areValidTransitions(const Vector<Vector<Pair<char, size_t>>>& tranistions, const MySet<char>& alphabeth, size_t states)
	{
		if (tranistions.getSize() != states)
		{
			return false;
		}
		for (size_t i = 0; i < tranistions.getSize(); i++)
		{
			for (size_t j = 0; j < tranistions.getSize(); j++)
			{
				if (!(alphabeth.contains(tranistions[i][j].getFirst()) || (tranistions[i][j].getSecond() > states)))
				{
					return false;
				}
			}
		}
		return true;
	}
}
void NondetemFiniteAutomata::decreaseStatesFromIndex(size_t index)
{

	transitions.popAt(index);
	for (size_t i = index; i < states.getSize(); i++)
	{
		states[i]--;
	}
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		for (size_t j = 0; j < transitions[i].getSize(); j++)
		{
			if (transitions[i][j].getSecond() > index)
			{
				transitions[i][j].setSecond(transitions[i][j].getSecond() - 1);
			}
		}
	}
}

void NondetemFiniteAutomata::accesibleStatesFrom(MySet<size_t>& accessedStates, size_t state) const
{
	accessedStates.addElement(state);
	for (size_t i = 0; i < transitions[state - 1].getSize(); i++)
	{
		if (!accessedStates.contains(transitions[state - 1][i].getSecond()))
		{
			accesibleStatesFrom(accessedStates, transitions[state - 1][i].getSecond());
		}
	}
}


void NondetemFiniteAutomata::setTransitions(Vector<Vector<Pair<char, size_t>>>& transitions)
{
	areValidTransitions(transitions, this->alphabeth, getStatesCount());
	this->transitions = transitions;
}

void NondetemFiniteAutomata::setStates(const Vector<size_t>& states)
{
	this->states = states;
}

const MySet<char>& NondetemFiniteAutomata::getAlphabeth() const
{
	return this->alphabeth;
}

const MySet<size_t>& NondetemFiniteAutomata::getStartingStates() const
{
	return this->startingStates;
}

const Vector<Vector<Pair<char, size_t>>>& NondetemFiniteAutomata::getTransitions() const
{
	return transitions;
}

void NondetemFiniteAutomata::addLetter(char letter)
{
	alphabeth.addElement(letter);
}

const MySet<size_t>& NondetemFiniteAutomata::getFinalStates() const
{
	return this->finalStates;
}
void NondetemFiniteAutomata::addState()
{
	states.pushBack(states.getSize() + 1);
	Vector<Pair<char, size_t>> newTrans;
	errorStates.addElement(states.getSize());
	transitions.pushBack(newTrans);
}

void NondetemFiniteAutomata::removeState(size_t state)
{
	if (state > states.getSize())
	{
		throw std::exception("Invalid state");
	}
	else
	{
		decreaseStatesFromIndex(state - 1);
		states.popAt(state - 1);
	}
}

void NondetemFiniteAutomata::removeUnaccessibleStates()
{
	MySet<size_t> allAccessibleStates;
	for (size_t i = 0; i < startingStates.getSize(); i++)
	{
		MySet<size_t> accessibleFromCertainStart;
		accesibleStatesFrom(accessibleFromCertainStart, startingStates[i]);
		allAccessibleStates.unionWith(accessibleFromCertainStart);
	}
	for (size_t i = 0; i < states.getSize(); i++)
	{
		if (!allAccessibleStates.contains(states[i]))
		{
			for (size_t j = 0; j < allAccessibleStates.getSize(); j++)
			{
				if (allAccessibleStates[j] > states[i])
				{
					allAccessibleStates[j]--;
				}
			}
			removeState(states[i]);
			i--;
		}
	}
}
void NondetemFiniteAutomata::makeStateFinal(size_t state)
{
	if (states.getSize() < state)
	{
		throw std::exception("State doesnt exist");
	}
	else
	{
		errorStates.removeElement(state);
		finalStates.addElement(state);
	}
}

void NondetemFiniteAutomata::makeStateStarting(size_t state)
{
	if (states.getSize() < state)
	{
		throw std::exception("State doesnt exist");
	}
	else
	{
		startingStates.addElement(state);
	}
}

void NondetemFiniteAutomata::addTransition(size_t from, char letter, size_t to)
{
	if (states.getSize() < from || states.getSize() < to)
	{
		throw std::exception("State doesnt exist");
	}
	else
	{
		if (!alphabeth.contains(letter))
		{
			throw std::exception("The letter is not in the alpabeth");
		}
		else
		{
			if (from != to && errorStates.contains(from))
			{
				errorStates.removeElement(from);
			}
			Pair<char, size_t> temp(letter, to);
			transitions[from - 1].pushBack(temp);
		}
	}
}

size_t NondetemFiniteAutomata::getStatesCount() const
{
	return states.getSize();
}

bool NondetemFiniteAutomata::isStartingState(size_t state) const
{
	return startingStates.contains(state);
}

bool NondetemFiniteAutomata::isFinalState(size_t state) const
{
	return finalStates.contains(state);
}

bool NondetemFiniteAutomata::isEmptyLanguage() const
{
	for (size_t i = 0; i < startingStates.getSize(); i++)
	{
		MySet<size_t> accessedFromStart;
		accesibleStatesFrom(accessedFromStart, startingStates.getElements()[i]);
		for (size_t i = 0; i < accessedFromStart.getSize(); i++)
		{
			if (isFinalState(accessedFromStart.getElements()[i]))
			{
				return false;
			}
		}
	}


	return true;
}

bool NondetemFiniteAutomata::accept(const MyString& word) const
{
	for (size_t i = 0; i < startingStates.getSize(); i++)
	{
		if (isAcceptedFromState(startingStates[i], word, *this))
		{
			return true;
		}
	}
	return false;
}

void NondetemFiniteAutomata::clearFinalStates()
{
	finalStates.clear();
}

void NondetemFiniteAutomata::clearStartingStates()
{
	startingStates.clear();
}

void NondetemFiniteAutomata::clearAutomata()
{
	clearFinalStates();
	clearStartingStates();
	states.clear();
	transitions.clear();
}

void NondetemFiniteAutomata::printTransitions() const
{
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		std::cout << i + 1 << ": ";
		for (size_t j = 0; j < transitions[i].getSize(); j++)
		{
			std::cout << transitions[i][j].getFirst() << " " << transitions[i][j].getSecond() << " | ";
		}
		std::cout << std::endl;
	}
}

void NondetemFiniteAutomata::makeTotal()
{
	addState();
	size_t efectiveStates = getStatesCount();
	for (size_t i = 0; i < efectiveStates; i++)
	{
		for (size_t j = 0; j < alphabeth.getSize(); j++)
		{
			if (!hasTransitionWithLetter(i + 1, alphabeth.getElements()[j], transitions))
			{
				addTransition(i + 1, alphabeth.getElements()[j], getStatesCount());
			}
		}
	}
}

void NondetemFiniteAutomata::convertToDfa()
{
	//makeTotal();
	Vector<Vector<Pair<char, size_t>>> newTransitions;
	MySet<MySet<size_t>> newStates;
	MySet<size_t> newFinalStates;
	MySet<size_t> newErrorList;
	newStates.addElement(this->startingStates);
	for (size_t i = 0; i < startingStates.getSize(); i++)
	{
		if (isFinalState(startingStates[i]))
		{
			newFinalStates.addElement(newStates.getSize());
			break;
		}
	}
	newTransitions.pushBack(Vector<Pair<char, size_t >>());
	bool changed = true;
	size_t startingIndex = 0;
	while (changed)
	{
		changed = false;
		size_t countOfNewStates = newStates.getSize();
		for (size_t i = startingIndex; i < countOfNewStates; i++)
		{
			for (size_t j = 0; j < alphabeth.getSize(); j++)
			{
				MySet<size_t> set;
				MySet<size_t> error;
				bool isFinal = false;
				for (size_t s = 0; s < newStates[i].getSize(); s++)
				{
					for (size_t k = 0; k < transitions[newStates[i][s] - 1].getSize(); k++)
					{
						Pair<char, size_t> currPair = transitions[newStates[i][s] - 1][k];
						if (currPair.getFirst() == alphabeth[j])
						{
							if (!errorStates.contains(currPair.getSecond()))
							{
								set.addElement(currPair.getSecond());
								if (isFinalState(currPair.getSecond()))
								{
									isFinal = true;
								}
							}
							else
							{
								error.addElement(currPair.getSecond());
							}

						}
					}
				}
				if (set.getSize() != 0 || error.getSize() != 0)
				{
					if (!newStates.contains(set))
					{
						newStates.addElement(set);
						if (set.getSize() == 0)
						{
							newErrorList.addElement(newStates.getSize());
						}
						if (isFinal) { newFinalStates.addElement(newStates.getSize()); }
						newTransitions.pushBack(Vector<Pair<char, size_t>>());
						newTransitions[i].pushBack(Pair<char, size_t>(alphabeth[j], newStates.getSize()));
						changed = true;
					}
					else
					{
						newTransitions[i].pushBack(Pair<char, size_t>(alphabeth[j], indexOfState(newStates, set) + 1));
					}
				}
			}
		}
		startingIndex = countOfNewStates;
	}
	clearAutomata();
	for (size_t i = 0; i < newStates.getSize(); i++)
	{
		addState();
	}
	transitions.clear();
	transitions = newTransitions;
	finalStates = newFinalStates;
	startingStates.addElement(1);
	errorStates = newErrorList;
}

void NondetemFiniteAutomata::reverseAutomata()
{
	Vector<Vector<Pair<char, size_t>>> newTransitions;
	for (size_t i = 0; i < states.getSize(); i++)
	{
		newTransitions.pushBack(Vector<Pair<char, size_t>>());
	}
	for (size_t i = 0; i < transitions.getSize(); i++)
	{
		for (size_t j = 0; j < transitions[i].getSize(); j++)
		{
			newTransitions[transitions[i][j].getSecond() - 1].pushBack(Pair<char, size_t>(transitions[i][j].getFirst(), i + 1));
		}
	}
	transitions.clear();
	transitions = newTransitions;
	MySet<size_t> temp = finalStates;
	finalStates = startingStates;
	startingStates = temp;
}

bool isAcceptedFromState(size_t state, const MyString& word, const NondetemFiniteAutomata& automata)
{
	if (word == "")
	{
		return automata.isFinalState(state);
	}
	for (size_t i = 0; i < automata.getTransitions()[state - 1].getSize(); i++)
	{
		if (automata.getTransitions()[state - 1][i].getFirst() == word[0])
		{
			if (isAcceptedFromState(automata.getTransitions()[state - 1][i].getSecond(), word.c_str() + 1, automata))
			{
				return true;
			}
		}
	}
	return false;
}
