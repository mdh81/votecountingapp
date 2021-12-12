#include "Command.h"
#include "ParserCollection.h"
#include "CandidatesFileParser.h"
#include "Candidate.h"
#include <string>
#include <vector>
using namespace std;

string LoadCandidatesCommand::execute(const vector<string>& arguments) {
    // Check usage
    if (arguments.size() != 1) {
        return getUsage();
    }
    
    // Load candidates file 
    string output;
    CandidatesFileParser& parser = ParserCollection::getInstance().getCandidatesFileParser();
    parser.parseFile(arguments.at(0));
    output += "File Loaded Successfully";

    // Build candidate objects and transfer ownership to VoteCounter
    vector<Candidate> candidateObjects;
    auto& candidateNames = parser.getCandidates(); 
    unsigned char prefix = 'A';
    for (auto candidateName : candidateNames) {
        Candidate candidate(candidateName, std::to_string(++prefix));
    }

    return output;
}