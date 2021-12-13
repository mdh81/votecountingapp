#ifndef VCAPP_COMMAND_PROCESSOR_H
#define VCAPP_COMMAND_PROCESSOR_H
#include <string>
#include <iostream>
#include "CommandCatalog.h"

class CommandProcessor {
    public:
        static CommandProcessor& getInstance() {
            static CommandProcessor instance;
            return instance;
        }
        void initialize(const std::string& commandsFileName);
        void cmdLoop(std::istream& inputStream = std::cin, std::ostream& outputStream = std::cout) const;
    
    public:
        CommandProcessor(const CommandProcessor&) = delete;
        CommandProcessor(CommandProcessor&&) = delete;
        CommandProcessor& operator=(const CommandProcessor&) = delete;
        CommandProcessor& operator=(CommandProcessor&&) = delete;
    private:
        CommandProcessor() : m_commandCatalog(CommandCatalog::getInstance()) {}

    private:
        CommandCatalog& m_commandCatalog;

};

#endif