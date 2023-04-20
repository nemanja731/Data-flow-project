#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Interfaces.h"
#include "Types.h"
#include "Operation.h"
#include "Memory.h"
#include "Machine.h"
#include "Logger.h"
#include "Sched.h"

using namespace std;

// Check if string is real number
bool digitString(const string s){
    return s.find_first_not_of( ".-0123456789" ) == string::npos;
}

// Set value of port
void Operation::setPort(int portNumber, string variable) {
    in_ports_.at(portNumber) = variable;
}

// Update value of token
void Operation::updatePort(string varName, string newValue) {
    for (int i = 0; i < in_ports_.size(); ++i)
        if (in_ports_[i] == varName) in_ports_[i] = newValue;
}

// Check if all ports have numbers in them
bool Operation::check() {
    try {
        for (string val : in_ports_)
            if (!digitString(val))
                return false;
    }
    catch(VarNotAvalibleException& e) {
        return false;
    }
    return true;
}

// Check if all ports have numbers in them
// Check if memory is ready for writing
bool Equal::check() {
    try {
        if (digitString(in_ports_[0]) && Memory::getInstance().ready()) {
            Memory::getInstance().reserve();
            return true;
        }
        return false;
    }
    catch(VarNotAvalibleException& e) {
        return false;
    }
}

// Interface with Scheduler class
void Operation::notify(ID id) {
    done_ = true;
    end_time_ = to_string((int) Scheduler::Instance()->getCurTime());
    string result = evaluate();

    string logData = "";
    logData = token_ + " (" + start_time_ + "-" + end_time_ + ")ns";
    Logger::getInstance().log(logData.c_str());

    Machine::getInstance().upadeState(output_name_, result);
}

string Equal::evaluate() {
    Memory::getInstance().set(output_name_, in_ports_[0]);
    return in_ports_[0];
}

string Add::evaluate() {
    double val1, val2, solution;
    val1 = atof(in_ports_[0].c_str());
    val2 = atof(in_ports_[1].c_str());
    solution = val1 + val2;
    return to_string(solution);
}

string Mul::evaluate() {
    double val1, val2, solution;
    val1 = atof(in_ports_[0].c_str());
    val2 = atof(in_ports_[1].c_str());
    solution = val1 * val2;
    return to_string(solution);
}

string Pow::evaluate() {
    double val1, val2, solution;
    val1 = atof(in_ports_[0].c_str());
    val2 = atof(in_ports_[1].c_str());
    solution = std::pow(val1, val2);
    return to_string(solution);
}