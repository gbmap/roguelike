
#include <SDL2/SDL.h>
#include <libtcod.hpp>

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

  while (1) {  // Game loop.

    TCOD_console_clear(console.get());
    tcod::print(console, {0, 0}, "Hello World", std::nullopt, std::nullopt);
    context->present(console);

    SDL_Event event;
    SDL_WaitEvent(nullptr);  // Optional, sleep until events are available.
    while (SDL_PollEvent(&event)) {
      context->convert_event_coordinates(event);  // Optional, converts pixel coordinates into tile coordinates.
      switch (event.type) {
        case SDL_QUIT:
          return 0;  // Exit.
      }
    }
  }
}