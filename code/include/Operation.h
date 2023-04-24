#pragma once

#include <string>
#include <vector>
#include "Configuration.h"
#include "Interfaces.h"
#include "Types.h"
#include "Writer.h"

using namespace std;

// abstracts class
class Operation : public ITimedElement
{
public:
    Operation(string token, string outputName) : token(token), outputName(outputName){};
    Operation(const Operation &user) = delete;
    Operation &operator=(const Operation &) = delete;

    virtual string evaluate() = 0;
    virtual bool check();

    void setInput(int inputNumber, string variable);
    void updateInput(string varName, string newValue);
    void notify(ID id);
    bool done() const;
    void setStartTime(double time);
    double getTime() const;

    string token, outputName;

protected:
    string startTime, endTime;
    bool done = false;
    double time;
    vector<string> inputs;
};

class Equal : public Operation
{
public:
    Equal(string token, string outputName) : Operation{token, outputName}
    {
        inputs.resize(1);
        time = Configuration::getInstance().getValue("Tw");
    };
    bool check() override;

private:
    string evaluate() override;
};

class Add : public Operation
{
public:
    Add(string token, string outputName) : Operation{token, outputName}
    {
        inputs.resize(2);
        time = Configuration::getInstance().getValue("Ta");
    };

private:
    string evaluate() override;
};

class Mul : public Operation
{
public:
    Mul(string token, string outputName) : Operation{token, outputName}
    {
        inputs.resize(2);
        time = Configuration::getInstance().getValue("Tm");
    };

private:
    string evaluate() override;
};

class Pow : public Operation
{
public:
    Pow(string token, string outputName) : Operation{token, outputName}
    {
        inputs.resize(2);
        time = Configuration::getInstance().getValue("Te");
    };

private:
    string evaluate() override;
};
