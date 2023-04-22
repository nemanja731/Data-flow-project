#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "Exceptions.h"
#include "Strategy.h"

using namespace std;

// compiler executs different strategies
class Compiler
{
public:
    Compiler() = default;

    string compile(string filepath) const;
    void setStrategy(string name);

private:
    Strategy *strategy = nullptr;
};