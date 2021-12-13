#include "Command.h"
#include "VoteCounter.h"
#include "Ballot.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

string SubmitBallotCommand::execute(const vector<string>& arguments) {
    if (arguments.empty()) { return getUsage(); }
    VoteCounter& voteCounter = VoteCounter::getInstance();
    Candidate::CandidateReferences candidates;
    // Validate ballot choices
    // 1) Ignore duplicate chocies while retaining the order of ballot entries
    set<string> uniqueCandidates(arguments.begin(), arguments.end());
    for (auto& candidatePrefix : uniqueCandidates) {
        // 2) Ignore invalid choices
        if(!voteCounter.hasCandidate(candidatePrefix)) { continue; }
        // 3) Store valid choices
        candidates.push_back(voteCounter.getCandidateReference(candidatePrefix));
    }
    if(candidates.empty()) { return "Ballot Rejected: No valid choices on the ballot"; } 
    
    voteCounter.addBallot(Ballot(candidates));
    return "Ballot Submitted"; 
}