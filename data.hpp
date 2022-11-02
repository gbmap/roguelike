#ifndef ENTITY_H
#define ENTITY_H

#include "./math/vec2d.hpp"

#include <stdint.h>
#include <string_view>

namespace roguelike
{
    struct color_t
    {
        uint8_t r, g, b;
    };

    typedef std::string char_t;

    class WorldRepresentation
    {
        char_t symbol           = "@";
        color_t  foreground_color = {255, 255, 255};
        color_t  background_color = {0, 0, 0};
    public:
        WorldRepresentation(char_t symbol, color_t foreground_color, color_t background_color)
            : symbol(symbol), foreground_color(foreground_color), background_color(background_color) {}
        const char_t& GetSymbol() const { return symbol; }
        const color_t& GetForegroundColor() const { return foreground_color; }
        const color_t& GetBackgroundColor() const { return background_color; }
    };

    struct EntityStats 
    {

    };
}

#endif