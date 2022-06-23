
#include <catch.hpp>
#include "..\state_machine.hpp"

using namespace SAI;

template class StateMachine<void>;

TEST_CASE("MaxProbabilityStateSelector 2.0 > 1.0", "[MaxProbabilityStateSelector]")
{

    State<void> stateA = SAI::State<void>(0, [](const void* pParameters) { return 0.0f; });
    State<void> stateB = SAI::State<void>(1, [](const void* pParameters) { return 1.0f; });

    MaxProbabilityStateSelector<void> selector;

    StateMachine<void> stateMachine;
    stateMachine.AddState(&stateA);
    stateMachine.AddState(&stateB);

    REQUIRE(stateMachine.GetCurrentState(&selector, nullptr) == &stateB);
}
