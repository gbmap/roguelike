

#ifndef SAI_ISTATE_SELECTOR_HPP
#define SAI_ISTATE_SELECTOR_HPP

/*
    A state selector defines a function to select the
    next state based on each observed state's probability.
*/

#include "def.hpp"
#include "state.hpp"

#include <vector>
#include <algorithm>

namespace SAI
{
    SAI_TEMPLATE_STATE_PARAMETERS
    class StateSelector
    {
    public:
        virtual SAI_GENERIC_STATE* SelectState(const std::vector<SAI_GENERIC_STATE*>& states, const SAI_STATE_PARAMETERS* parameters) const = 0;
    };

    SAI_TEMPLATE_STATE_PARAMETERS
    class MaxProbabilityStateSelector : public StateSelector<SAI_STATE_PARAMETERS>
    {
    public:
        SAI_GENERIC_STATE* SelectState(
            const std::vector<SAI_GENERIC_STATE*>& states,
            const SAI_STATE_PARAMETERS* parameters
        ) const override
        {
            return *std::max_element(
                states.begin(), 
                states.end(), 
                [parameters](SAI_GENERIC_STATE* a, SAI_GENERIC_STATE* b) {
                    return a->GetProbability(parameters) < b->GetProbability(parameters);
            });
        }
    };
}

#endif