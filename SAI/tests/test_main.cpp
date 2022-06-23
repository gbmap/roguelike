
#include <catch.hpp>
#include "..\state_machine.hpp"

using namespace SAI;

template class StateMachine<void>;

TEST_CASE("MaxProbabilityStateSelector 2.0 > 1.0", "[MaxProbabilityStateSelector]")
{
    FixedProbabilityState<void> stateA(1.0);
    FixedProbabilityState<void> stateB(2.0);

    MaxProbabilityStateSelector<void> selector;

    StateMachine<void> stateMachine;
    stateMachine.AddState(&stateA);
    stateMachine.AddState(&stateB);

    REQUIRE(stateMachine.GetCurrentState(&selector, nullptr) == &stateB);
}
