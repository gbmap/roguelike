#include <SDL2/SDL.h>
#include <libtcod.hpp>
#include <vector>

#include <chrono>
#include <atomic>
#include <thread>

#include "roguelike/roguelike.hpp"
#include "roguelike/renderer_libtcod.hpp"
#include "roguelike/commands/world_command.hpp"
#include "roguelike/entity_parser/entity_yml_parser.hpp"
#include "roguelike/rng.hpp"

using namespace roguelike;
using namespace std::literals::chrono_literals;

std::atomic<bool> g_running{true};

void PollEvents(Roguelike& game) {
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
      bool should_quit = event.type == SDL_QUIT
                      || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE;
      if (should_quit)
      {
        auto command = new roguelike::commands::RoguelikeExitCommand();
        game.GetCommandPoll()->QueueCommand(command);
        g_running = false;
      }
      else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_c) {
          Entity* entity = new Entity({"☺", {255,255,255}, {0,0,0}}, {40, 12});
          entity->SetBrain(new RandomMovementBrain());
          auto command = new roguelike::commands::WorldSpawnEntityCommand(entity);
          game.GetWorld().GetCommandPoll()->QueueCommand(command);

        }
        // else if (event.key.keysym.sym == )
        else { 
          auto command = new roguelike::commands::RoguelikeKeyCommand(event.key.keysym.sym);
          game.GetCommandPoll()->QueueCommand(command);
        }
      }
  }
}

int main(int argc, char* argv[]) {
  // TCOD_console_set_custom_font("terminal8x8_gs_ro.png", TCOD_FONT_LAYOUT_ASCII_INROW, 0, 0);
  auto console = tcod::Console{80, 25};  // Main console.
  auto params                  = TCOD_ContextParams{};
       params.tcod_version     = TCOD_COMPILEDVERSION;  // This is required.
       params.console          = console.get();         // Derive the window size from the console size.
       params.window_title     = "Roguelike";
       params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
       params.vsync            = true;
       params.argc             = argc;                  // This allows some user-control of the context.
       params.argv             = argv;
  auto context = tcod::new_context(params);

  Roguelike r = Roguelike(new roguelike::RendererTCOD(console, context.get()));

  auto parser = roguelike::EntityYMLParser();
  for (int i = 0; i < 20; i++) {
    std::string entity_file = "data/grass.yml";
    if (i%2 == 0) {
      entity_file = "data/shrubbery.yml";
    }

    Entity* entity = parser.ParseFile(entity_file);
    entity->SetPosition((int)((((float)RNG::Rand())/100)*80), (int)((((float)RNG::Rand())/100)*25));
    r.GetWorld().SpawnEntity(entity);
  }

  r.GetWorld().SpawnEntity(new Entity({"☺", {255,255,255}, {0,0,0}}, {40, 12}));

  r.StartSystems();
  while (g_running) {
    PollEvents(r);
    r.Render();
  }
  return 0;
}