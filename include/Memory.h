#pragma once

#include <exception>
#include <vector>
#include <string>
#include "Config.h"

using namespace std;

// Singleton class for handling memory alocation
class Memory {
 public:

    // Return instance of Memory
    static Memory& getInstance();
    Memory(const Memory& user) = delete;
    Memory& operator=(const Memory&) = delete;

    // Write variable-value pair to memory
    void set(string varName, string val);
    // Return value of variable
    string get(string varName);

    // Check if writing to memory is avalible
    inline bool ready() const { return (in_process_ < nw_); };
    // Increment number of writings in process
    inline void reserve() { if (ready()) ++in_process_; };

    // Save Memory state to file
    void save(string filename);

 private:
    Memory() { nw_ = Config::getInstance().getValue("Nw"); };

    int nw_, in_process_ = 0;
    vector<string> variables_;
    vector<string> values_;

};

class VarNotAvalibleException : public exception {
    public:
    VarNotAvalibleException(const char* msg) : exception(), msg_(msg) {};
    const char * what () const throw () {
        return msg_;
    }
    private:
        const char* msg_;
};
