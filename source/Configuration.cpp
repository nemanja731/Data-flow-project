#include <fstream>
#include <string>
#include "Configuration.h"

using namespace std;

// read config file
void Configuration::readConfiguration(string fileName)
{
    ifstream inputFile(fileName);
    string name, equal;
    double value;

    // read variables and theirs values
    while (inputFile.peek() != EOF)
    {
        inputFile >> name;
        inputFile >> equal;
        if (name != "compilation")
        {
            inputFile >> value;
            variableNames.push_back(name);
            variableValues.push_back(value);
        }
        else
            inputFile >> compilation;
    }
}

// returns value of desired variable
double Configuration::getValue(string name)
{
    for (int i = 0; i < variableNames.size(); ++i)
        if (variableNames[i] == name)
            return variableValues[i];
}

string Configuration::getCompilation()
{
    return compilation;
}
