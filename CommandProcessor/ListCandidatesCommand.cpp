#include "Command.h"
#include "VoteCounter.h"
#include <string>
#include <vector>
using namespace std;

string ListCandidatesCommand::execute(const vector<string>& arguments) {
    if (!arguments.empty()) { 
        return getUsage();
    }
    const Candidate::CandidateVector& candidates = VoteCounter::getInstance().getCandidates();
    string output;
    if (candidates.empty()) { 
        output += "Candidates list is empty\n";
        return output;
    }
    for (size_t i = 0; i < candidates.size(); ++i) { 
        output += candidates.at(i)->getPrefix() + ".\t" + candidates.at(i)->getName() + (i == candidates.size()-1 ? "" : "\n");
    }
    return output;
}