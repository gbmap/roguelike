
#include <SDL2/SDL.h>
#include <libtcod.hpp>

#include "SAI/state_machine.hpp"
#include "SAI/istate_selector.hpp"

#define clamp01(a) (a < 0.0f ? 0.0f : (a > 1.0f ? 1.0f : a));

struct Stats 
{
  std::array<int, 2> position;
  float food;
  float energy;
};

template class SAI::StateMachine<Stats>;

class SeekFoodState : public SAI::IState<Stats>
{
public:
  float GetProbability(const Stats* parameters) const override
  {
    return 1.0f - parameters->food;
  }
};

class SeekShelterState : public SAI::IState<Stats>
{
public:
  float GetProbability(const Stats* parameters) const override
  {
    return 1.0f - parameters->energy;
  }
};

class LeasureState : public SAI::IState<Stats>
{
public:
  float GetProbability(const Stats* parameters) const override
  {
    return parameters->energy * parameters->food;
  }
};

void UpdateStats(Stats* stats, float dt)
{
  stats->food = clamp01(stats->food - 0.05f*dt);
  stats->energy = clamp01(stats->energy - 0.025f*dt);
}


int main(int argc, char* argv[]) {
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
  stateMachine.AddState(new SeekFoodState());
  stateMachine.AddState(new SeekShelterState());
  stateMachine.AddState(new LeasureState());

  SAI::MaxProbabilityStateSelector<Stats> selector;

  while (1) {  // Game loop.

    float dt = 1.0; 
    UpdateStats(&stats, dt);

    SAI::IState<Stats>* pCurrentState = stateMachine.GetCurrentState(&selector, &stats);
    std::string stateName = "";

    // This would normally implemented in a state class
    if (dynamic_cast<SeekFoodState*>(pCurrentState) != nullptr) 
    {
      int xDelta = std::max(-1, std::min(1, 3 - stats.position[0]));
      int yDelta = std::max(-1, std::min(1, 3 - stats.position[1]));
      stats.position = {stats.position[0] + xDelta, stats.position[1] + yDelta};

      if (xDelta == 0 && yDelta == 0){
        stats.food += 0.5f*dt;
      }

      stateName = "SeekFoodState";
    }
    else if (dynamic_cast<SeekShelterState*>(pCurrentState) != nullptr)
    {
      int xDelta = std::max(-1, std::min(1, 7 - stats.position[0]));
      int yDelta = std::max(-1, std::min(1, 7 - stats.position[1]));
      stats.position = {stats.position[0] + xDelta, stats.position[1] + yDelta};

      if (xDelta == 0 && yDelta == 0){
        stats.energy += 0.5f*dt;
      }
      
      stateName = "SeekShelterState";
    }
    else if (dynamic_cast<LeasureState*>(pCurrentState) != nullptr)
    {
      int xDelta = std::max(-1, std::min(1, 3 - stats.position[0]));
      int yDelta = std::max(-1, std::min(1, 7 - stats.position[1]));
      stats.position = {stats.position[0] + xDelta, stats.position[1] + yDelta};
      
      stateName = "LeasureState";
    }

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
    // SDL_WaitEvent(nullptr);  // Optional, sleep until events are available.
    while (SDL_PollEvent(&event)) {
      context->convert_event_coordinates(event);  // Optional, converts pixel coordinates into tile coordinates.
      switch (event.type) {
        case SDL_QUIT:
          return 0;  // Exit.
      }
    }

    SDL_Delay(1000);
  }
}