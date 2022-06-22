

#include "istate_selector.hpp"
#include "def.hpp"

#include <algorithm>

namespace SAI
{
    SAI_TEMPLATE_STATE_PARAMETERS
    SAI_GENERIC_STATE* MaxProbabilityStateSelector<SAI_STATE_PARAMETERS>::SelectState(
        const std::vector<SAI_GENERIC_STATE*>& states
    ) const
    {
        return std::max_element(
            states.begin(), 
            states.end(), 
            [](SAI_GENERIC_STATE* a, SAI_GENERIC_STATE* b) {
                return a->GetProbability() < b->GetProbability();
        });
    }
}
