#ifndef SAI_ISTATE_HPP
#define SAI_ISTATE_HPP

#include "def.hpp"

namespace SAI
{
    typedef float t_probability;
    typedef unsigned int t_stateId;

#define FUNC_PTR_GET_PROBABILITY(fncGetProbability) \
 t_probability (*fncGetProbability)(const SAI_STATE_PARAMETERS* pParameters)

    /*
        Defines a wrapper for a function that maps from TStateParameters -> t_probability.
    */
    SAI_TEMPLATE_STATE_PARAMETERS
    class State
    {
    public:
        State(const t_stateId& id, FUNC_PTR_GET_PROBABILITY(fncGetProbability))
        {
            m_id = id;
            m_fncGetProbability = fncGetProbability;
        }

        float GetProbability(const SAI_STATE_PARAMETERS* parameters) const
        {
            return m_fncGetProbability(parameters);
        }
    private:
        t_stateId m_id;
        FUNC_PTR_GET_PROBABILITY(m_fncGetProbability);
    };
}

#endif 