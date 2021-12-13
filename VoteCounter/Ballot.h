#ifndef VCAPP_BALLOT_H
#define VCAPP_BALLOT_H

#include "Candidate.h"
#include <vector>

class Ballot {
    public:
        Ballot(const Candidate::CandidateReferences& candidates) : m_candidates(candidates) { m_exhausted = false; }
        const Candidate::CandidateReferences& getCandidates() const { return m_candidates; }
        void setExhausted() { m_exhausted = true; }
        bool isExhausted() const { return m_exhausted; }

    public:
        // Ballots are distinct objects. Disable copy construction
        Ballot(const Ballot&) = delete;
        // Define move constructor to be able to transfer owenership
        Ballot(Ballot&&) = default; 
        // Assignment of ballot objects is an invalid operation
        Ballot& operator=(const Ballot&) = delete;
        Ballot& operator=(Ballot&&) = delete;

    public:
        using BallotVector = std::vector<Ballot>;

    private:
        Candidate::CandidateReferences m_candidates;
        bool m_exhausted;
};

#endif