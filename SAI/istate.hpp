


#ifndef SAI_ISTATE_HPP
#define SAI_ISTATE_HPP

#include "def.hpp"

namespace SAI
{
    SAI_TEMPLATE_STATE_PARAMETERS
    class IState
    {
    private:
        float m_fWeight;
    public:
        virtual float GetProbability(const SAI_STATE_PARAMETERS* parameters) const = 0;

        float GetWeight() const;
        void SetWeight(float value);
    };
}

#endif 