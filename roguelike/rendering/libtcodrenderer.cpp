
#include "libtcodrenderer.hpp"

TCOD_ColorRGB ColorToTCODColor(const color_t& color)
{
    return TCOD_ColorRGB{color.r, color.g, color.b};
}

void LibtcodRenderer::Clear()
{
    TCOD_console_clear(&console);
}

void LibtcodRenderer::Render(
    const WorldRepresentation& representation, const vec2di& position
) const
{
    tcod::print(
        console, 
        {position.GetX(), position.GetY()}, 
        representation.GetSymbol(),
        ColorToTCODColor(representation.GetForegroundColor()),
        ColorToTCODColor(representation.GetBackgroundColor())
    );
}