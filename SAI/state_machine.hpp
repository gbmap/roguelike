

/***********
 
Statistical State Machine

Statistically based state machine where its decisions are
made through a discrete probability distribution where each state is
a sample.

***********/

#ifndef SAI_H
#define SAI_H

#include <vector>

#include "def.hpp"
#include "state_selector.hpp"
#include "state.hpp"

namespace SAI
{
    /*
        Holds a collection of states and provides a method to select
        the next state based on each observed state's probability.
    */
    SAI_TEMPLATE_STATE_PARAMETERS
    class StateMachine
    {
    public:
        StateMachine(std::shared_ptr<StateSelector<SAI_STATE_PARAMETERS>> pStateSelector = nullptr)
            : pStateSelector(pStateSelector) {}

        void AddState(SAI_GENERIC_STATE* pState);
        void RemoveState(SAI_GENERIC_STATE* pState);
        
        SAI_GENERIC_STATE* GetCurrentState(
            const SAI_STATE_PARAMETERS* pParameters
        ) const;
    private:
        std::vector<SAI_GENERIC_STATE*> m_States;
        std::shared_ptr<StateSelector<SAI_STATE_PARAMETERS>> pStateSelector;
    };


    // ============================================================


    SAI_TEMPLATE_STATE_PARAMETERS
    void StateMachine<SAI_STATE_PARAMETERS>::AddState(SAI_GENERIC_STATE* pState)
    {
        this->m_States.push_back(pState);
    }

    SAI_TEMPLATE_STATE_PARAMETERS
    void StateMachine<SAI_STATE_PARAMETERS>::RemoveState(SAI_GENERIC_STATE* pState)
    {
        auto it = std::find(m_States.begin(), m_States.end(), pState);
        if (it != m_States.end())
            m_States.erase(it);
    }

    SAI_TEMPLATE_STATE_PARAMETERS
    SAI_GENERIC_STATE* StateMachine<SAI_STATE_PARAMETERS>::GetCurrentState(
        const SAI_STATE_PARAMETERS* parameters
    ) const
    {
        return pStateSelector->SelectState(m_States, parameters);
    }
}

#endif 