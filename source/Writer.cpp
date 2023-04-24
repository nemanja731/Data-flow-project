#pragma once;
#include "Writer.h"

using namespace std;

// open file
void Writer::open(string file)
{
    fileName.open(file);
}

// close file
void Writer::close()
{
    fileName.close();
}

// write to file
void Writer::write(string text)
{
    fileName << text << endl;
}