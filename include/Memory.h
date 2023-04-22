#pragma once

#include <string>
#include <vector>
#include "Configuration.h"
#include "Exceptions.h"

using namespace std;

class Memory
{
public:
    Memory(const Memory &user) = delete;
    Memory &operator=(const Memory &) = delete;
    static Memory &getInstance()
    {
        static Memory instance;
        return instance;
    }

    bool isReady() const;
    void reserve();
    void save(string fileName);
    void set(string varName, string val);
    string get(string varName);

private:
    Memory();

    int nw, inProcess = 0;
    vector<string> variables;
    vector<string> values;
};
