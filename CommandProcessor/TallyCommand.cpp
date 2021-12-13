#include "Command.h"
#include "VoteCounter.h"
#include <string>
#include <vector>
using namespace std;

string TallyCommand::execute(const vector<string>& arguments) {
    if (!arguments.empty()) { return getUsage(); }
    string output = "\n";
    VoteCounter& vc = VoteCounter::getInstance();
    vc.tally(output);
    vc.clear();
    return output;
}