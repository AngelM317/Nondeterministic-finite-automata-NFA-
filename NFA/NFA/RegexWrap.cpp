#include "RegexWrap.h"
#include "SharedPtr.hpp"

namespace
{

    size_t getRegexPartIndexe(const MyString& exp, size_t& startIndex, size_t maxIndex) //finds the new part to be calculated
    {
        size_t finalIndex = startIndex;
        size_t bracketsCount = 0;
        while (exp[finalIndex] != '('&& exp[finalIndex]!='+'&& exp[finalIndex] != '\0'&& exp[finalIndex] != ')')
        {
            finalIndex++;
        }
        if (exp[finalIndex] == ')')
        {
            return (finalIndex - 1 > maxIndex) ? maxIndex : finalIndex - 1;
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
            } while (bracketsCount > 0 && exp[finalIndex] != 0);

        }
        if (exp[finalIndex] > 0)
        {
            if (exp[finalIndex] == '*')
            {
                return (finalIndex>maxIndex)?maxIndex-1:finalIndex;
            }
        }
        return (finalIndex-1 > maxIndex) ? maxIndex : finalIndex-1;
        
    }
    SharedPtr<Regex> getRegexPart(const MyString& exp,size_t& startIndex, size_t finalIndex)                //
    {
        SharedPtr<Regex> toBeReturned = new SimpleRegex(""); //result so far
        MyString temp = ""; // saves consecutive letters (a word) untill it find some symbol signaling some operation
        while (exp[startIndex]!='\0'&&finalIndex>=startIndex)
        {
            if (exp[startIndex] == '(')
            {
                toBeReturned = new ConcatRegex(toBeReturned, new SimpleRegex(temp));
                size_t newStart = getRegexPartIndexe(exp, startIndex, finalIndex-1); //The next art to concat with
                SharedPtr<Regex> temp2(getRegexPart(exp, ++startIndex, newStart-1));
                startIndex;
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
                    toBeReturned = (new KleeneRegex(toBeReturned));

                }
                temp = "";
                

            }
            else if (exp[startIndex] == '+')
            {
                toBeReturned = new ConcatRegex(toBeReturned, new SimpleRegex(temp));
                toBeReturned = new UnionRegex(toBeReturned, getRegexPart(exp, ++startIndex, getRegexPartIndexe(exp, startIndex,finalIndex-1)));
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
bool RegexWrap::operator==(const RegexWrap& other) const
{
    return this->regex->getText()==other.regex->getText();
}
RegexWrap::RegexWrap()
{
    this->regex = new SimpleRegex("~");
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
        regex->setText(exp);
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
        if (text[i] == ' '|| text[i] == '@') //writting epsellon or blank space doest change the nature of the regex but without them its much easier to calculate
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

