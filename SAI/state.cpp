#include "state.hpp"

namespace SAI
{
    SAI_TEMPLATE_STATE_PARAMETERS
    State<SAI_STATE_PARAMETERS>::State(
        const t_stateId& id,
        FUNC_PTR_GET_PROBABILITY(fncGetProbability)
    ) {
        m_id = id;
        m_fncGetProbability = fncGetProbability;
    } 
}