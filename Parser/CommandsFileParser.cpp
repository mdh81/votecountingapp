#include "CommandsFileParser.h"
#include <iostream>
#include <sstream>
using namespace std;

// NOTE: This method leans on RVO to eliminate copies of returned data
vector<string> CommandsFileParser::getCommands() {
    if (m_commandsMap.empty()) {
        // Tokenize m_contents by newline and return a list of candidates
        istringstream tokenizer(m_contents);
        string line;
        while (std::getline(tokenizer,line)) {
            auto isNotWhiteSpace = [](char c) { return c != ' ' && c != '\t' && c != '\v' && c != '\f'; };
            line.erase(line.begin(), std::find_if(line.begin(), line.end(), isNotWhiteSpace));
            line.erase(std::find_if(line.rbegin(), line.rend(), isNotWhiteSpace).base(), line.end());
            if (!line.empty()) {
                // Split command definition into command and argument
                string cmdName;
                string cmdArg; // Limitation: Only single argument supported
                auto sepIndex = line.find(' ');
                if (sepIndex != string::npos) {
                    cmdName = line.substr(0, sepIndex);
                    cmdArg = line.substr(sepIndex+1);
                } else {
                    cmdName = line;
                }
                // Skip duplicate commands
                auto itr = m_commandsMap.find(cmdName);
                if (itr == m_commandsMap.end()) {
                    m_commandsMap.emplace(cmdName, cmdArg);
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

string CommandsFileParser::getCommandArgument(const string& command) const {
    auto itr = m_commandsMap.find(command);
    if (itr == m_commandsMap.end()) throw runtime_error("Command '" + command + "' undefined");
    return itr->second;
}

