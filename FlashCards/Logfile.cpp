#include "Logfile.h"

// Initializes a new logfile at the given path
Logfile::Logfile(char* path)
{
    // Create new output file stream that overwrites the existing file
    this->ofstream = new std::ofstream(path, std::ios::out | std::ios_base::trunc);
}

Logfile::Logfile(wchar_t * path)
{
    this->ofstream = new std::ofstream(path, std::ios::out | std::ios_base::trunc);
}

Logfile::~Logfile()
{
    this->ofstream->close();
    delete this->ofstream;
}

// Write data in the logfile
void Logfile::Write(char* c)
{
    this->ofstream->write(c, strlen(c));
    this->ofstream->flush();
}
