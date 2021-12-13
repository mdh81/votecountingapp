#ifndef VCAPP_COMMAND_CATALOG_H
#define VCAPP_COMMAND_CATALOG_H

#include "Command.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

class CommandCatalog {
    public:
        Command& getCommand(const std::string& commandName);
        // No throw alternative to getCommand
        bool hasCommand(const std::string& commandName) { return m_commandsMap.find(commandName) != m_commandsMap.end(); }
        void initialize(const std::string& commandsFileName); 
        std::vector<std::string> getAllCommands() const;
    
    public:
        static CommandCatalog& getInstance() {
            static CommandCatalog instance;
            return instance;
        }
        CommandCatalog(const CommandCatalog&) = delete;
        CommandCatalog(CommandCatalog&&) = delete;
        CommandCatalog& operator=(const CommandCatalog&) = delete;
        CommandCatalog& operator=(CommandCatalog&&) = delete;
    
    private:
        CommandCatalog() = default;

    private:
        std::unordered_map<std::string, std::unique_ptr<Command>> m_commandsMap;
};

#endif