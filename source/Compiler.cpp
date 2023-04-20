#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>

#include "Compiler.h"
#include "Config.h"

using namespace std;

// Helper functions for inf2post()
int ipr(char c);
int spr(char c);

// Simple compilation strategy
// Reads each line of given file, turns infix notation to postfix
// Segments postfix notation to one operation in each line
void SimpleCompilationStrategy::compile(string filepath) {
    string line, outpath;
    string tmpMem;
    string x, op1, op2;
    stringstream ss;
    int tmpCounter = 1, operation = 1;

    // Ouput file is filepath with .txt changed for .imf
    outpath = filepath.substr(0, filepath.length()-4) + ".imf";
    ifstream inFile(filepath);
    ofstream outFile(outpath);

    // Read each line
    while (getline(inFile, line)) {
        int it = 0;
        stack<string> S;

        // Turn line to postfix notation
        line = inf2post(line);

        // Read each element of postfix notation
        x = readNext(line, &it);
        while (x != "") {
            if (!checkOperation(x))
                S.push(x);
            else {
                op2 = S.top(); S.pop();
                op1 = S.top(); S.pop();

                if (x == "=")
                    outFile << "[" << operation++ << "] = " 
                            << op1 << " " << op2 << endl;
                else {
                    tmpMem = "t" +  to_string(tmpCounter++);

                    outFile << "[" << operation++ << "] " << x
                            << " " << tmpMem << " "
                            << op1 << " " << op2 << endl;
                    S.push(tmpMem); 
                }
            }
            x = readNext(line, &it);
        }
    }
    inFile.close();
    outFile.close();
}

// Advanced compilation strategy
void AdvancedCompilationStrategy::compile(string filepath) {
    string line, outpath;
    string tmpMem;
    string x, op1, op2;
    int tmpCounter = 1, operation = 1;

    // Ouput file is filepath with .txt changed for .imf
    outpath = filepath.substr(0, filepath.length()-4) + ".imf";
    ifstream inFile(filepath);

    // Vector of all commands to be sorted
    vector<string> commands;

    // Read each line
    while (inFile.peek() != EOF) {
        int it = 0;
        stack<string> S;

        // Read line
        getline(inFile, line);

        // Turn line to postfix notation
        line = inf2post(line);

        // Read each element of postfix notation
        x = readNext(line, &it);
        while (x != "") {
            if (!checkOperation(x))
                S.push(x);
            else {
                op2 = S.top(); S.pop();
                op1 = S.top(); S.pop();

                if (x == "=")
                    commands.push_back("[" + to_string(operation++) 
                        + "] = " + op1 + " " + op2);
                else {
                    tmpMem = "t" +  to_string(tmpCounter++);

                    commands.push_back("[" + to_string(operation++)
                            + "] " + x + " " + tmpMem + " "
                            + op1 + " " + op2);
                    S.push(tmpMem); 
                }
            }
            x = readNext(line, &it);
        }
    }
    inFile.close();


    // Sort commands in order of importance
    // Importance is calculated as sum of time needed for all
    // operations dependant on starting operation to complete
    sortCommands(commands);

    // Write sorted commands to output location
    ofstream outFile(outpath);
    for (string com : commands)
        outFile << com << endl;

}

// Return Nth element in string (1-base)
string fetchNth(string s, int n) {
    string ret;
    stringstream ss(s);
    for (int i = 0; i < n; ++i)
        ss >> ret;
    return ret;
}

// Score all commands with calcScore and then sort them descendingly
void AdvancedCompilationStrategy::sortCommands(vector<string>& commands) {

    map<string, double> scores;
    string c;
    for ( string com : commands ) {
        c = fetchNth(com, 3);
        scores.insert(pair<string, double> (c, 0));
        if (fetchNth(com, 2) == "=") {
            included_in_score_.clear();
            scores.at(c) = calcScore(c, commands);
        }
    }

    for (int i = 0; i < commands.size(); ++i)
        for (int j = i; j < commands.size(); ++j)
            if (scores.at(fetchNth(commands[i], 3)) < 
                scores.at(fetchNth(commands[j], 3)))
                    swap(commands[i], commands[j]);


}

// Score every command based on the amount of time needed
// to calculate everything that depands on particular value
double AdvancedCompilationStrategy::calcScore(string c, vector<string>& commands) {
    double score = 0;
    string x;

    if (included_in_score_.count(c) != 0) 
        return 0;

    if (scores_.count(c) != 0)
        return scores_.at(c);

    scores_.insert(pair<string, double> (c, 0));
    included_in_score_.insert(c);

    for (string com : commands) {
        if (c == fetchNth(com, 3)) 
            score += getTime(fetchNth(com, 2));

        if (c == fetchNth(com, 4))
            score += calcScore(fetchNth(com, 3), commands);
        
        if (c == fetchNth(com, 5))
            score += calcScore(fetchNth(com, 3), commands);
    }
    scores_.at(c) = score;
    return score;
}


double AdvancedCompilationStrategy::getTime(string c) {
    switch (c[0]) {
    case '=':
        return Config::getInstance().getValue("Tw");
    case '+':
        return Config::getInstance().getValue("Ta");
    case '*':
        return Config::getInstance().getValue("Tm");
    case '^':
        return Config::getInstance().getValue("Te");
    
    default:
        throw exception();
    }
}

// Rewrite infix notation to postfix notation
// Postfix has operations and operands in string divided by 
// spaces
string CompilationStrategy::inf2post(string infix) {
    stack<string> S;
    string next, postfix = "";
    string x;
    int rank = 0;
    int it = 0;

    // Remove trailing '\r' characters if they exist
    if (infix[infix.length()-1] == '\r')
        infix = infix.substr(0, infix.length()-1);

    next = readNext(infix, &it); // fist var
    postfix += next;
    next = readNext(infix, &it); // '=' sign
    next = readNext(infix, &it); // equation

    // Parse string
    while (next != "") {
        if(!(checkOperation(next))) {
            postfix += " " + next;
            ++rank;
        }
        else {
            while (!S.empty() && (ipr(next[0]) <= spr(S.top()[0]))) {
                x = S.top();
                postfix += " " + x;
                S.pop();
            }

            if (next != ")")
                S.push(next);
            else S.pop();
        }
        next = readNext(infix, &it);
    }
    while (!S.empty()) {
        x = S.top();
        postfix += " " + x;
        S.pop();
    }
    postfix += " =";
    return postfix;
}

// Returns next variable, value or operation in a given string
string CompilationStrategy::readNext(string input, int* it) {
    string el = "";
    while ((*it < input.length()) && input[*it] == ' ')
        (*it)++;

    if (*it > input.length()) return el;

    if ((input[*it] == '-') && (isdigit(input[(*it)+1]))) {
        el += "-";
        ++(*it);
    }

    if (checkOperation(input[*it])) el = input[(*it)++];
    else
        while ((*it < input.size()) && !checkOperation(input[*it]) && input[*it] != ' ')
            el += input[(*it)++];
    
    return el;
}

bool CompilationStrategy::checkOperation(string c) {
    return ((c.size() == 1) && ((c[0] == '+') || (c[0] == '-') || \
            (c[0] == '*') || (c[0] == '/') || (c[0] == '^') || \
            (c[0] == '(') || (c[0] == ')') || (c[0] == '=')));
}

bool CompilationStrategy::checkOperation(char c) {
    return ((c == '+') || (c == '-') || \
            (c == '*') || (c == '/') || (c == '^') || \
            (c == '(') || (c == ')') || (c == '='));
}

// Helper functions for inf2post()
int ipr(char c) {
    switch (c) {
    case '+': case '-':
        return 2;
        break;
    
    case '*': case '/':
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

    default:
        // TODO: Exception!
        break;
    }
}

int spr(char c) {
    switch (c) {
    case '+': case '-':
        return 2;
        break;
    
    case '*': case '/':
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

    default:
        // TODO: Exception!
        break;
    }
}
