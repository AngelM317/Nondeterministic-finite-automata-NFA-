#pragma once
#include"Vector.hpp"
#include"Pair.hpp"
#include"MySet.hpp"
#include "MyString.h"
class NondetemFiniteAutomata
{
private:
	Vector<Vector<Pair<char, size_t>>> transitions;
	MySet<char> alphabeth;
	MySet<size_t> finalStates;
	MySet<size_t> startingStates;
	Vector<size_t> states;
	MySet<size_t> errorStates;
	MySet<size_t> universumStates;
	void decreaseStatesFromIndex(size_t index);
	void accesibleStatesFrom(MySet<size_t>& states,size_t state) const;
public:
	friend bool isAcceptedFromState(size_t state, const MyString& word, const NondetemFiniteAutomata&) ;
	void setTransitions(Vector<Vector<Pair<char, size_t>>>& transitions);
	void setStates(const Vector<size_t>& states);

	const MySet<char>& getAlphabeth() const;
	const MySet<size_t>& getFinalStates() const;
	const MySet<size_t>& getStartingStates() const;
	const Vector<Vector<Pair<char, size_t>>>& getTransitions() const;

	void addLetter(char letter);
	void addState();
	void addTransition(size_t from, char letter, size_t to);

	void removeState(size_t state);
	void removeUnaccessibleStates();

	void makeStateFinal(size_t state);
	void makeStateStarting(size_t state);

	size_t getStatesCount() const;
	bool isStartingState(size_t state) const;
	bool isFinalState(size_t state) const;
	bool isEmptyLanguage() const;
	bool accept(const MyString& word) const;

	void makeTotal();
	void convertToDfa();
	void reverseAutomata();

	void clearFinalStates();
	void clearStartingStates();
	void clearAutomata();
	void printTransitions() const;






};

