#include <fstream>
#include <string>
#include "Configuration.h"
#include "Writer.h"

using namespace std;

// read config file
void Configuration::readConfiguration(string configurationFileName, string fileName)
{
    // open log file
    string logFileName = fileName.substr(0, fileName.length() - 4) + ".log";
    Writer::getInstance().open(logFileName);

    ifstream inputFile(configurationFileName);
    string name, equal;
    double value;

    // read variables and theirs values
    while (inputFile.peek() != EOF)
    {
        inputFile >> name;
        inputFile >> equal;
        if (name != "strategy")
        {
            inputFile >> value;
            variableNames.push_back(name);
            variableValues.push_back(value);
        }
        else
            inputFile >> strategy;
    }
}

// returns value of desired variable
double Configuration::getValue(string name)
{
    for (int i = 0; i < variableNames.size(); ++i)
        if (variableNames[i] == name)
            return variableValues[i];
}

string Configuration::getStrategy()
{
    return strategy;
}
