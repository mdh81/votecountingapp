#include "CandidatesFileParser.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

const vector<string>& CandidatesFileParser::getCandidates() {
    if (m_candidatesList.empty()) {
        // Assume there are 10 candidates for memory allocation purposes 
        m_candidatesList.reserve(10);
        
        // Tokenize m_contents by newline and return a list of candidates
        istringstream tokenizer(m_contents);
        string line;
        while (std::getline(tokenizer,line)) {
            auto isNotWhiteSpace = [](char c) { return c != ' ' && c != '\t' && c != '\v' && c != '\f'; };
            line.erase(line.begin(), std::find_if(line.begin(), line.end(), isNotWhiteSpace));
            line.erase(std::find_if(line.rbegin(), line.rend(), isNotWhiteSpace).base(), line.end());
            if (!line.empty())
                m_candidatesList.push_back(line);
        }
    }
    return m_candidatesList;
}
