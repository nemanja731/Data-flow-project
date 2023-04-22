#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "Exceptions.h"

using namespace std;

// abstract class, compile txt -> imf
class Strategy
{
public:
    virtual void compile(string filepath) = 0;

protected:
    string infixToPostfix(string infix);
    string parse(string postfix, int rank, string x, stack<string> S, int it, string infix);
    string readNext(string input, int *it);
    bool checkOperation(string c);
    bool checkOperation(char c);
    int inputPriority(char c);
    int outputPriority(char c)
};

class SimpleStrategy : public Strategy
{
public:
    virtual void compile(string filepath) override;
};

class AdvancedStrategy : public Strategy
{
public:
    virtual void compile(string filepath) override;

private:
    set<string> included;
    map<string, double> scores;

    void sortCommands(vector<string> &commands);
    double calculateScore(string c, vector<string> &commands);
    double getTime(string c);
};