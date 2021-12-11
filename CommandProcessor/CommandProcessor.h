#ifndef VCAPP_COMMAND_PROCESSOR_H
#define VCAPP_COMMAND_PROCESSOR_H
#include <string>

class CommandProcessor {
    public:
        static CommandProcessor& getInstance() {
            static CommandProcessor instance;
            return instance;
        }
    
    public:
        CommandProcessor(CommandProcessor&) = delete;
        CommandProcessor(CommandProcessor&&) = delete;
        CommandProcessor& operator=(CommandProcessor&) = delete;
        CommandProcessor& operator=(CommandProcessor&&) = delete;
    private:
        CommandProcessor() = default;
};

#endif