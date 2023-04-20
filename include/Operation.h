#pragma once

#include <string>
#include <vector>
#include "Interfaces.h"
#include "Types.h"
#include "Logger.h"
#include "Config.h"

using namespace std;

// Abstracts class for simulation of data flow operation
class Operation : public ITimedElement {
 public:
    Operation(string token, string outputName) \
        : token_(token), output_name_(outputName) {};
    Operation(const Operation& user) = delete;
    Operation& operator=(const Operation&) = delete;

    // Set value of port
    void setPort(int portNumber, string variable);
    // Update value of token
    void updatePort(string varName, string newValue);
    // Check if all ports have numbers in them
    virtual bool check();
    // Interface with Scheduler class
    void notify(ID id);
    // Calculate output of operation (virtual)
    virtual string evaluate() = 0;

    inline bool done() const { return done_; };
    // Set start time of operation
    inline void setStart(double time) { 
        start_time_ = to_string((int) time);
    }
    inline double execTime() const { return time_; };

    // Privremeno
    string token_, output_name_;
 protected:
    string start_time_, end_time_;
    bool done_ = false;
    double time_;
    vector<string> in_ports_;
};

// Equals operation Class
class Equal : public Operation {
 public:
    Equal(string token, string outputName) \
        : Operation { token, outputName } {
        in_ports_.resize(1);
        time_ = Config::getInstance().getValue("Tw");
    };
    bool check() override;
 private:
    string evaluate() override;
};

// Addition operation Class
class Add : public Operation {
 public:
    Add(string token, string outputName) \
        : Operation { token, outputName } {
        in_ports_.resize(2);
        time_ = Config::getInstance().getValue("Ta");
    };
 private:
    string evaluate() override;
};

// Multiplication operation Class
class Mul : public Operation {
 public:
    Mul(string token, string outputName) \
        : Operation { token, outputName } {
        in_ports_.resize(2);
        time_ = Config::getInstance().getValue("Tm");
    };
 private:
    string evaluate() override;
};

// Power operation Class
class Pow : public Operation {
 public:
    Pow(string token, string outputName) \
        : Operation { token, outputName } {
        in_ports_.resize(2);
        time_ = Config::getInstance().getValue("Te");
    };
 private:
    string evaluate() override;
};
