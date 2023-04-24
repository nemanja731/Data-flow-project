#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>
#include "Compiler.h"
#include "Configuration.h"

using namespace std;

Compiler::Compiler()
{
    compiler->setStrategy(Configuration::getInstance().getStrategy());
}

void Compiler::setStrategy(string name)
{
    delete strategy;
    if (name == "simple")
        strategy = new SimpleStrategy;
    else if (name == "advanced")
        strategy = new AdvancedStrategy;
}

string Compiler::compile(string fileName) const
{
    strategy->compile(fileName);
    return fileName.substr(0, fileName.length() - 4) + ".imf";
}