#include "NondetemFiniteAutomata.h"
#include <exception>
namespace //helping funcs
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

void NondetemFiniteAutomata::accesibleStatesFrom(MySet<size_t>& accessedStates, size_t state) const //Finds every accebile state From the start BY DFS
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
bool NondetemFiniteAutomata::isErrorState(size_t state) const
{
	if (isFinalState(state))
	{
		return false;
	}
	for (size_t i = 0; i < transitions[state - 1].getSize(); i++)
	{
		if (transitions[state - 1][i].getSecond() != state)
		{
			return false;
		}
	}
	return true;
}
NondetemFiniteAutomata::NondetemFiniteAutomata(const MyString& regex)
{
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

MyString NondetemFiniteAutomata::regexFromAutomation() const
{
	if (isEmptyLanguage())
	{
		return "~";
	}
	MyString toReturn = "";
	NondetemFiniteAutomata temp(*this);
	temp.minimize();
	temp.addState();
	temp.addLetter('@');
	for (size_t i = 0; i < temp.finalStates.getSize(); i++)
	{
		temp.addTransition(temp.finalStates[i], '@', temp.getStatesCount());
	}
	temp.addState();
	temp.addTransition(temp.getStatesCount(), '@', 1);
	temp.clearFinalStates();
	temp.clearStartingStates();
	temp.makeStateFinal(temp.getStatesCount() - 1);                                         //adding new starting and new FInishing state with epselon transition to the old starting and epsellon transtion from all ending to new startung
	temp.makeStateStarting(temp.getStatesCount());
	temp.removeUnaccessibleStates(); 
	Vector<Vector<Pair<MyString,size_t>>> allRegTransitions;

	for (size_t i = 0; i < temp.transitions.getSize(); i++)
	{
		allRegTransitions.pushBack(Vector<Pair<MyString, size_t>>());
		for (size_t j = 0; j < temp.transitions[i].getSize(); j++)
		{
			allRegTransitions[i].pushBack(Pair<MyString, size_t>(temp.transitions[i][j].getFirst(), temp.transitions[i][j].getSecond()));
		}
	}
	for (size_t i = 0; i < temp.states.getSize(); i++)
	{
		MyString Kleenie = "(";
		bool first = true; //for adding the + sign correctly
		for (size_t k = 0; k < allRegTransitions[i].getSize(); k++)
		{
			
				if (allRegTransitions[i][k].getSecond() == i + 1)
				{
					if (first)
					{
						Kleenie += allRegTransitions[i][k].getFirst();
						first = false;
					}
					else
					{
						Kleenie += "+";
						Kleenie += allRegTransitions[i][k].getFirst();
					}
				}
	
		}
		if (Kleenie != "(")
		{
			Kleenie += ")*";
		}
		else
		{
			Kleenie = "";
		}
		for (size_t j = 0; j < allRegTransitions.getSize(); j++) 
		{
			if (j <= i)
				continue;
			size_t fixSize = allRegTransitions[j].getSize();
			for (size_t k = 0; k <fixSize; k++)
			{
				
				if (allRegTransitions[j][k].getSecond() == i + 1)
				{
					size_t fixSize2 = allRegTransitions[i].getSize();
					for (size_t m = 0; m < fixSize2; m++)
					{
						Pair<MyString, size_t> pairToCocat = allRegTransitions[i][m];
						if(pairToCocat.getSecond()!=i+1)
						{
							allRegTransitions[j].pushBack(Pair<MyString, size_t>(allRegTransitions[j][k].getFirst() +Kleenie+ pairToCocat.getFirst(), pairToCocat.getSecond()));        
							//std::cout << j+1 << " | " << allRegTransitions[j][k].getFirst() + Kleenie + pairToCocat.getFirst() << " | " << pairToCocat.getSecond() << "\n";
						}
					}
					if(!temp.isStartingState(j+1))
					allRegTransitions[j].popAt(k);
				}
			}
		}

	}
	bool first = true;
	for (size_t i = 0; i < allRegTransitions[temp.getStartingStates()[0]-1].getSize(); i++)
	{
		if (temp.isFinalState(allRegTransitions[temp.getStartingStates()[0] - 1][i].getSecond()))
		{
			if (first)
			{
				toReturn += allRegTransitions[temp.getStartingStates()[0] - 1][i].getFirst();
				first = false;
			}
			else
			{
				toReturn += "+";
				toReturn += allRegTransitions[temp.getStatesCount() - 1][i].getFirst();
			}
		}	
	}
	return toReturn;
	




}

void NondetemFiniteAutomata::minimize()
{
	reverseAutomata();
	convertToDfa();
	reverseAutomata();
	convertToDfa();
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
								set.addElement(currPair.getSecond());												//making subsets for new states
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
				if (set.getSize() != 0 || error.getSize() != 0)			//adding the new subset as state
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
			newTransitions[transitions[i][j].getSecond() - 1].pushBack(Pair<char, size_t>(transitions[i][j].getFirst(), i + 1)); //flipiing the transitions
		}
	}
	transitions.clear();
	transitions = newTransitions;
	MySet<size_t> temp = finalStates;
	finalStates = startingStates;
	startingStates = temp;

	for (size_t i = 0; i < getStatesCount(); i++)
	{
		if (isErrorState(i + 1))
		{
			errorStates.addElement(i + 1);
		}
	}
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
