#include "CommandsFileParser.h"
#include <iostream>
#include <sstream>
using namespace std;

void CommandsFileParser::parseFile(const string& fileName) {
    m_commandsMap.clear();
    FileParser::parseFile(fileName);
}

// NOTE: This method leans on RVO to eliminate copies of returned data
vector<string> CommandsFileParser::getCommands() {
    if (m_commandsMap.empty()) {
        // Tokenize m_contents by newline and return a list of candidates
        istringstream tokenizer(m_contents);
        string line;
        // Limitation: The below logic assumes command descriptions are of the form
        // command name [<command argument 1>] [<command argument 2>]
        // It does not have any error handling for entries that don't conform to this format
        while (std::getline(tokenizer,line)) {
            auto isNotWhiteSpace = [](char c) { return c != ' ' && c != '\t' && c != '\v' && c != '\f'; };
            line.erase(line.begin(), std::find_if(line.begin(), line.end(), isNotWhiteSpace));
            line.erase(std::find_if(line.rbegin(), line.rend(), isNotWhiteSpace).base(), line.end());
            if (!line.empty()) {
                // Split command definition into command and arguments
                string cmdName;
                vector<string> cmdArgs;
                unsigned cmdTokNum = 0;
                auto sepPos = line.find_first_of(' ');
                if (sepPos == string::npos) {
                    cmdName = line;
                } else {
                    cmdName = line.substr(0, sepPos);
                    string args = line.substr(sepPos+1);
                    istringstream argsStream(args);
                    string argTok;
                    while(getline(argsStream, argTok, '<')) {
                        if(argTok.empty()) continue;
                        cmdArgs.push_back(argTok.substr(0, argTok.find_first_of('>')));
                    }
                }
                
                // Skip duplicate commands
                auto itr = m_commandsMap.find(cmdName);
                if (itr == m_commandsMap.end()) {
                    m_commandsMap.try_emplace(cmdName, std::move(cmdArgs));
                }
            }
        }
    }
    vector<string> commands;
    commands.reserve(m_commandsMap.size());
    for (auto& entry : m_commandsMap) {
        commands.push_back(entry.first);
    }
    return commands;
}

// NOTE: This method leans on RVO to eliminate copies of returned data
vector<string> CommandsFileParser::getCommandArguments(const string& command) const {
    auto itr = m_commandsMap.find(command);
    if (itr == m_commandsMap.end()) throw runtime_error("Command '" + command + "' undefined");
    return itr->second;
}

