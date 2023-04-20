#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Machine.h"
#include "Memory.h"
#include "Event.h"
#include "Sched.h"

using namespace std;

// Returns instance of Machine
Machine& Machine::getInstance() {
    static Machine instance;
    return instance;
}

// Initialize machine with .imf file
void Machine::init(string file) {
    ifstream inFile(file);
    string line, token;
    string op, dest, var1, var2;
    Operation* tmp;

    // Create operation object for each line of .imf file
    // Put all operations in waiting_ vecotor
    while (getline(inFile, line)) {
        stringstream ss(line);
        
        ss >> token >> op >> dest >> var1;

        if (op == "=") {
            tmp = new Equal(token, dest);
            tmp->setPort(0, var1);
        }
        else {
            ss >> var2;
            switch (op[0]) {
            case '+':
                tmp = new Add(token, dest);
                break;
            case '*':
                tmp = new Mul(token, dest);
                break;
            case '^':
                tmp = new Pow(token, dest);
                break;
            default:
                break;
            }
            tmp->setPort(0, var1);
            tmp->setPort(1, var2);
        }
        waiting_.push_back(tmp);
    }
}

// Put all ready files on scheduler
// Move all ready files from waiting to executing 
void Machine::scheduale() {
    int i = 0;
    while (i < waiting_.size()) {
        if (waiting_[i]->check()) {
            Event::create(waiting_[i], waiting_[i]->execTime());
            waiting_[i]->setStart(Scheduler::Instance()->getCurTime());
            executing_.push_back(waiting_[i]);
            waiting_.erase(waiting_.begin() + i);
        } else ++i;
    }
}

// Execute initialized program
void Machine::exec(string file) {

    // Init machine
    init(file);

    // Process all ready operations until they are all done
    while ((!waiting_.empty()) || (!executing_.empty())) {
        scheduale();
        Scheduler::Instance()->processNow();    
    }

    // Save Memory state
    Memory::getInstance().save(file);
}

// Update all operations with given name-value pair
void Machine::upadeState(string name, string value) {

    // Update all ports
    for (int i = 0; i < waiting_.size(); ++i)
        waiting_[i]->updatePort(name, value);
    
    // Remove all done operations
    int i = 0;
    while (i < executing_.size())
        if (executing_[i]->done()) {
            delete executing_[i];
            executing_.erase(executing_.begin() + i);
        } else ++i;

    // Schedual all now ready operations 
    scheduale();
}