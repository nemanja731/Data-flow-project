#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Memory.h"

using namespace std;

Memory::Memory() { nw = Configuration::getInstance().getValue("Nw"); }

bool Memory::isReady() const
{
    return (inProcess < nw);
}

void Memory::reserve()
{
    if (isReady())
        ++inProcess;
}

void Memory::save(string fileName)
{
    string outpath;
    outpath = fileName.substr(0, fileName.length() - 4) + ".mem";
    ofstream outputFile(outpath);

    for (int i = 0; i < variables.size(); ++i)
        outputFile << variables[i] << " = " << atof(values[i].c_str()) << endl;
}

void Memory::set(string varName, string val)
{
    inProcess = inProcess - 1;
    for (int i = 0; i < variables.size(); ++i)
        if (variables[i] == varName)
        {
            values[i] = val;
            return;
        }

    variables.push_back(varName);
    values.push_back(val);
}

string Memory::get(string varName)
{
    for (int i = 0; i < variables.size(); ++i)
        if (variables[i] == varName)
            return values[i];
    throw VariableNotExist("There is not variable in memory.");
}