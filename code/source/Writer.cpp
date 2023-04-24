#pragma once;
#include "Writer.h"

using namespace std;

// open file
void Writer::open(string fileName)
{
    file.open(fileName);
}

// close file
void Writer::close()
{
    file.close();
}

// write to file
void Writer::write(string text)
{
    file << text << endl;
}