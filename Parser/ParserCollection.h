#ifndef VCAPP_PARSER_COLLECTION
#define VCAPP_PARSER_COLLECTION

#include "CommandsFileParser.h"
#include "CandidatesFileParser.h"

class ParserCollection {
    public:
        static ParserCollection& getInstance() {
            static ParserCollection parserCollection;
            return parserCollection;
        }
        
        CommandsFileParser& getCommandsFileParser() { 
            return m_commandsFileParser; 
        }
        
        CandidatesFileParser& getCandidatesFileParser() { 
            return m_candidatesFileParser;
        }

    private:
        // Private constructor to ensure multiple instances can't be created
        ParserCollection() = default;
        
    public:
        // Prevent copies 
        ParserCollection(const ParserCollection&) = delete;
        ParserCollection(ParserCollection&&) = delete;
        // Assignments of the single instance to itself is meaningless, disallow it 
        ParserCollection& operator=(const ParserCollection&) = delete;
        ParserCollection& operator=(ParserCollection&&) = delete;

    private:
        CommandsFileParser m_commandsFileParser;
        CandidatesFileParser m_candidatesFileParser;
    
};

#endif