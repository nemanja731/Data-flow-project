#include <iostream>
#include <string>
#include "Compiler.h"
#include "Configuration.h"
#include "Machine.h"
#include "Sched.h"
#include "Writer.h"

using namespace std;

int main(int argc, char *argv[])
{
    string ConfigurationfileName = argv[1], fileName = argv[2];
    string logFileName = fileName.substr(0, fileName.length() - 4) + ".log";

    // read log file and configuration file
    Writer::getInstance().read(logFileName);
    Configuration::getInstance().read(ConfigurationfileName);

    // creates compiler
    Compiler *compiler = new Compiler;
    compiler->setStrategy(Configuration::getInstance().getCompilation());

    // make imf file
    string imfFileName = compiler->compile(fileName);

    // execute imf file with Machine
    Machine::getInstance().execute(imfFileName);

    // write log file
    Writer::getInstance().close();

    return 0;
}
