#ifndef VCAPP_CANDIDATE_H
#define VCAPP_CANDIDATE_H
#include <string>
#include <vector>
#include <memory>

class Candidate {
    public:
        Candidate(const std::string& name, const std::string& prefix);
        std::string getName() const { return m_name; }
        std::string getPrefix() const { return m_prefix; }
        bool isEliminated() const { return m_eliminated; }
        void setEliminated() { m_eliminated = true; }
        void assignBallot() { ++m_numBallots; }
        size_t getNumberOfAssignedBallots() const { return m_numBallots; }
        void resetAssignment() { m_numBallots = 0; }

    public:
        // Candidates are distinct objects. Disable copy construction
        Candidate(const Candidate&) = delete;
        // Candidates are distinct objects. Disable copy construction
        Candidate(Candidate&&) = delete; 
        // Assignment of candidate objects is an invalid operation
        Candidate& operator=(const Candidate&) = delete;
        Candidate& operator=(Candidate&&) = delete; 

    public:
        using CandidateVector = std::vector<std::unique_ptr<Candidate>>;

    private:
        const std::string m_name;
        const std::string m_prefix;
        unsigned m_rank;
        bool m_eliminated;
        size_t m_numBallots;
};

#endif