#ifndef VCAPP_COMMANDS_H
#define VCAPP_COMMANDS_H

#include <string>

class Command {
    public:
        virtual std::string execute(const std::string& argument = "") = 0;
        virtual ~Command() = default;
};

class ListCandidatesCommand : public Command {
    public:
        ListCandidatesCommand() = default;
        std::string execute(const std::string& argument) override;
};

class LoadCandidatesCommand : public Command {
    public:
        LoadCandidatesCommand() = default;
        std::string execute(const std::string& argument) override;
};

class SubmitBallotCommand : public Command {
    public:
        SubmitBallotCommand() = default;
        std::string execute(const std::string& argument) override;
};

class TallyCommand : public Command {
    public:
        TallyCommand() = default;
        std::string execute(const std::string& argument) override;
};

class ViewResultsCommand : public Command {
    public:
        ViewResultsCommand() = default;
        std::string execute(const std::string& argument) override;
};


#endif