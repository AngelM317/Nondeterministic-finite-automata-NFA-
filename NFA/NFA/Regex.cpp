#include "Regex.h"

void Regex::initializeAlphabeth()
{
    for (size_t i = 0; i < text.length(); i++)
    {
        if (text[i] != '+' && text[i] != '*' && text[i] != '(' && text[i] != ')'&&text[i]!=' ')
        {
            auotomation.addLetter(text[i]);
        }
    }
}

void Regex::clearWS()
{
    MySet<size_t> wsIndex;
    for (size_t i = 0; i <= text.length(); i++)
    {
        if (text[i] == ' ')
        {
            wsIndex.addElement(i);
        }
    }
    MyString newText = "";
    int i = 0;
    while (text[i] != 0)
    {
        if (!wsIndex.contains(i))
        {
            newText += text[i];
        }
    }
}

const MyString& Regex::getText() const
{
    return this->text;
}

const NondetemFiniteAutomata& Regex::getAutomation() const
{
    return this->auotomation;
}

bool Regex::isValidRegex() const
{
    int brackets;
    for (size_t i = 0; i < text.length(); i++)
    {
        if (text[i] == '(')
        {
            brackets++;
        }
        if (text[i] == ')')
        {
            if (brackets <= 0)
            {
                return false;
            }
            brackets--;
        }
        if (text[i] == '*')
        {
            if (i == 0)
                return false;
            if (text[i - 1] != '0')
                return false;
        }
    }
    return true;
}

bool Regex::isEmpty() const
{
    return text==nullptr;
}
