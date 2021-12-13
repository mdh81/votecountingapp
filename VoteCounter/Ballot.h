#ifndef VCAPP_BALLOT_H
#define VCAPP_BALLOT_H

#include "Candidate.h"
#include <vector>

class Ballot {
    public:
        Ballot(const std::vector<Candidate*>& candidates);
        const std::vector<Candidate*>& getPreferredCandidates() const { return m_preferredCandidates; }
        void setExhausted() { m_exhausted = true; }
        bool isExhausted() const { return m_exhausted; }
        Candidate* getPreferredCandidate() { return m_currentPreferredCandidate; };
        // Evaluate a ballot by checking the list of preferred candidate.
        // If none of the preferred candidates are in the running the ballot
        // will be marked exhausted
        Candidate* evaluate();

    public:
        // Ballots are distinct objects. Disable copy construction
        Ballot(const Ballot&) = delete;
        // Ballots are distinct objects. Disable copy construction
        Ballot(Ballot&&) = delete; 
        // Assignment of ballot objects is an invalid operation
        Ballot& operator=(const Ballot&) = delete;
        Ballot& operator=(Ballot&&) = delete;

    public:
        using BallotVector = std::vector<std::unique_ptr<Ballot>>;

    private:
        std::vector<Candidate*> m_preferredCandidates;
        bool m_exhausted;
        Candidate* m_currentPreferredCandidate;
};

#endif