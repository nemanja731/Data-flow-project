#pragma once

#include <fstream>
#include <string>
#include "Operation.h"

using namespace std;

// Singleton class for logging given data
class Logger {
 public:
    
    // Returns instance of Logger
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    // Open file for logging
    inline void init(string file) {
        logging_file_.open(file);
    }

    // Close logging file
    inline void close() {
        logging_file_.close();
    }

    // Write string to log file
    void log(string logText) {
        logging_file_ << logText << endl;
    }

 private:
    Logger() = default;
    ofstream logging_file_;
};