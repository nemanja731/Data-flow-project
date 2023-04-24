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

    // read configuration file
    Configuration::getInstance().readConfiguration(configurationFileName, fileName);

    // creates compiler
    Compiler *compiler = new Compiler;

    // make imf file
    string imfFileName = compiler->compile(fileName);

    // execute imf file with Machine
    Machine::getInstance().execute(imfFileName);

    return 0;
}
