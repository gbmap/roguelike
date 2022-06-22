

/***********
 
Statistical AI

Statistically based state machine where its decisions are
made through a discrete probability distribution where each state is
a sample.

***********/

#ifndef SAI_H
#define SAI_H

#include <vector>

#include "def.hpp"

namespace SAI
{
    SAI_TEMPLATE_STATE_PARAMETERS
    class StateMachine
    {
    public:
        void AddState(SAI_GENERIC_STATE* pState);
        void RemoveState(SAI_GENERIC_STATE* pState);
        
        ISTATE* GetCurrentState() const;
    private:
        std::vector<SAI_GENERIC_STATE*> m_States;
    };
}

#endif 