#ifndef SAI_ISTATE_HPP
#define SAI_ISTATE_HPP

#include "def.hpp"

namespace SAI
{
    SAI_TEMPLATE_STATE_PARAMETERS
    class IState
    {
    private:

        // Factor to be applied to this state's probability.
        // This is used to adjust the probability of the state. 
        // It enables us to describe an agent's personality through
        // a vector of state weights. E. g., an aggressive agent could
        // increase its AttackState probability by a factor of 2.
        float m_fWeight;
    public:
        virtual float GetProbability(const SAI_STATE_PARAMETERS* parameters) const = 0;

        float GetWeight() const { return m_fWeight; }
        void SetWeight(const float& value) { m_fWeight = value; }
    };

    SAI_TEMPLATE_STATE_PARAMETERS
    class FixedProbabilityState : public IState<SAI_STATE_PARAMETERS>
    {
    public:
        FixedProbabilityState(const float& probability) { this->m_fProbability = probability; }
        float GetProbability(const SAI_STATE_PARAMETERS* parameters) const override
        {
            return this->m_fProbability;
        }
    private:
        float m_fProbability;
    };

}

#endif 