#ifndef ENTITY_H
#define ENTITY_H

#include "./math/vec2d.hpp"

#include <stdint.h>

namespace roguelike
{
    struct color_t
    {
        uint8_t r, g, b;
    };

    struct EntityData
    {
        char16_t symbol           = '@';
        vec2di   position         = vec2di(0, 0);
        color_t  foreground_color = {255, 255, 255};
        color_t  background_color = {0, 0, 0};
    };

    struct StatsData 
    {
        float food;
        float energy;
    };

    struct ActorData
    {
        EntityData entity;
        StatsData stats;
    };

}

#endif