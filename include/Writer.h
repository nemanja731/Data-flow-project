#pragma once

#include <fstream>
#include <string>
#include "Operation.h"

using namespace std;

class Writer
{
public:
    static Writer &getInstance()
    {
        static Writer instance;
        return instance;
    }

    void open(string fileName);
    void write(string text);
    void close();

private:
    Writer() = default;
    ofstream file;
};