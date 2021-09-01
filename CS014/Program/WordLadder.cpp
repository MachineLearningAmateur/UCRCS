#include "WordLadder.h"
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

/* Passes in the name of a file that contains a dictionary of 5-letter words.
       Fills the list (dict) with the words within this file. 
       If the file does not open for any reason or if any word within the file
       does not have exactly 5 characters, this function should output an
       error message and return.
    */
WordLadder::WordLadder(const std::string &word)
{
    std::ifstream wordList;
    wordList.open(word);
    if (!wordList.is_open())
    {
        std::cout << "File did not open properly." << std::endl;
    }
    std::string words;
    while (wordList >> words)
    {
        if (words.size() != 5)
        {
            std::cout << "A word in the file did not have exactly 5 characters." << std::endl;
            return;
        }
        dict.push_back(words);
    }
}

//counts the # of differences in characters between two words
bool WordLadder::countDiff(const std::string word1, const std::string word2)
{
    bool flag = false;
    for (unsigned int i = 0; i < word1.size(); i++)
    {
        if (word1.at(i) != word2.at(i))
        {
            if (flag)
                return false;
            else
                flag = true;
        }
    }
    return flag;
}

/* Passes in two 5-letter words and the name of an output file.
       Outputs to this file a word ladder that starts from the first word passed in
       and ends with the second word passed in.
       If either word passed in does not exist in the dictionary (dict),
       this function should output an error message and return.
       Otherwise, this function outputs to the file the word ladder it finds or outputs
       to the file, the message, "No Word Ladder Found."
    */
void WordLadder::outputLadder(const std::string &start, const std::string &end, const std::string &outputFile)
{
    if (start == end)
    {
        std::ofstream oFile;
        oFile.open(outputFile);
        oFile << start;
        return;
    }
    std::queue<std::stack<std::string>> queueOfStacks;
    std::stack<std::string> s;
    std::stack<std::string> newStack;
    s.push(start);
    dict.remove(start);
    queueOfStacks.push(s);
    while (!queueOfStacks.empty())
    {
        for (std::list<std::string>::iterator i = dict.begin(); i != dict.end(); i++)
        {
            std::string word = queueOfStacks.front().top();
            if (countDiff(word, *i))
            {
                newStack = queueOfStacks.front();
                newStack.push(*i);
                if (*i == end)
                {
                    std::ofstream oFile;
                    oFile.open(outputFile);
                    if (!oFile.is_open())
                    {
                        std::cout << "File did not open properly" << std::endl;
                        return;
                    }
                    std::vector<std::string> reverse;
                    while (newStack.size() >= 0)
                    {
                        reverse.push_back(newStack.top());
                        newStack.pop();
                    }
                    for (int i = reverse.size() - 1; i >= 0; i--)
                    {
                        oFile << reverse.at(i);
                        if (i != 0)
                        {
                            oFile << " ";
                        }
                    }
                    return;
                }
                queueOfStacks.push(newStack);
                dict.erase(i);
                i--;
            }
        }
        queueOfStacks.pop();
    }
}
