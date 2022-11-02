
#pragma once

#include "renderer.hpp"
#include <libtcod.hpp>

class LibtcodRenderer : public Renderer
{
public:
    LibtcodRenderer(TCOD_Console& console, TCOD_Context* context) 
        : console(console), context(context) {}


    void Clear() override; 
    void Render(const WorldRepresentation& representation, const vec2di& position) const override;

private:
    TCOD_Console& console;
    TCOD_Context* context;
};