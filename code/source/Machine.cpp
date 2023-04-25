#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Event.h"
#include "Machine.h"
#include "Memory.h"
#include "Sched.h"
#include "Writer.h"

using namespace std;

Machine &Machine::getInstance()
{
    static Machine instance;
    return instance;
}

void Machine::readImf(string fileName)
{
    ifstream inputFile(fileName);
    string line, token;
    string op, dest, var1, var2;
    Operation *temporary;

    // for each line of .imf file creates operation object
    while (getline(inputFile, line))
    {
        stringstream ss(line);

        ss >> token >> op >> dest >> var1;

        if (op == "=")
        {
            temporary = new Equal(token, dest);
            temporary->setInput(0, var1);
        }
        else
        {
            ss >> var2;
            switch (op[0])
            {
            case '+':
                temporary = new Add(token, dest);
                break;
            case '*':
                temporary = new Mul(token, dest);
                break;
            case '^':
                temporary = new Pow(token, dest);
                break;
            default:
                break;
            }
            temporary->setInput(0, var1);
            temporary->setInput(1, var2);
        }
        // push all operations in waitingOperations
        waitingOperations.push_back(temporary);
    }
}

// push all ready files on scheduler and move all ready files from waiting to executing
void Machine::schedule()
{
    int i = 0;
    while (i < waitingOperations.size())
    {
        if (waitingOperations[i]->check())
        {
            Event::create(waitingOperations[i], waitingOperations[i]->getTime());
            waitingOperations[i]->setStartTime(Scheduler::Instance()->getCurTime());
            executingOperations.push_back(waitingOperations[i]);
            waitingOperations.erase(waitingOperations.begin() + i);
        }
        else
            ++i;
    }
}

// put operations ready for execution on scheduler
void Machine::execute(string fileName)
{
    // read machine
    readImf(fileName);

    // process all ready operations until they are all done
    while ((!waitingOperations.empty()) || (!executingOperations.empty()))
    {
        schedule();
        Scheduler::Instance()->processNow();
    }

    // save Memory state
    Memory::getInstance().save(fileName);

    // close log file
    Writer::getInstance().close();
}

// update all operations
void Machine::updateAllOperations(string name, string value)
{

    for (int i = 0; i < waitingOperations.size(); ++i)
        waitingOperations[i]->updateInput(name, value);

    // all completed operations should be removed
    int i = 0;
    while (i < executingOperations.size())
        if (executingOperations[i]->done())
        {
            delete executingOperations[i];
            executingOperations.erase(executingOperations.begin() + i);
        }
        else
            ++i;

    // schedule ready operations
    schedule();
}