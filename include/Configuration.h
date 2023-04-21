#pragma once

#include <string>
#include <vector>

using namespace std;

// Singleton class for compiler configuration management
class Config {
 public:
    static Config& getInstance() {
        static Config instance;
        return instance;
    }
    Config(const Config& user) = delete;
    Config& operator=(const Config&) = delete;

    // Initializes Config with configuration file
    void init(string filename);

    // Returns value of desired variable
    double getValue(string name);

    // Returns compilation strategy from configuration file
    string getCompilation() { return compilation_; };

 private:
    Config() = default;
    vector<string> names_;
    vector<double> values_;
    string compilation_;
};