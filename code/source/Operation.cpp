#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Exceptions.h"
#include "Interfaces.h"
#include "Machine.h"
#include "Memory.h"
#include "Operation.h"
#include "Sched.h"
#include "Types.h"
#include "Writer.h"

using namespace std;

void Operation::setStartTime(double time)
{
    startTime = to_string((int)time);
}

double Operation::getTime() const
{
    return time;
}

// set value of input
void Operation::setInput(int inputNumber, string variable)
{
    inputs.at(inputNumber) = variable;
}

// update value of token
void Operation::updateInput(string varName, string newValue)
{
    for (int i = 0; i < inputs.size(); ++i)
        if (inputs[i] == varName)
            inputs[i] = newValue;
}

// check if all inputs have values
bool Operation::check()
{
    try
    {
        for (string val : inputs)
            if (!checkNumber(val))
                return false;
    }
    catch (VariableNotExist &e)
    {
        return false;
    }
    return true;
}

bool Operation::done() const
{
    return done;
}

// check if string is real number
bool checkNumber(const string s)
{
    return s.find_first_not_of(".-0123456789") == string::npos;
}

// check if all inputs have values and if memory is ready for writing
bool Equal::check()
{
    try
    {
        if (checkNumber(inputs[0]) && Memory::getInstance().ready())
        {
            Memory::getInstance().reserve();
            return true;
        }
        return false;
    }
    catch (VariableNotExist &e)
    {
        return false;
    }
}

// interface with Scheduler class
void Operation::notify(ID id)
{
    done = true;
    endTime = to_string((int)Scheduler::Instance()->getCurTime());
    string result = evaluate();
    string data = "";
    data = token + " (" + startTime + "-" + endTime + ")ns";
    Writer::getInstance().write(data.c_str());
    Machine::getInstance().updateAllOperations(outputName, result);
}

string Equal::evaluate()
{
    Memory::getInstance().set(outputName, inputs[0]);
    return inputs[0];
}

double[] Operation::eval()
{
    double values[3];
    value[0] = atof(inputs[0].c_str());
    value[1] = atof(inputs[1].c_str());
    return values;
}

string Add::evaluate()
{
    double values[3] = eval();
    values[2] = values[0] + values[1];
    return to_string(values[2]);
}

string Mul::evaluate()
{
    double values[3] = eval();
    values[2] = values[0] * values[1];
    return to_string(values[2]);
}

string Pow::evaluate()
{
    double values[3] = eval();
    values[2] = std::pow(values[0], values[1]);
    return to_string(values[2]);
}