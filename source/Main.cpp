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
    string configurationFileName = argv[1], fileName = argv[2];
    string logFileName = fileName.substr(0, fileName.length() - 4) + ".log";

    // open log file
    Writer::getInstance().open(logFileName);

    // read configuration file
    Configuration::getInstance().readConfiguration(configurationFileName);

    // creates compiler
    Compiler *compiler = new Compiler;

    // make imf file
    string imfFileName = compiler->compile(fileName);

    // execute imf file with Machine
    Machine::getInstance().execute(imfFileName);

    // close log file
    Writer::getInstance().close();

    return 0;
}
