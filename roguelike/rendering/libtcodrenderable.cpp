
#include "libtcodrenderable.hpp"
#include "renderer.hpp"


WorldRepresentation LibtcodRenderable::GetRepresentation()
{
    return representation;
}

void LibtcodRenderable::SetRepresentation(WorldRepresentation representation)
{
    this->representation = representation;
}

vec2di LibtcodRenderable::GetPosition()
{
    return position;
}

void LibtcodRenderable::SetPosition(vec2di position)
{
    this->position = position;
}

void LibtcodRenderable::Render(Renderer* renderer)
{
    // return;
    renderer->Render(GetRepresentation(), GetPosition());
}