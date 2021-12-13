#include <iostream>
using namespace std;

#include "Driver.h"
#include <fstream>

int main(int argc, char** argv) {
    Driver d;
    ofstream ofs("commands.txt");
    ofs << "load <Candidates File>\nlist\ntally\nresults <Candidate Name>\n";
    ofs.close();
    d.loadCommands("commands.txt");
    return 0;
}
