#include "Regex.h"

const MyString& Regex::getText() const
{
    return this->text;
}

NondetemFiniteAutomata& Regex::getAutomation()
{
    return this->auotomation;
}

bool Regex::isEmpty() const
{
    return text==nullptr;
}
