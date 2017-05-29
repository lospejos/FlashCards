#pragma once
#include <string>
#include <fstream>
#include <iostream>

class Logfile
{
private:
    std::ofstream* ofstream;

public:
    Logfile (char* path);
    Logfile (wchar_t* path);
    ~Logfile ();
    void Write (char* c);
};