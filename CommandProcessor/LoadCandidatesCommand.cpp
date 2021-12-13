#include "Command.h"
#include "ParserCollection.h"
#include "CandidatesFileParser.h"
#include "Candidate.h"
#include "VoteCounter.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

string LoadCandidatesCommand::execute(const vector<string>& arguments) {
    // Check usage
    if (arguments.size() != 1) {
        return getUsage();
    }
    
    // Load candidates file 
    // NOTE: The command assumes that the candidates file doesn't contain duplicates 
    string output;
    CandidatesFileParser& parser = ParserCollection::getInstance().getCandidatesFileParser();
    parser.parseFile(arguments.at(0));
    output += "File Loaded Successfully";

    // Build candidate objects and transfer ownership to VoteCounter
    Candidate::CandidateVector candidateObjects;
    auto& candidateNames = parser.getCandidates();
    if (candidateNames.size() > 26) {
        output += "\nMaximum number of candidates exceeded!";
        return output;
    }

    char prefix = 'A';
    for (auto candidateName : candidateNames) {
        candidateObjects.push_back(std::make_unique<Candidate>(candidateName, string(1, prefix++)));
    }
    VoteCounter::getInstance().setCandidates(candidateObjects);

    return output;
}