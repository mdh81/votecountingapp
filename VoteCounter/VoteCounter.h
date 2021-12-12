#ifndef VCAPP_VOTE_COUNTER_H
#define VCAPP_VOTE_COUNTER_H

#include "Candidate.h"
#include <vector>
#include <unordered_map>

class VoteCounter {
    public:
        static VoteCounter& getInstance() {
            static VoteCounter instance;
            return instance;
        }
        void setCandidates(std::vector<Candidate>&& candidates);
        const std::vector<Candidate>& getCandidates() const { return m_candidates; }
        const Candidate& getCandidate(const std::string& prefix) const;
    public:
        VoteCounter(VoteCounter&) = delete;
        VoteCounter(VoteCounter&&) = delete;
        VoteCounter& operator=(VoteCounter&) = delete;
        VoteCounter& operator=(VoteCounter&&) = delete;
    private:
        VoteCounter() = default; 
        using CandidateVector = std::vector<Candidate>;
        using CandidateReference = CandidateVector::iterator;
        using CandidatePrefixMap = std::unordered_map<std::string, CandidateReference>;
        CandidateVector m_candidates;
        CandidatePrefixMap m_candidatePrefixMap;
};


#endif