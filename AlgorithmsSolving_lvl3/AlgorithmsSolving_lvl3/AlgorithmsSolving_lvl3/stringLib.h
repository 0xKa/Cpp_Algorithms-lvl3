#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum enLetterType { All, Capital, Small };

namespace StringLib
{
    void PrintFirstLetterOfEachWord(string s)
    {
        cout << "Fisrt Letters:\n";
        bool isFirstLetter = true;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != ' ' && isFirstLetter)
                cout << s[i] << endl;

            isFirstLetter = (s[i] == ' ' ? true : false);
        }
    }

    void UpperFirstLetterOfEachWord(string& s)
    {
        bool isFirstLetter = true;

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != ' ' && isFirstLetter)
            {
                s[i] = toupper(s[i]);
            }

            isFirstLetter = (s[i] == ' ' ? true : false);
        }

    }

    void LowerFirstLetterOfEachWord(string& s)
    {
        bool isFirstLetter = true;

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != ' ' && isFirstLetter)
            {
                s[i] = tolower(s[i]);
            }

            isFirstLetter = (s[i] == ' ' ? true : false);
        }
    }

    string AllToUpper(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s[i] = toupper(s[i]);
        }
        return s;
    }

    string AllToLower(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s[i] = tolower(s[i]);
        }
        return s;
    }

    char ConvertCharacterCase(char c)
    {
        return (islower(c) ? toupper(c) : tolower(c));
    }

    string InvertAllLettersCase(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s[i] = ConvertCharacterCase(s[i]);
        }
        return s;
    }

    int CountCapitalLetters(string s)
    {
        int CapsCounter = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (isupper(s[i]))
                CapsCounter++;
        }
        return CapsCounter;
    }

    int CountSmallLetters(string s)
    {
        int SmolCounter = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (islower(s[i]))
                SmolCounter++;
        }
        return SmolCounter;
    }

    int CountLetters(string s, enLetterType type = All)
    {
        if (type == All)
            return s.length();
        else if (type == Capital)
            return CountCapitalLetters(s);
        else
            return CountSmallLetters(s);
    }

    int CountSpecificLetter(string s, char letter, bool MatchCase = true)
    {
        int counter = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (MatchCase) {
                if (s[i] == letter)
                    counter++;
            }
            else {
                if (s[i] == letter || s[i] == ConvertCharacterCase(letter))
                    counter++;
            }
        }
        return counter;
    }

    bool isVowel(char c)
    {
        c = tolower(c);
        return (c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o');
    }

    int CountVowelLetters(string s)
    {
        int VowelCounter = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (isVowel(s[i]))
                VowelCounter++;
        }
        return VowelCounter;
    }

    void PrintVowelLetters(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            if (isVowel(s[i]))
                cout << s[i] << "\t";
        }
    }

    void PrintEachWordInString(string s)
    {
        cout << "\nString Words: \n";
        string word, delim = " "; //delimiter means space string --> " " 
        short position = 0;

        while ((position = s.find(delim)) != s.npos) //position of the first delimiter != s.npos
        {
            word = s.substr(0, position);
            if (word != "")
                cout << word << endl; //print the word from 0 to delimiter position

            s.erase(0, position + delim.length()); //erase the word we printed and the delimiter after it
        }

        if (s != "") //if the string is not empty yet, print the last word
            cout << s << endl;

    }

    int CountEachWordInString(string s)
    {
        string word, delim = " "; //delimiter means space string --> " " 
        short position = 0, counter = 0;

        while ((position = s.find(delim)) != s.npos) //position of the first delimiter != s.npos
        {
            word = s.substr(0, position);
            if (word != "")
                counter++;

            s.erase(0, position + delim.length()); //erase the word we printed and the delimiter after it
        }

        return ++counter; //print the counter + 1 because there is still one word in the string 
    }

    vector <string> SplitString(string s, string separator)
    {
        //separator is the same as delimeter

        vector <string> vStringWords;

        string word;
        short position = 0;

        while ((position = s.find(separator)) != s.npos)
        {
            word = s.substr(0, position);
            if (word != "")
                vStringWords.push_back(word);

            s.erase(0, position + separator.length());
        }

        if (s != "")
            vStringWords.push_back(s);

        return vStringWords;
    }

    string TrimLeft(string s)
    {
        char delim = ' ';
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != delim && s[0] == delim)
                s = s.substr(i, s.length() - 1);
        }
        return s;
    }

    string TrimRight(string s)
    {
        char delim = ' ';
        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (s[i] != delim && s[s.length() - 1] == delim)
                s = s.substr(0, i + 1);
        }
        return s;
    }

    string Trim(string s)
    {
        return TrimRight(TrimLeft(s));
    }

    string JoinString(vector <string> vStrings, string separator)
    {
        string FullString = "";
        for (string& i : vStrings)
        {
            FullString = FullString + i + separator;
        }
        //return the string without the last separator 
        return FullString.substr(0, FullString.length() - separator.length());
    }

    string JoinString(string arrStrings[6], int arrLength, string separator)
    {
        string FullString = "";
        for (int i = 0; i < arrLength; i++)
        {
            FullString = FullString + arrStrings[i] + separator;

        }

        //return the string without the last separator 
        return FullString.substr(0, FullString.length() - separator.length());
    }

    string ReverseString(string s)
    {
        string ReversedString = "", separator = " ";
        vector <string> vString = SplitString(s, separator);
        vector <string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {
            iter--;
            ReversedString = ReversedString + *iter + separator;
        }

        return ReversedString.substr(0, ReversedString.length() - separator.length());
    }

    string ReplaceWordUsingBuiltInFunction(string s, string WordToReplace, string NewWord)
    {
        int WordPosition = s.find(WordToReplace);

        if (WordPosition == s.npos)
            return "\nWord Not Found\n";

        while (WordPosition != s.npos)//use while to check for multiple words
        {
            s.replace(WordPosition, WordToReplace.length(), NewWord);// built-in funcation

            WordPosition = s.find(WordToReplace); //check if there is another word
        }

        return s;
    }

    string ReplaceWord(string s, string WordToReplace, string NewWord)
    {
        int WordPosition = s.find(WordToReplace);

        if (WordPosition == s.npos)
            return "\nWord Not Found\n";

        while (WordPosition != s.npos)//use while to check for multiple words
        {
            s.erase(WordPosition, WordToReplace.length());
            s.insert(WordPosition, NewWord);

            WordPosition = s.find(WordToReplace); //check if there is another word
        }

        return s;
    }

    string ReplaceWordUsingSplit(string s, string WordToReplace, string NewWord, bool MatchCase = true)
    {
        vector <string> vStringWords = SplitString(s, " ");

        s.clear(); //clear the string to refill it
        for (string& i : vStringWords)
        {
            if (MatchCase == true && i == WordToReplace)
                i = NewWord;

            if (MatchCase == false && AllToLower(i) == AllToLower(WordToReplace))
                i = NewWord;
        }

        return JoinString(vStringWords, " ");// refilling the string and return it
    }

    string RemovePunctuations(string s)
    {
        string NewString = "";
        for (int i = 0; i < s.length(); i++)
        {
            if (!ispunct(s[i]))
            {
                NewString = NewString + s[i];
            }
        }
        return NewString;
    }
}