#include <iostream>
#include <fstream>
#include "CommandProcessor.h"
#include "Command.h"
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    // Create command file
    ofstream ofs("commands.txt");
    ofs << "load <Candidates File>\nlist\ntally\nresults <Candidate Name>\n";
    ofs.close();
    CommandProcessor& cmdProc = CommandProcessor::getInstance();
    cmdProc.initialize("commands.txt");
    // Load candidates file if the user provided it
    if (argc == 2) {
        LoadCandidatesCommand().execute({argv[1]});
    }
    cmdProc.cmdLoop();
    return 0;
}
