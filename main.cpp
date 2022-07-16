#include <SDL2/SDL.h>
#include <libtcod.hpp>
#include <vector>

#include <chrono>
#include <atomic>
#include <thread>

#include "app/roguelike.hpp"
#include "app/renderer_libtcod.hpp"
#include "app/commands/world_command.hpp"

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
          Entity* entity = new Entity({"☺", {255,255,255}, {0,0,0}}, {0, 0});
          auto command = new roguelike::commands::WorldSpawnEntityCommand(entity);
          game.GetWorld().GetCommandPoll()->QueueCommand(command);
        }


        auto command = new roguelike::commands::RoguelikeKeyCommand(event.key.keysym.sym);
        game.GetCommandPoll()->QueueCommand(command);
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
  r.StartSystems();
  while (g_running) {
    PollEvents(r);
    r.Render();
  }
  return 0;
}