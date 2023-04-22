#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>
#include "Compiler.h"
#include "Configuration.h"

using namespace std;

void Compiler::setStrategy(string name)
{
    delete strategy;
    if (name == "simple")
        strategy = new SimpleStrategy;
    else if (name == "advanced")
        strategy = new AdvancedStrategy;
}

string Compiler::compile(string filepath) const
{
    strategy->compile(filepath);
    return filepath.substr(0, filepath.length() - 4) + ".imf";
}