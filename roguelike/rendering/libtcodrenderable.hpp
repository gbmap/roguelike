#pragma once

#include "renderable.hpp"

#include "../../math/vec2d.hpp"
#include "../../data.hpp"

class Renderer;
using namespace roguelike;

class LibtcodRenderable : Renderable
{
public:
    void Render(Renderer* renderer) override;

    WorldRepresentation GetRepresentation();
    void SetRepresentation(WorldRepresentation representation);

    vec2di GetPosition();
    void SetPosition(vec2di position);
protected:
    WorldRepresentation representation;
    vec2di position;
};