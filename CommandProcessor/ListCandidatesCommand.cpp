#include "Command.h"
#include "VoteCounter.h"
#include <string>
#include <vector>
using namespace std;

string ListCandidatesCommand::execute(const vector<string>& arguments) {
    if (!arguments.empty()) { 
        return getUsage();
    }
    const vector<Candidate>& candidates = VoteCounter::getInstance().getCandidates();
    string output;
    if (candidates.empty()) { 
        output += "Candidates list is empty\n";
        return output;
    }
    for (const auto& candidate : candidates) {
        output += candidate.getPrefix() + ".\t" + candidate.getName() + "\n";
    }
    return output;
}