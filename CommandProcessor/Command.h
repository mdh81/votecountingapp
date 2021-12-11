#ifndef VCAPP_COMMANDS_H
#define VCAPP_COMMANDS_H

#include <string>

class Command {
    public:
        virtual std::string execute(const std::string& argument = "") = 0;
        virtual ~Command() = default;
};

class LoadCanidatesCommand : public Command {
    public:
        std::string execute(const std::string& argument) override;
};

class SubmitBallotCommand : public Command {
    public:
        std::string execute(const std::string& argument) override;
};

class TallyCommand : public Command {
    public:
        std::string execute(const std::string& argument) override;
};

class ViewResultsCommand : public Command {
    public:
        std::string execute(const std::string& argument) override;
};


#endif