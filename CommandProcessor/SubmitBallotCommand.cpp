#include "Command.h"
#include "VoteCounter.h"
#include "Ballot.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

string SubmitBallotCommand::execute(const vector<string>& arguments) {
    if (arguments.empty()) { return getUsage(); }
    VoteCounter& voteCounter = VoteCounter::getInstance();
    std::vector<Candidate*> candidates;
    // Validate ballot choices
    unordered_set<string> uniqueCandidates;
    for (auto& candidatePrefix : arguments) {
        // 1) Ignore duplicate chocies while retaining the order of ballot entries
        if (!uniqueCandidates.insert(candidatePrefix).second) continue;
        // 2) Ignore invalid choices
        if (!voteCounter.hasCandidate(candidatePrefix)) continue;
        // 3) Store valid choices
        // C++ doesn't allow overload by return type, so call the plural method to
        // get a single Candidate* 
        candidates.push_back(voteCounter.getCandidates({candidatePrefix}).at(0));
    }
    if(candidates.empty()) { return "Ballot Rejected: No valid choices on the ballot"; } 
    voteCounter.addBallot(std::make_unique<Ballot>(candidates));
    return "Ballot Submitted"; 
}