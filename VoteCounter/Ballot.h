#ifndef VCAPP_BALLOT_H
#define VCAPP_BALLOT_H

#include "Candidate.h"
#include "Types.h"
#include <vector>
#include <memory>

class Ballot {
    public:
        Ballot(const VCTypes::CandidateReferences& candidates) : m_candidates(candidates) { m_exhausted = false; }
        VCTypes::CandidateReferences getCandidates() const { return m_candidates; }
        void setExhausted() { m_exhausted = true; }
        bool isExhausted() const { return m_exhausted; }

    public:
        // Ballots are distinct objects. Disable copy construction
        Ballot(Ballot&) = delete;
        // Define move constructor to be able to transfer owenership
        Ballot(Ballot&&) = default; 
        // Assignment of ballot objects is an invalid operation
        Ballot& operator=(Ballot&) = delete;
        Ballot& operator=(Ballot&&) = delete;

    private:
        VCTypes::CandidateReferences m_candidates;
        bool m_exhausted;
};

#endif