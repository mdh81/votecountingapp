#ifndef VCAPP_COMMANDS_FILE_PARSER_H
#define VCAPP_COMMANDS_FILE_PARSER_H

#include "FileParser.h"
#include <vector>
#include <string>
#include <unordered_map>

class CommandsFileParser : public FileParser {
    public:
        std::vector<std::string> getCommands();
        std::vector<std::string> getCommandArguments(const std::string& command) const;
    private:
        using CommandsMap = std::unordered_map<std::string, std::vector<std::string>>;
        CommandsMap m_commandsMap;
};

#endif