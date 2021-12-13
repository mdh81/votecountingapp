#include "Command.h"
#include <string>
#include <vector>
using namespace std;

string TallyCommand::execute(const vector<string>& arguments) {
    if (!arguments.empty()) { return getUsage(); }
    string output;
    return output;
}