

#include <SDL2/SDL.h>
#include <libtcod.hpp>
#include <vector>

#include "data.hpp"
#include "app/roguelike_app.hpp"
#include "app/renderer_libtcod.hpp"

using namespace roguelike;

int main(int argc, char* argv[]) 
{
  auto console = tcod::Console{80, 25};  // Main console.
  Roguelike r = Roguelike(new roguelike::RendererTCOD(console));

  // Configure the context.
  auto params                  = TCOD_ContextParams{};
       params.tcod_version     = TCOD_COMPILEDVERSION;  // This is required.
       params.console          = console.get();         // Derive the window size from the console size.
       params.window_title     = "Libtcod Project";
       params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
       params.vsync            = true;
       params.argc             = argc;                  // This allows some user-control of the context.
       params.argv             = argv;

  auto context = tcod::new_context(params);

  // roguelike.SpawnEntity(new roguelike::EntityData{ {10, 10}, '@', {255, 255, 255}, {0, 0, 0} });
  r.SpawnEntity(new EntityData{'@', vec2di(0,0), {255, 255, 255}, {0, 0, 0} });
  r.SpawnEntity(new EntityData{'F', vec2di(10, 10), {0, 255, 0}, {0, 125, 0} });

  while (1) 
  {  
    float dt = 1.0; 

    TCOD_console_clear(console.get());

    r.Update(dt);

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