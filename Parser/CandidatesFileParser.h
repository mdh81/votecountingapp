#ifndef CANDIDATE_FILE_PARSER
#define CANDIDATE_FILE_PARSER

#include "FileParser.h"
#include <string>
#include <vector>

class CandidatesFileParser : public FileParser {
    public:
        void parseFile(const std::string& fileName);
        const std::vector<std::string>& getCandidates();
    private:
        std::vector<std::string> m_candidatesList;
};

#endif
