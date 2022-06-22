

#ifndef SAI_ISTATE_SELECTOR_HPP
#define SAI_ISTATE_SELECTOR_HPP

/*
    A state selector defines a function to select the
    next state based on each observed state's probability.
*/

#include "def.hpp"
#include "istate.hpp"

#include <vector>

namespace SAI
{
    SAI_TEMPLATE_STATE_PARAMETERS
    class IStateSelector
    {
    public:
        virtual SAI_GENERIC_STATE* SelectState(
            const std::vector<SAI_GENERIC_STATE*>& states
        ) const = 0;
    };

    SAI_TEMPLATE_STATE_PARAMETERS
    class MaxProbabilityStateSelector : public IStateSelector
    {
    public:
        SAI_GENERIC_STATE* SelectState(
            const std::vector<SAI_GENERIC_STATE*>& states
        ) const override;
    }
}

#endif