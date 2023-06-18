#include "RegexWrap.h"
#include "SharedPtr.hpp"

namespace
{

    size_t getRegexPartIndexe(const MyString& exp, size_t& startIndex)
    {
        size_t finalIndex = startIndex;
        size_t bracketsCount = 0;
        while (exp[finalIndex] != '('&& exp[finalIndex]!='+'&& exp[finalIndex] != '\0')
        {
            finalIndex++;
        }
        if (exp[finalIndex] != '+')
        {
            do
            {
                if (exp[finalIndex] == '(')
                {
                    bracketsCount++;
                }
                if (exp[finalIndex++] == ')')
                {
                    bracketsCount--;
                }
            } while (bracketsCount != 0 && exp[finalIndex] != 0);

        }
        if (exp[finalIndex] != 0)
        {
            if (exp[finalIndex] == '*')
            {
                return finalIndex;
            }
        }
        return finalIndex - 1;
        
    }
    SharedPtr<Regex> getRegexPart(const MyString& exp,size_t& startIndex, size_t finalIndex)                //
    {
        SharedPtr<Regex> toBeReturned = new SimpleRegex("");
        MyString temp = "";
        while (exp[startIndex]!='\0'&&finalIndex>=startIndex)
        {
            if (exp[startIndex] == '(')
            {
                /*SharedPtr<Regex> temp1(new SimpleRegex(temp));
                SharedPtr<Regex> temp2 (getRegexPart(exp, ++startIndex, getRegexPartIndexe(exp,startIndex)));
                SharedPtr<Regex> concat(new ConcatRegex(temp1, temp2));        */   
                toBeReturned = new ConcatRegex(toBeReturned, new SimpleRegex(temp));
                size_t newStart = getRegexPartIndexe(exp, startIndex);
                SharedPtr<Regex> temp2(getRegexPart(exp, ++startIndex, newStart));
                startIndex = newStart + 1;
                toBeReturned =new ConcatRegex(toBeReturned, temp2);
                temp = "";
            }
            else if (exp[startIndex] == ')')
            {
                toBeReturned = new ConcatRegex(toBeReturned, new SimpleRegex(temp));
                startIndex++;
                if (exp[startIndex] == '*')
                {
                    startIndex++;
                    toBeReturned = (new KleeneRegex(new SimpleRegex(temp)));

                }
                temp = "";
                

            }
            else if (exp[startIndex] == '+')
            {
                toBeReturned = new ConcatRegex(toBeReturned, new SimpleRegex(temp));
                toBeReturned = new UnionRegex(toBeReturned, getRegexPart(exp, ++startIndex, getRegexPartIndexe(exp, startIndex)));
                temp = "";
            }
            else if (exp[startIndex] == '~')
            {
                temp = "~";
                startIndex++;
            }
            else
            {
                if(temp!="~")
                temp += exp[startIndex];

                startIndex++;
            }
        }

        return new ConcatRegex(toBeReturned, new SimpleRegex(temp));
    }
}

SharedPtr<Regex>& RegexWrap::getRegex()
{
    return regex;
}
RegexWrap::RegexWrap()
{
	this->regex = new SimpleRegex(nullptr);
}

RegexWrap::RegexWrap(MyString& exp)
{
    clearWs(exp);
    if (!isValidReggex(exp))
    {
        regex = new SimpleRegex("~");
    }
    else
    {
        regex = new SimpleRegex("");
        size_t startIndex = 0;
        while (exp[startIndex] != '\0')
        {
            regex = getRegexPart(exp, startIndex, exp.length());       
        }
    }

}


bool RegexWrap::isValidReggex(const MyString& exp) const
{
    int brackets=0;
    for (size_t i = 0; i < exp.length(); i++)
    {
        if (exp[i] == '(')
        {
            brackets++;
        }
        if (exp[i] == ')')
        {
            if (brackets <= 0)
            {
                return false;
            }
            brackets--;
        }
        if (exp[i] == '*')
        {
            if (i == 0)
                return false;
            if (exp[i - 1] != ')')
                return false;
        }
    }
    return true;
}

void RegexWrap::clearWs(MyString& text)
{
    MySet<size_t> wsIndex;
    for (size_t i = 0; i <= text.length(); i++)
    {
        if (text[i] == ' '|| text[i] == '@')
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
        i++;
    }
    newText += text[i];
    text = std::move(newText);
}

