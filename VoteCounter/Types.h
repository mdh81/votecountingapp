#ifndef VCAPP_TYPES_H
#define VCAPP_TYPES_H

#include "Candidate.h"
#include <vector>

namespace VCTypes {
    
    using CandidateVector = std::vector<Candidate>;
    using CandidateReference = CandidateVector::const_iterator;
    using CandidateReferences = std::vector<CandidateReference>;

};

#endif