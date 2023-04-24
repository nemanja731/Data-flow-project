#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include "Compiler.h"
#include "Configuration.h"
#include "Strategy.h"

// reads each line of given file, infix -> postfix
// segments postfix notation to one operation in each line
void SimpleStrategy::compile(string fileName)
{
    string line, outFileName;
    stringstream ss;
    int temporaryCounter = 1, operation = 1;

    // txt -> imf
    outFileName = fileName.substr(0, fileName.length() - 4) + ".imf";
    ifstream inputFile(fileName);
    ofstream outputFile(outFileName);
    while (getline(inputFile, line))
        readLine(line, outputFile, operation, temporaryCounter);
    inputFile.close();
    outputFile.close();
}

void SimpleStrategy::readLine(string line, ofstream outputFile, int operation, int temporaryCounter)
{
    int it = 0;
    string temporaryMem, x, operation1, operation2;
    stack<string> S;

    line = infixToPostfix(line);
    // read each element of postfix notation
    x = readNext(line, &it);
    while (x != "")
    {
        if (!checkOperation(x))
            S.push(x);
        else
        {
            operation2 = S.top();
            S.pop();
            operation1 = S.top();
            S.pop();

            if (x == "=")
                outputFile << "[" << operation++ << "] = " << operation1 << " " << operation2 << endl;
            else
            {
                temporaryMem = "t" + to_string(temporaryCounter++);

                outputFile << "[" << operation++ << "] " << x << " " << temporaryMem << " " << operation1 << " " << operation2 << endl;
                S.push(temporaryMem);
            }
        }
        x = readNext(line, &it);
    }
}

// returns next variable, value or operation in a given string
string Strategy::readNext(string input, int *it)
{
    string el = "";
    while ((*it < input.length()) && input[*it] == ' ')
        (*it)++;

    if (*it > input.length())
        return el;

    if ((input[*it] == '-') && (isdigit(input[(*it) + 1])))
    {
        el += "-";
        ++(*it);
    }

    if (checkOperation(input[*it]))
        el = input[(*it)++];
    else
        while ((*it < input.size()) && !checkOperation(input[*it]) && input[*it] != ' ')
            el += input[(*it)++];

    return el;
}

// Advanced strategy
void AdvancedStrategy::compile(string fileName)
{
    string line, outFileName;
    stringstream ss;

    // txt -> imf
    outFileName = fileName.substr(0, fileName.length() - 4) + ".imf";
    ifstream inputFile(fileName);
    vector<string> commands;
    // read each line
    while (inputFile.peek() != EOF)
        readLine(inputFile);
    inputFile.close();

    // sort by importance which is calculated as sum of time needed for all
    sortCommands(commands);

    // write sorted commands to output location
    ofstream outputFile(outFileName);
    for (string com : commands)
        outputFile << com << endl;
}

void AdvancedStrategy::readLine(ifstream inputFile)
{
    int it = 0, temporaryCounter = 1, operation = 1;
    string line, temporaryMem, x, operation1, operation2;
    stack<string> S;

    getline(inputFile, line);
    line = infixToPostfix(line);
    // read each element of postfix notation
    x = readNext(line, &it);
    while (x != "")
    {
        if (!checkOperation(x))
            S.push(x);
        else
        {
            operation2 = S.top();
            S.pop();
            operation1 = S.top();
            S.pop();

            if (x == "=")
                commands.push_back("[" + to_string(operation++) + "] = " + operation1 + " " + operation2);
            else
            {
                temporaryMem = "t" + to_string(temporaryCounter++);

                commands.push_back("[" + to_string(operation++) + "] " + x + " " + temporaryMem + " " + operation1 + " " + operation2);
                S.push(temporaryMem);
            }
        }
        x = readNext(line, &it);
    }
}

// return Nth element in string
string getN(string s, int n)
{
    string ret;
    stringstream ss(s);
    for (int i = 0; i < n; ++i)
        ss >> ret;
    return ret;
}

// score all commands with calculateScore and then sort them descendingly
void AdvancedStrategy::sortCommands(vector<string> &commands)
{
    map<string, double> scores;
    string c;
    for (string com : commands)
    {
        c = getN(com, 3);
        scores.insert(pair<string, double>(c, 0));
        if (getN(com, 2) == "=")
        {
            included.clear();
            scores.at(c) = calculateScore(c, commands);
        }
    }

    for (int i = 0; i < commands.size(); ++i)
        for (int j = i; j < commands.size(); ++j)
            if (scores.at(getN(commands[i], 3)) < scores.at(getN(commands[j], 3)))
                swap(commands[i], commands[j]);
}

// score every command based on the amount of time needed to calculate everything that depands on particular value
double AdvancedStrategy::calculateScore(string c, vector<string> &commands)
{
    double score = 0;
    string x;

    if (included.count(c) != 0)
        return 0;

    if (scores.count(c) != 0)
        return scores.at(c);

    scores.insert(pair<string, double>(c, 0));
    included.insert(c);

    for (string com : commands)
    {
        if (c == getN(com, 3))
            score += getTime(getN(com, 2));

        if (c == getN(com, 4))
            score += calculateScore(getN(com, 3), commands);

        if (c == getN(com, 5))
            score += calculateScore(getN(com, 3), commands);
    }
    scores.at(c) = score;
    return score;
}

double AdvancedStrategy::getTime(string c)
{
    switch (c[0])
    {
    case '=':
        return Configuration::getInstance().getValue("Tw");
    case '+':
        return Configuration::getInstance().getValue("Ta");
    case '*':
        return Configuration::getInstance().getValue("Tm");
    case '^':
        return Configuration::getInstance().getValue("Te");

    default:
        throw exception();
    }
}

// infix -> postfix (postfix has operations and operands in string divided by spaces)
string Strategy::infixToPostfix(string infix)
{
    stack<string> S;
    string next, postfix = "";
    string x;
    int rank = 0;
    int it = 0;

    // remove trailing '\r' characters if they exist
    if (infix[infix.length() - 1] == '\r')
        infix = infix.substr(0, infix.length() - 1);

    next = readNext(infix, &it);
    postfix += next;
    // '=' sign
    next = readNext(infix, &it);
    // equation
    next = readNext(infix, &it);

    // parse string
    postfix = parse(postfix, rank, x, S, it, infix);
    postfix += " =";
    return postfix;
}

string Strategy::parse(string postfix, int rank, string x, stack<string> S, int it, string infix)
{
    while (next != "")
    {
        if (!(checkOperation(next)))
        {
            postfix += " " + next;
            ++rank;
        }
        else
        {
            while (!S.empty() && (inputPriority(next[0]) <= outputPriority(S.top()[0])))
            {
                x = S.top();
                postfix += " " + x;
                S.pop();
            }

            if (next != ")")
                S.push(next);
            else
                S.pop();
        }
        next = readNext(infix, &it);
    }
    while (!S.empty())
    {
        x = S.top();
        postfix += " " + x;
        S.pop();
    }
}

int Strategy::inputPriority(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 2;
        break;

    case '*':
    case '/':
        return 3;
        break;

    case '^':
        return 5;
        break;

    case '(':
        return 6;
        break;

    case ')':
        return 1;
        break;

    case '=':
        return 0;
        break;
    }
}

int Strategy::outputPriority(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 2;
        break;

    case '*':
    case '/':
        return 3;
        break;

    case '^':
        return 4;
        break;

    case '(':
        return 0;
        break;

    case ')':
        return 0;
        break;

    case '=':
        return 1;
        break;
    }
}

bool Strategy::checkOperation(string c)
{
    return ((c.size() == 1) && ((c[0] == '+') || (c[0] == '-') || (c[0] == '*') || (c[0] == '/') || (c[0] == '^') || (c[0] == '(') || (c[0] == ')') || (c[0] == '=')));
}

bool Strategy::checkOperation(char c)
{
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '(') || (c == ')') || (c == '='));
}