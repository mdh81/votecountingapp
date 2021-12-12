#ifndef VCAPP_CANDIDATE_H
#define VCAPP_CANDIDATE_H
#include <string>

class Candidate {
    public:
        Candidate(const std::string& name, const std::string& prefix);
        std::string getName() const { return m_name; }
        std::string getPrefix() const { return m_prefix; }
        unsigned getRank() const { return m_rank; }
        bool isEliminated() const { return m_eliminated; }
        void setRank(unsigned rank) { m_rank = rank; }
        void setEliminated(bool eliminated) { m_eliminated = eliminated; }

    public:
        // Candidates are distinct objects. Disable move and copy construction
        Candidate(Candidate&) = delete;
        Candidate(Candidate&&) = delete; 
        // Assignment of candidate objects is an invalid operation
        Candidate& operator=(Candidate&) = delete;
        Candidate& operator=(Candidate&&) = delete;

    private:
        const std::string m_name;
        const std::string m_prefix;
        unsigned m_rank;
        bool m_eliminated;
};

#endif