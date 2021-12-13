#ifndef VCAPP_VOTE_COUNTER_H
#define VCAPP_VOTE_COUNTER_H

#include "Candidate.h"
#include "Ballot.h"
#include <vector>
#include <unordered_map>

class VoteCounter {
    public:
        static VoteCounter& getInstance() {
            static VoteCounter instance;
            return instance;
        }
        // Getters and setters for Candidates
        // NOTE: Assumes ownership of Candidate objects
        void setCandidates(std::vector<Candidate>&& candidates);
        // Get all registered candidates
        const std::vector<Candidate>& getCandidates() const { return m_candidates; }
        // Get candidate with given prefix
        // NOTE: throws if there is no candidate with the given name
        const Candidate& getCandidate(const std::string& prefix) const; 
        // Get reference to a candidate with the given prefix
        // NOTE: throws if there is no candidate with the given name 
        Candidate::CandidateReference getCandidateReference(const std::string& prefix) const;
        // No throw alternative that returns a boolean to indicate the presence of a candidate
        // with the given prefix
        bool hasCandidate(const std::string& prefix) const;

        // Getters and setters for Ballots
        // NOTE: Assumes ownership of the input Ballot object
        void processBallot(Ballot&& ballot);
        const Ballot::BallotVector& getBallots() const { return m_ballots; }

        // Clears the state
        void reset() { m_ballots.clear(); m_candidates.clear(); }

    public:
        // Copy and move not allowed to enforce single instance
        VoteCounter(VoteCounter&) = delete;
        VoteCounter(VoteCounter&&) = delete;
        // Assignments are invalid
        VoteCounter& operator=(VoteCounter&) = delete;
        VoteCounter& operator=(VoteCounter&&) = delete;

    private:
        VoteCounter() = default; 
        Candidate::CandidateVector m_candidates;
        Ballot::BallotVector m_ballots;
        using CandidatePrefixMap = std::unordered_map<std::string, Candidate::CandidateReference>;
        CandidatePrefixMap m_candidatePrefixMap;
};


#endif