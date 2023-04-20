#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <vector>
#include <map>
#include <set>

using namespace std;

// Strategy class for compiling .txt to .imf file
// Apstract class
class CompilationStrategy {
 public:
    virtual void compile(string filepath) = 0;
 protected:
    // Infix to postfix equation
    string inf2post(string infix);
    
    // Returns next variable, value or operation in a given string
    string readNext(string input, int* it);
    bool checkOperation(string c);
    bool checkOperation(char c);
};

class SimpleCompilationStrategy : public CompilationStrategy{
 public:
    virtual void compile(string filepath) override;
};

class AdvancedCompilationStrategy : public CompilationStrategy{
 public:
    virtual void compile(string filepath) override;
 private:
    map<string, double> scores_;
    set<string> included_in_score_;
    void sortCommands(vector<string>& commands);
    double calcScore(string c, vector<string>& commands);
    double getTime(string c);
};

// Compiler class for executing different strategies 
class Compiler {
 public:
    Compiler() = default;

    // Compile file with previously set strategy
    string compile(string filepath) const { 
        compilation_strategy_->compile(filepath); 
        return filepath.substr(0, filepath.length()-4) + ".imf";
    };

    // Set strategy type
    void setCompilationStrategy(string strategyName) {
        delete compilation_strategy_;
        if (strategyName == "simple")
            compilation_strategy_ = new SimpleCompilationStrategy;
        else if (strategyName == "advanced")
            compilation_strategy_ = new AdvancedCompilationStrategy;
    };

 private:
    CompilationStrategy* compilation_strategy_ = nullptr;
};

class UnknownCompilationStrategyException : public exception {
    public:
    UnknownCompilationStrategyException(const char* msg) : exception(), msg_(msg) {};
    const char * what () const throw () {
        return msg_;
    }
    private:
        const char* msg_;
};