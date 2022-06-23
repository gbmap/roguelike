
#include <SDL2/SDL.h>
#include <libtcod.hpp>

#include "SAI/state_machine.hpp"

#define clamp01(a) (a < 0.0f ? 0.0f : (a > 1.0f ? 1.0f : a));

struct Stats 
{
  std::array<int, 2> position;
  float food;
  float energy;
};

// A potential problem here is collision with user provided
// state ids. This can be mitigated with an algorithm for
// generating unique state ids.

// The state machine API could aos implement collision testing
// when adding states.
SAI::State<Stats> stateSeekFood = SAI::State<Stats>(0,
  [](const Stats* parameters) {
    return 1.0f - parameters->food;
});

SAI::State<Stats> stateSeekShelter = SAI::State<Stats>(1,
  [](const Stats* parameters) {
    return 1.0f - parameters->energy;
});

SAI::State<Stats> stateLeisure = SAI::State<Stats>(2,
  [](const Stats* parameters) {
    return parameters->energy * parameters->food;
});

void UpdateStats(Stats* stats, float dt)
{
  stats->food = clamp01(stats->food - 0.05f*dt);
  stats->energy = clamp01(stats->energy - 0.025f*dt);
}

int main(int argc, char* argv[]) 
{
  auto console = tcod::Console{80, 25};  // Main console.

  // Configure the context.
  auto params = TCOD_ContextParams{};
  params.tcod_version = TCOD_COMPILEDVERSION;  // This is required.
  params.console = console.get();  // Derive the window size from the console size.
  params.window_title = "Libtcod Project";
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.vsync = true;
  params.argc = argc;  // This allows some user-control of the context.
  params.argv = argv;

  auto context = tcod::new_context(params);

  Stats stats;
  stats.position = {0,0};
  stats.energy = 1.0f;
  stats.food = 1.0f;

  SAI::StateMachine<Stats> stateMachine;
  stateMachine.AddState(&stateSeekFood);
  stateMachine.AddState(&stateSeekShelter);
  stateMachine.AddState(&stateLeisure);

  SAI::MaxProbabilityStateSelector<Stats> selector;

  while (1) 
  {  

    float dt = 1.0; 
    UpdateStats(&stats, dt);

    SAI::State<Stats>* pCurrentState = stateMachine.GetCurrentState(&selector, &stats);
    std::string stateName = "";

    TCOD_console_clear(console.get());

    // String addition is bad.
    std::string strPosition = "(" + std::to_string(stats.position[0]) + ", " + std::to_string(stats.position[1]) + ")";
    tcod::print(console, {0,0}, strPosition, std::nullopt, std::nullopt);

    tcod::print(console, {3,3}, "F", std::nullopt, std::nullopt);
    tcod::print(console, {7,7}, "S", std::nullopt, std::nullopt);
    tcod::print(console, {3,7}, "L", std::nullopt, std::nullopt);

    std::string strStats = "Food: " + std::to_string(stats.food) + " Energy: " + std::to_string(stats.energy);
    tcod::print(console, {0,24}, strStats, std::nullopt, std::nullopt);
    tcod::print(console, {0,23}, stateName, std::nullopt, std::nullopt);

    tcod::print(console, stats.position, "@", std::nullopt, std::nullopt);
    context->present(console);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      // context->convert_event_coordinates(event);  // Optional, converts pixel coordinates into tile coordinates.
      switch (event.type) {
        case SDL_QUIT:
          return 0;  // Exit.
      }
    }

    SDL_Delay(1000);
  }
}