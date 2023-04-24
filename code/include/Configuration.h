#pragma once

#include <string>
#include <vector>

using namespace std;

class Configuration
{
public:
    static Configuration &getInstance()
    {
        static Configuration instance;
        return instance;
    }

    Configuration(const Configuration &user) = delete;
    Configuration &operator=(const Configuration &) = delete;

    void readConfiguration(string fileName);
    double getValue(string name);
    string getCompilation();

private:
    Configuration() = default;

    string compilation;
    vector<string> variableNames;
    vector<double> variableValues;
};