#pragma once 

#include "../../data/models/NecessaryFiles.h"

class CommandLineParserInterface {
public:

    virtual NecessaryFiles ParseCommandLine(int argc, char* argv[]) = 0;
};