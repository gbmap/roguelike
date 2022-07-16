#pragma once

#include "renderer.hpp"
#include "../data.hpp"

#include <libtcod.hpp>
#include <string>
#include <iostream>

namespace roguelike
{
    TCOD_ColorRGB ColorToTCODColor(const color_t& color)
    {
        return TCOD_ColorRGB{color.r, color.g, color.b};
    }

    class RendererTCOD : public Renderer
    {
    public:
        RendererTCOD(TCOD_Console& console, TCOD_Context* context) 
            : console(console), context(context) {}

        void Clear() override {
            console.clear();
        }

        void Render(const WorldRepresentation& r, const vec2di& p) const override
        {
            tcod::print(
                console, 
                {p.GetX(), p.GetY()}, 
                r.GetSymbol(),
                ColorToTCODColor(r.GetForegroundColor()),
                ColorToTCODColor(r.GetBackgroundColor())
            );
        }

        void Present() override {
            context->present(console);
        }

    private:
        TCOD_Console& console;
        TCOD_Context* context;
    };
}